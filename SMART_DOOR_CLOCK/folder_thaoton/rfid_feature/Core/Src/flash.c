/**
 * @file       flash.c
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.1
 * @date       2023-08-25
 *
 * @brief      <Flash>
 */
/* Includes ----------------------------------------------------------- */
#include "flash.h"
#include "bsp_flash.h"
#include "stm32f4xx.h"

/* Public function prototypes ----------------------------------------- */
void flash_erase_sector2(uint32_t address)
{
	bsp_flash_unlock();

	FLASH_EraseInitTypeDef EraseInitStruct;

	EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.Banks = FLASH_BANK_1; // Choose the appropriate bank
	EraseInitStruct.Sector = FLASH_SECTOR_2; // Set sector 0
	EraseInitStruct.NbSectors = 1; // Since you want to erase only 1 sector
	EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3; // Set the appropriate voltage range

	uint32_t page_err;

	bsp_flashex_erase(&EraseInitStruct, &page_err);
	bsp_flash_lock();
}



void flash_write_int(uint32_t address, int value)
{
	bsp_flash_unlock();
	bsp_flash_program(FLASH_TYPEPROGRAM_WORD, address, value);
	bsp_flash_lock();
}

void flash_write_float(uint32_t address, float f)
{
	bsp_flash_unlock();
	uint8_t data[4];
	*(float*)data = f;
	bsp_flash_program(FLASH_TYPEPROGRAM_WORD, address, *(uint32_t*)data);
	bsp_flash_lock();
}

void flash_write_array(uint32_t address, uint8_t *arr, uint16_t len)
{
	bsp_flash_unlock();
	uint16_t *pt = (uint16_t*)arr;
	for(uint16_t i = 0; i < (len + 1)/2; i++)
	{
		bsp_flash_program(FLASH_TYPEPROGRAM_HALFWORD, address + 2*i, *pt);
		pt++;
	}
	bsp_flash_lock();
}

void flash_write_struct(uint32_t address, wifi_info_t dta)
{
	flash_write_array(address, (uint8_t *) &dta, sizeof(dta));
}

int flash_read_int(uint32_t address)
{
	return *(__IO uint16_t *) (address);
}

float flash_read_float(uint32_t address)
{
	uint32_t data = *(__IO uint32_t *)(address);
	return *(float*)(&data);
}

void flash_read_array(uint32_t address, uint8_t *arr, uint16_t len)
{
	uint16_t *pt = (uint16_t*)arr;
	for(uint16_t i = 0; i < (len + 1)/2; i++)
	{
		*pt = *(__IO uint16_t *)(address + 2*i);
		pt++;
	}
}

//void flash_write_array(uint32_t address, uint8_t *arr, uint16_t len)
//{
//    bsp_flash_unlock();
//    for (uint16_t i = 0; i < len; i++)
//    {
//        bsp_flash_program(FLASH_TYPEPROGRAM_BYTE, address + i, arr[i]);
//    }
//    bsp_flash_lock();
//}
//
//
//void flash_read_array(uint32_t address, uint8_t *arr, uint16_t len)
//{
//    for (uint16_t i = 0; i < len; i++)
//    {
//        arr[i] = *(__IO uint8_t *)(address + i);
//    }
//}


void flash_read_struct(uint32_t address ,wifi_info_t *dta)
{
	flash_read_array(address, (uint8_t *)dta, sizeof(wifi_info_t));
}

/* End of file -------------------------------------------------------- */
