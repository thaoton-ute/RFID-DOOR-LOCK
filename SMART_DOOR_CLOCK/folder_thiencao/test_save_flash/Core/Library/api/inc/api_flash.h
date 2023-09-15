/*
 * api_flash.h
 *
 *  Created on: Sep 6, 2023
 *      Author: Admin
 */

#ifndef LIBRARY_API_INC_API_FLASH_H_
#define LIBRARY_API_INC_API_FLASH_H_

#include "stm32f4xx_hal.h"
#include "driver_ds1307.h"

void flash_load();

size_t countEventsInSector(uint32_t sectorAddress);

void saveTimeToFlash(ds1307_time_t* timeData);

void readTimeFromFlash(ds1307_time_t* timeData, uint32_t address, size_t index);

//void saveEventIndexToFlash(size_t eventIndex);

//size_t readEventIndexFromFlash();

void saveCurrentSectorToFlash(uint32_t currentSector);

uint32_t readCurrentSectorFromFlash();

uint32_t switchToNextSector(uint32_t currentSector);

void save_password_to_flash(uint32_t address, uint8_t *arr, uint16_t len, uint8_t index);

uint8_t get_index(uint8_t arr[][4]);

uint8_t read_password_from_flash(uint32_t address, uint8_t arr[][4], uint16_t rows, uint16_t cols);
#endif /* LIBRARY_API_INC_API_FLASH_H_ */
