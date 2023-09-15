/**
 * @file       rc522.h
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.1
 * @date       2023-08-20
 * @author     Thao Ton
 *
 * @brief      <RC522 Driver>
 *
 */
/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_DRIVER_RC522_H_
#define INC_DRIVER_RC522_H_
/* Includes ----------------------------------------------------------- */
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

/* Public defines ----------------------------------------------------- */
#define MFRC522_CS_LOW					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4, (GPIO_PinState) (0))
#define MFRC522_CS_HIGH					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4, (GPIO_PinState) (1))
/* MFRC522 Commands */
#define PCD_IDLE						0x00   //NO action; Cancel the current command
#define PCD_AUTHENT						0x0E   //Authentication Key
#define PCD_RECEIVE						0x08   //Receive Data
#define PCD_TRANSMIT					0x04   //Transmit data
#define PCD_TRANSCEIVE					0x0C   //Transmit and receive data,
#define PCD_RESETPHASE					0x0F   //Reset
#define PCD_CALCCRC						0x03   //CRC Calculate

/* Mifare_One card command word */
#define PICC_REQIDL						0x26   // find the antenna area does not enter hibernation
#define PICC_REQALL						0x52   // find all the cards antenna area
#define PICC_ANTICOLL					0x93   // anti-collision
#define PICC_SElECTTAG					0x93   // election card
#define PICC_AUTHENT1A					0x60   // authentication key A
#define PICC_AUTHENT1B					0x61   // authentication key B
#define PICC_READ						0x30   // Read Block
#define PICC_WRITE						0xA0   // write block
#define PICC_DECREMENT					0xC0   // debit
#define PICC_INCREMENT					0xC1   // recharge
#define PICC_RESTORE					0xC2   // transfer block data to the buffer
#define PICC_TRANSFER					0xB0   // save the data in the buffer
#define PICC_HALT						0x50   // Sleep

/* MFRC522 Registers */
//Page 0: Command and Status
#define MFRC522_REG_RESERVED00			0x00
#define MFRC522_REG_COMMAND				0x01
#define MFRC522_REG_COMM_IE_N			0x02
#define MFRC522_REG_DIV1_EN				0x03
#define MFRC522_REG_COMM_IRQ			0x04
#define MFRC522_REG_DIV_IRQ				0x05
#define MFRC522_REG_ERROR				0x06
#define MFRC522_REG_STATUS1				0x07
#define MFRC522_REG_STATUS2				0x08
#define MFRC522_REG_FIFO_DATA			0x09
#define MFRC522_REG_FIFO_LEVEL			0x0A
#define MFRC522_REG_WATER_LEVEL			0x0B
#define MFRC522_REG_CONTROL				0x0C
#define MFRC522_REG_BIT_FRAMING			0x0D
#define MFRC522_REG_COLL				0x0E
#define MFRC522_REG_RESERVED01			0x0F
//Page 1: Command
#define MFRC522_REG_RESERVED10			0x10
#define MFRC522_REG_MODE				0x11
#define MFRC522_REG_TX_MODE				0x12
#define MFRC522_REG_RX_MODE				0x13
#define MFRC522_REG_TX_CONTROL			0x14
#define MFRC522_REG_TX_AUTO				0x15
#define MFRC522_REG_TX_SELL				0x16
#define MFRC522_REG_RX_SELL				0x17
#define MFRC522_REG_RX_THRESHOLD		0x18
#define MFRC522_REG_DEMOD				0x19
#define MFRC522_REG_RESERVED11			0x1A
#define MFRC522_REG_RESERVED12			0x1B
#define MFRC522_REG_MIFARE				0x1C
#define MFRC522_REG_RESERVED13			0x1D
#define MFRC522_REG_RESERVED14			0x1E
#define MFRC522_REG_SERIALSPEED			0x1F
//Page 2: CFG
#define MFRC522_REG_RESERVED20			0x20
#define MFRC522_REG_CRC_RESULT_M		0x21
#define MFRC522_REG_CRC_RESULT_L		0x22
#define MFRC522_REG_RESERVED21			0x23
#define MFRC522_REG_MOD_WIDTH			0x24
#define MFRC522_REG_RESERVED22			0x25
#define MFRC522_REG_RF_CFG				0x26
#define MFRC522_REG_GS_N				0x27
#define MFRC522_REG_CWGS_PREG			0x28
#define MFRC522_REG__MODGS_PREG			0x29
#define MFRC522_REG_T_MODE				0x2A
#define MFRC522_REG_T_PRESCALER			0x2B
#define MFRC522_REG_T_RELOAD_H			0x2C
#define MFRC522_REG_T_RELOAD_L			0x2D
#define MFRC522_REG_T_COUNTER_VALUE_H	0x2E
#define MFRC522_REG_T_COUNTER_VALUE_L	0x2F
//Page 3:TestRegister
#define MFRC522_REG_RESERVED30			0x30
#define MFRC522_REG_TEST_SEL1			0x31
#define MFRC522_REG_TEST_SEL2			0x32
#define MFRC522_REG_TEST_PIN_EN			0x33
#define MFRC522_REG_TEST_PIN_VALUE		0x34
#define MFRC522_REG_TEST_BUS			0x35
#define MFRC522_REG_AUTO_TEST			0x36
#define MFRC522_REG_VERSION				0x37
#define MFRC522_REG_ANALOG_TEST			0x38
#define MFRC522_REG_TEST_ADC1			0x39
#define MFRC522_REG_TEST_ADC2			0x3A
#define MFRC522_REG_TEST_ADC0			0x3B
#define MFRC522_REG_RESERVED31			0x3C
#define MFRC522_REG_RESERVED32			0x3D
#define MFRC522_REG_RESERVED33			0x3E
#define MFRC522_REG_RESERVED34			0x3F
//Dummy byte
#define MFRC522_DUMMY					0x00
#define MFRC522_MAX_LEN					16

