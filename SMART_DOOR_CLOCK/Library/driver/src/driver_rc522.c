/**
 * @file       ds1307.c
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.1
 * @date       2023-08-20
 * @author     Thao Ton
 *
 * @brief      Implementation of functions related to DS1307 RTC.
 *
 */

/* Includes ----------------------------------------------------------- */
#include "driver_rc522.h"
#include "bsp_spi.h"
/* Pubic variables ------------------------------------------------------*/
uint8_t back_data[12], m;
rc522_data rc522;

uint8_t tm_spi_send(uint8_t data)
{
	uint8_t data_se[1], data_re[1];
	data_se[0] = data;
	bsp_spi_transmit_receive(data_se, data_re, 1, 10);
	return data_re[0];
}

uint8_t mfrc522_select_tag(uint8_t* ser_num)
{
	uint8_t i;
	mfrc522_status_t status;
	uint8_t size;
	uint16_t recv_bits;
	uint8_t buffer[9];

	buffer[0] = PICC_SElECTTAG;
	buffer[1] = 0x70;
	for (i = 0; i < 5; i++)
	{
		buffer[i+2] = *(ser_num + i);
	}
	mfrc522_calculate_crc(buffer, 7, &buffer[7]);
	status = mfrc522_to_card(PCD_TRANSCEIVE, buffer, 9, buffer, &recv_bits);

	if ((status == MI_OK) && (recv_bits == 0x18)) {
		size = buffer[0];
	} else {
		size = 0;
	}

	return size;
}

uint8_t mfrc522_read_register(uint8_t addr)
{
	uint8_t val;
	//CS low
	MFRC522_CS_LOW;
	tm_spi_send(((addr << 1) & 0x7E) | 0x80);
	val = tm_spi_send(MFRC522_DUMMY);
	//CS high
	MFRC522_CS_HIGH;
	return val;
}

/* Public function prototypes ---------------------------------------- */
void mfrc522_init(void)
{
	mfrc522_reset();

	mfrc522_write_register(MFRC522_REG_T_MODE, 0x8D);
	mfrc522_write_register(MFRC522_REG_T_PRESCALER, 0x3E);
	mfrc522_write_register(MFRC522_REG_T_RELOAD_L, 30);
	mfrc522_write_register(MFRC522_REG_T_RELOAD_H, 0);

	/* 48dB gain */
	mfrc522_write_register(MFRC522_REG_RF_CFG, 0x70);

	mfrc522_write_register(MFRC522_REG_TX_AUTO, 0x40);
	mfrc522_write_register(MFRC522_REG_MODE, 0x3D);

	mfrc522_antenna_on();	//Open the antenna
}

mfrc522_status_t mfrc522_check(uint8_t* id)
{
	mfrc522_status_t status;
	//Find cards, return card type

	status = mfrc522_request(PICC_REQIDL, id);

	if (status == MI_OK) {
		//Card detected
		//Anti-collision, return card serial number 4 bytes
		status = mfrc522_anticoll(id);
	}
	mfrc522_halt();			//Command card into hibernation
	return status;
}

mfrc522_status_t mfrc522_compare(uint8_t* card_id, uint8_t* compare_id)
{
	uint8_t i;
	for (i = 0; i < 5; i++) {
		if (card_id[i] != compare_id[i]) {
			return MI_ERR;
		}
	}
	return MI_OK;
}

mfrc522_status_t mfrc522_request(uint8_t request_mode, uint8_t* tag_type)
{
	mfrc522_status_t status;
	uint16_t backBits;			//The received data bits

	mfrc522_write_register(MFRC522_REG_BIT_FRAMING, 0x07);		//TxLastBists = BitFramingReg[2..0]	???

	tag_type[0] = request_mode;
	status = mfrc522_to_card(PCD_TRANSCEIVE, tag_type, 1, tag_type, &backBits);
	if ((status != MI_OK) || (backBits != 0x10)) {
		status = MI_ERR;
	}

	return status;
}

