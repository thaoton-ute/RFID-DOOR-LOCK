/*
 * api_flash.c
 *
 *  Created on: Sep 3, 2023
 *      Author: Admin
 */


#include "api_flash.h"
#include "stm32f4xx.h"
#include "driver_ds1307.h"
#include "driver_flash.h"
#include <stdio.h>

#define FLASH_START_ADDRESS 0x08010000 // Sector 4
#define FLASH_SECTOR_SIZE 65500 // 65536

// The variable to track the current position
uint32_t flash_address = FLASH_START_ADDRESS;


// write full time to Flash
void flash_save_time()
{
	ds1307_time_t time;
	ds1307_get_date_time(&time);

	HAL_FLASH_Unlock();

	if (flash_address >= (FLASH_START_ADDRESS + FLASH_SECTOR_SIZE))
	{
		flash_address = FLASH_START_ADDRESS;
	}

	flash_write_array(flash_address, (uint8_t*) &time, sizeof(time));

	HAL_FLASH_Lock();

	flash_address += sizeof(time);
}

void flash_read_time(uint32_t address, ds1307_time_t *time)
{
    flash_read_array(address, (uint8_t*)time, sizeof(ds1307_time_t));
}

void flash_read_time_and_send_uart(void)
{
	uint32_t address = FLASH_START_ADDRESS;
	ds1307_time_t time;
	char buffer[34];
    while (address < (FLASH_START_ADDRESS + FLASH_SECTOR_SIZE))
    {
    	flash_read_time(address, &time);
        sprintf(buffer, "Time: %02d:%02d:%02d Date: %02d/%02d/%04d\r\n",
                    time.hours, time.minutes, time.seconds,
					time.date, time.month, time.year);
        address += sizeof(time);
    }
}