typedef enum {
	MI_OK = 0,
	MI_NOTAGERR,
	MI_ERR
} mfrc522_status_t;

typedef struct {
		uint8_t card_id[5];
		uint8_t flag_the;
		uint8_t byte_first, byte_second, dem;
		uint8_t byte_data[1];
		uint8_t old_id[5];
} rc522_data;

/* Public variables --------------------------------------------------- */

/**
 * @brief Transmit a single byte of data over SPI and receive the response.
 *
 * This function sends a single byte of data over the SPI communication using the specified SPI peripheral.
 * It waits until the transmit buffer is empty and then sends the data. After sending, it waits for the
 * transmission to complete and then reads the response data from the slave device.
 *
 * @param[in] data The byte of data to be sent over SPI.
 * @return The byte of data received from the slave device in response.
 */
 uint8_t tm_spi_send(uint8_t data);
/**
 * @brief Read the value of a register from the MFRC522 RFID module.
 *
 * This function reads the value of a specified register from the MFRC522 RFID module. It communicates with
 * the module via SPI communication protocol. The function first selects the module (CS low), sends the
 * appropriate command and register address, reads the response, deselects the module (CS high), and finally
 * returns the received register value.
 *
 * @param[in] addr The address of the register to be read.
 * @return The value of the register read from the MFRC522 module.
 */
 uint8_t mfrc522_read_register(uint8_t addr);
/**
 * @brief Select a tag using its serial number.
 *
 * This function selects a tag using its serial number with the MFRC522 RFID module. It prepares the necessary
 * data, calculates the CRC, sends the data to the module using transceive mode, and receives the response.
 * The function checks the status and received bits to determine if the tag selection was successful. If
 * successful, it returns the size of the received data; otherwise, it returns 0.
 *
 * @param[in] ser_num A pointer to the serial number of the tag to be selected.
 * @return The size of the received data if tag selection is successful; otherwise, 0.
 */
 uint8_t mfrc522_select_tag(uint8_t* ser_num);

/* Public function prototypes ---------------------------------------- */

/**
 * @brief Initialize the MFRC522 RFID module.
 *
 * This function initializes the MFRC522 RFID module by performing the necessary configuration steps. It resets
 * the module, sets the timer mode and prescaler, configures the receiver gain, enables automatic transmission,
 * sets the mode, and turns on the antenna. This prepares the module for further operations.
 *
 * @return None.
 */
 void mfrc522_init(void);
/**
 * @brief Write a value to a specific register of the MFRC522 RFID module.
 *
 * This function writes a value to a specific register of the MFRC522 RFID module. It performs the necessary SPI
 * communication to send the register address along with the value to be written.
 *
 * @param[in] addr Register address to write to.
 * @param[in] val Value to be written to the register.
 * @return None.
 */
 void mfrc522_write_register(uint8_t addr, uint8_t val);
/**
 * @brief Set specific bits of a register in the MFRC522 RFID module.
 *
 * This function sets specific bits of a register in the MFRC522 RFID module to 1 without affecting other bits.
 *
 * @param[in] reg Register to modify.
 * @param[in] mask Mask indicating which bits to set to 1.
 * @return None.
 */
 void mfrc522_set_bit_mask(uint8_t reg, uint8_t mask);
/**
 * @brief Clear specific bits of a register in the MFRC522 RFID module.
 *
 * This function clears specific bits of a register in the MFRC522 RFID module to 0 without affecting other bits.
 *
 * @param[in] reg Register to modify.
 * @param[in] mask Mask indicating which bits to clear to 0.
 * @return None.
 */
 void mfrc522_clear_bit_mask(uint8_t reg, uint8_t mask);
/**
 * @brief Turn on the antenna of the MFRC522 RFID module.
 *
 * This function activates the antenna of the MFRC522 RFID module, allowing it to communicate with nearby RFID tags.
 *
 * @return None.
 */
void mfrc522_antenna_on(void);

/**
 * @brief Turn off the antenna of the MFRC522 RFID module.
 *
 * This function deactivates the antenna of the MFRC522 RFID module, preventing it from communicating with nearby RFID tags.
 *
 * @return None.
 */
void mfrc522_antenna_off(void);
/**
 * @brief Reset the MFRC522 RFID module.
 *
 * This function performs a reset on the MFRC522 RFID module, initializing its internal state to a known configuration.
 *
 * @return None.
 */