mfrc522_status_t mfrc522_to_card(uint8_t command, uint8_t* send_data, uint8_t send_len, uint8_t* back_data, uint16_t* back_len) {
	mfrc522_status_t status = MI_ERR;
	uint8_t irqEn = 0x00;
	uint8_t waitIRq = 0x00;
	uint8_t lastBits;
	uint8_t n;
	uint16_t i;

	switch (command) {
		case PCD_AUTHENT: {
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case PCD_TRANSCEIVE: {
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
			break;
	}

	mfrc522_write_register(MFRC522_REG_COMM_IE_N, irqEn | 0x80);
	mfrc522_clear_bit_mask(MFRC522_REG_COMM_IRQ, 0x80);
	mfrc522_set_bit_mask(MFRC522_REG_FIFO_LEVEL, 0x80);

	mfrc522_write_register(MFRC522_REG_COMMAND, PCD_IDLE);

	//Writing data to the FIFO
	for (i = 0; i < send_len; i++) {
		mfrc522_write_register(MFRC522_REG_FIFO_DATA, send_data[i]);
	}

	//Execute the command
	mfrc522_write_register(MFRC522_REG_COMMAND, command);
	if (command == PCD_TRANSCEIVE) {
		mfrc522_set_bit_mask(MFRC522_REG_BIT_FRAMING, 0x80);		//StartSend=1,transmission of data starts
	}

	//Waiting to receive data to complete
	i = 2000;	//i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms???
	do {
		//CommIrqReg[7..0]
		//Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
		n = mfrc522_read_register(MFRC522_REG_COMM_IRQ);
		i--;
	} while ((i!=0) && !(n&0x01) && !(n&waitIRq));

	mfrc522_clear_bit_mask(MFRC522_REG_BIT_FRAMING, 0x80);			//StartSend=0

	if (i != 0)  {
		if (!(mfrc522_read_register(MFRC522_REG_ERROR) & 0x1B)) {
			status = MI_OK;
			if (n & irqEn & 0x01) {
				status = MI_NOTAGERR;
			}

			if (command == PCD_TRANSCEIVE) {
				n = mfrc522_read_register(MFRC522_REG_FIFO_LEVEL);
				lastBits = mfrc522_read_register(MFRC522_REG_CONTROL) & 0x07;
				if (lastBits) {
					*back_len = (n - 1) * 8 + lastBits;
				} else {
					*back_len = n * 8;
				}

				if (n == 0) {
					n = 1;
				}
				if (n > MFRC522_MAX_LEN) {
					n = MFRC522_MAX_LEN;
				}

				//Reading the received data in FIFO
				for (i = 0; i < n; i++) {
					back_data[i] = mfrc522_read_register(MFRC522_REG_FIFO_DATA);
				}
			}
		} else {
			status = MI_ERR;
		}
	}

	return status;
}

mfrc522_status_t mfrc522_anticoll(uint8_t* ser_num) {
	mfrc522_status_t status;
	uint8_t i;
	uint8_t ser_numCheck = 0;
	uint16_t unLen;

	mfrc522_write_register(MFRC522_REG_BIT_FRAMING, 0x00);		//TxLastBists = BitFramingReg[2..0]

	ser_num[0] = PICC_ANTICOLL;
	ser_num[1] = 0x20;
	status = mfrc522_to_card(PCD_TRANSCEIVE, ser_num, 2, ser_num, &unLen);

	if (status == MI_OK) {
		//Check card serial number
		for (i = 0; i < 4; i++) {
			ser_numCheck ^= ser_num[i];
		}
		if (ser_numCheck != ser_num[i]) {
			status = MI_ERR;
		}
	}
	return status;
}



mfrc522_status_t mfrc522_auth(uint8_t auth_mode, uint8_t block_addr, uint8_t* sector_key, uint8_t* ser_num) {
	mfrc522_status_t status;
	uint16_t recv_bits;
	uint8_t i;
	uint8_t buff[12];

	//Verify the command block address + sector + password + card serial number
	buff[0] = auth_mode;
	buff[1] = block_addr;
	for (i = 0; i < 6; i++) {
		buff[i+2] = *(sector_key+i);
	}
	for (i=0; i<4; i++) {
		buff[i+8] = *(ser_num+i);
	}
	status = mfrc522_to_card(PCD_AUTHENT, buff, 12, buff, &recv_bits);


	if ((status != MI_OK) || (!(mfrc522_read_register(MFRC522_REG_STATUS2) & 0x08))) {
		status = MI_ERR;
	}

	return status;
}

mfrc522_status_t mfrc522_read(uint8_t block_addr, uint8_t* receive_data) {
	mfrc522_status_t status;
	uint16_t unLen;

	receive_data[0] = PICC_READ;
	receive_data[1] = block_addr;
	mfrc522_calculate_crc(receive_data,2, &receive_data[2]);
	status = mfrc522_to_card(PCD_TRANSCEIVE, receive_data, 4, receive_data, &unLen);

	if ((status != MI_OK) || (unLen != 0x90)) {
		status = MI_ERR;
	}

	return status;
}

mfrc522_status_t mfrc522_write(uint8_t block_addr, uint8_t* writeData) {
	mfrc522_status_t status;
	uint16_t recv_bits;
	uint8_t i;
	uint8_t buff[18];

	buff[0] = PICC_WRITE;
	buff[1] = block_addr;
	mfrc522_calculate_crc(buff, 2, &buff[2]);
	status = mfrc522_to_card(PCD_TRANSCEIVE, buff, 4, buff, &recv_bits);

	if ((status != MI_OK) || (recv_bits != 4) || ((buff[0] & 0x0F) != 0x0A)) {
		status = MI_ERR;
	}

	if (status == MI_OK) {
		//Data to the FIFO write 16Byte
		for (i = 0; i < 16; i++) {
			buff[i] = *(writeData+i);
		}
		mfrc522_calculate_crc(buff, 16, &buff[16]);
		status = mfrc522_to_card(PCD_TRANSCEIVE, buff, 18, buff, &recv_bits);

		if ((status != MI_OK) || (recv_bits != 4) || ((buff[0] & 0x0F) != 0x0A)) {
			status = MI_ERR;
		}
	}

	return status;
}

void mfrc522_write_register(uint8_t addr, uint8_t val) {
	//CS low
	MFRC522_CS_LOW;
	//Send address
	tm_spi_send((addr << 1) & 0x7E);
	//Send data
	tm_spi_send(val);
	//CS high
	MFRC522_CS_HIGH;
}

void mfrc522_set_bit_mask(uint8_t reg, uint8_t mask) {
	mfrc522_write_register(reg, mfrc522_read_register(reg) | mask);
}

void mfrc522_clear_bit_mask(uint8_t reg, uint8_t mask){
	mfrc522_write_register(reg, mfrc522_read_register(reg) & (~mask));
}

void mfrc522_antenna_on(void) {
	uint8_t temp;

	temp = mfrc522_read_register(MFRC522_REG_TX_CONTROL);
	if (!(temp & 0x03)) {
		mfrc522_set_bit_mask(MFRC522_REG_TX_CONTROL, 0x03);
	}
}

void mfrc522_antenna_off(void) {
	mfrc522_clear_bit_mask(MFRC522_REG_TX_CONTROL, 0x03);
}

void mfrc522_reset(void) {
	mfrc522_write_register(MFRC522_REG_COMMAND, PCD_RESETPHASE);
}



void mfrc522_calculate_crc(uint8_t*  picc_in_data, uint8_t len, uint8_t* picc_out_data) {
	uint8_t i, n;

	mfrc522_clear_bit_mask(MFRC522_REG_DIV_IRQ, 0x04);			//CRCIrq = 0
	mfrc522_set_bit_mask(MFRC522_REG_FIFO_LEVEL, 0x80);			//Clear the FIFO pointer
	//Write_MFRC522(CommandReg, PCD_IDLE);

	//Writing data to the FIFO
	for (i = 0; i < len; i++) {
		mfrc522_write_register(MFRC522_REG_FIFO_DATA, *(picc_in_data+i));
	}
	mfrc522_write_register(MFRC522_REG_COMMAND, PCD_CALCCRC);

	//Wait CRC calculation is complete
	i = 0xFF;
	do {
		n = mfrc522_read_register(MFRC522_REG_DIV_IRQ);
		i--;
	} while ((i!=0) && !(n&0x04));			//CRCIrq = 1

	//Read CRC calculation result
	picc_out_data[0] = mfrc522_read_register(MFRC522_REG_CRC_RESULT_L);
	picc_out_data[1] = mfrc522_read_register(MFRC522_REG_CRC_RESULT_M);
}

void mfrc522_halt(void) {
	uint16_t unLen;
	uint8_t buff[4];

	buff[0] = PICC_HALT;
	buff[1] = 0;
	mfrc522_calculate_crc(buff, 2, &buff[2]);
	mfrc522_to_card(PCD_TRANSCEIVE, buff, 4, buff, &unLen);
}

/* End of file -------------------------------------------------------- */