void mfrc522_reset(void);

/**
 * @brief Calculate CRC value for data.
 *
 * This function calculates the CRC (Cyclic Redundancy Check) value for the provided input data.
 *
 * @param[in] picc_in_data Pointer to the input data array.
 * @param[in] len Length of the input data array.
 * @param[out] picc_out_data Pointer to store the calculated CRC value.
 * @return None.
 */
void mfrc522_calculate_crc(uint8_t* picc_in_data, uint8_t len, uint8_t* picc_out_data);

/**
 * @brief Halt the communication with a PICC (Proximity Integrated Circuit Card).
 *
 * This function sends a command to halt the communication with a PICC (RFID tag), allowing the MFRC522 to stop further communication with the tag.
 *
 * @return None.
 */
void mfrc522_halt(void);

/**
 * @brief Check for the presence of a card in the vicinity of the MFRC522 module.
 *
 * This function checks for the presence of a card in the communication range of the MFRC522 module.
 *
 * @param[in,out] id Pointer to an array to store the ID of the detected card.
 * @return Status of the card detection (MI_OK if a card is detected, MI_NOTAGERR if no card is detected, MI_ERR for other errors).
 */
mfrc522_status_t mfrc522_check(uint8_t* id);

/**
 * @brief Compare two card IDs.
 *
 * This function compares two card IDs to check if they are the same.
 *
 * @param[in] card_id Pointer to the ID of the first card.
 * @param[in] compare_id Pointer to the ID of the second card to compare with.
 * @return Status of the comparison (MI_OK if the IDs match, MI_ERR if they do not match).
 */
mfrc522_status_t mfrc522_compare(uint8_t* card_id, uint8_t* compare_id);

/**
 * @brief Request a communication session with a PICC (Proximity Integrated Circuit Card).
 *
 * This function sends a request to initiate communication with a PICC and determine the type of the card.
 *
 * @param[in] request_mode Request mode for communication initiation.
 * @param[out] tag_type Pointer to store the type of the detected card.
 * @return Status of the request (MI_OK if successful, MI_ERR for errors).
 */
mfrc522_status_t mfrc522_request(uint8_t request_mode, uint8_t* tag_type);

/**
 * @brief Perform data exchange with a PICC (Proximity Integrated Circuit Card).
 *
 * This function sends data to a PICC and receives data back, allowing bidirectional communication with the card.
 *
 * @param[in] command Command code for the communication.
 * @param[in] send_data Pointer to the data to be sent.
 * @param[in] send_len Length of the data to be sent.
 * @param[out] back_data Pointer to store the received data.
 * @param[in,out] back_len Pointer to the expected and actual length of the received data.
 * @return Status of the communication (MI_OK if successful, MI_ERR for errors).
 */
 mfrc522_status_t mfrc522_to_card(uint8_t command, uint8_t* send_data, uint8_t send_len, uint8_t* back_data, uint16_t* back_len);

/**
 * @brief Perform anti-collision procedure to detect multiple cards in the vicinity.
 *
 * This function performs the anti-collision procedure to detect multiple cards present in the communication range.
 *
 * @param[out] ser_num Pointer to an array to store the serial number of the detected card.
 * @return Status of the anti-collision procedure (MI_OK if successful, MI_ERR for errors).
 */
 mfrc522_status_t mfrc522_anticoll(uint8_t* ser_num);

/**
 * @brief Authenticate with a PICC (Proximity Integrated Circuit Card).
 *
 * This function performs authentication with a PICC using the provided authentication mode and sector key.
 *
 * @param[in] auth_mode Authentication mode (PICC_AUTHENT1A or PICC_AUTHENT1B).
 * @param[in] block_addr Address of the block to authenticate.
 * @param[in] sector_key Pointer to the sector key for authentication.
 * @param[in] ser_num Pointer to the serial number of the card.
 * @return Status of the authentication (MI_OK if successful, MI_ERR for errors).
 */
 mfrc522_status_t mfrc522_auth(uint8_t auth_mode, uint8_t block_addr, uint8_t* sector_key, uint8_t* ser_num);

/**
 * @brief Read data from a specific block of a PICC.
 *
 * This function reads data from a specific block of a PICC using the provided block address.
 *
 * @param[in] block_addr Address of the block to read from.
 * @param[out] receive_data Pointer to store the received data.
 * @return Status of the read operation (MI_OK if successful, MI_ERR for errors).
 */
 mfrc522_status_t mfrc522_read(uint8_t block_addr, uint8_t* receive_data);

/**
 * @brief Write data to a specific block of a PICC.
 *
 * This function writes data to a specific block of a PICC using the provided block address.
 *
 * @param[in] block_addr Address of the block to write to.
 * @param[in] writeData Pointer to the data to be written.
 * @return Status of the write operation (MI_OK if successful, MI_ERR for errors).
 */
 mfrc522_status_t mfrc522_write(uint8_t block_addr, uint8_t* writeData);


#endif /* INC_DRIVER_RC522_H_ */

