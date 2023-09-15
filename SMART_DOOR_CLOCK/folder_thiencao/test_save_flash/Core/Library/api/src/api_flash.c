/*
 * api_flash.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Admin
 */

#include "api_flash.h"


#include "driver_flash.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define MAX_EVENTS 100 // Số lượng sự kiện mở cửa tối đa có thể lưu
#define MAX_PASSWORD 20
// Địa chỉ cơ sở của mỗi sector trong flash
#define SECTOR3_ADDRESS 0x0800C000
#define SECTOR5_ADDRESS 0x08020000 // Sector 5 //
#define SECTOR6_ADDRESS 0x08040000 // Sector 6 //

// Địa chỉ cơ sở cho lưu trữ eventIndex và currentSector
//#define EVENT_INDEX_ADDRESS 0x08010000	// Sector 4 //
#define CURRENT_SECTOR_ADDRESS 0x08020004

// Biến đếm sự kiện và sector hiện tại
volatile size_t eventIndex;
volatile uint32_t currentSector;

void flash_load()
{
    // Đọc giá trị ban đầu của currentSector từ flash
    currentSector = readCurrentSectorFromFlash();

    // Kiểm tra xem dữ liệu đọc từ flash có hợp lệ không
    if (currentSector == SECTOR5_ADDRESS || currentSector == SECTOR6_ADDRESS)
    {
        // Đếm số lượng sự kiện đã lưu trong sector hiện tại
        eventIndex = countEventsInSector(currentSector);
    }
    else
    {
        // Nếu currentSector không hợp lệ, khởi tạo giá trị mặc định
        eventIndex = 0;
        currentSector = SECTOR5_ADDRESS; // Hoặc giá trị mặc định khác nếu cần

        // Lưu giá trị mặc định vào flash
        saveCurrentSectorToFlash(currentSector);
    }
}

// Function để đếm số lượng sự kiện đã lưu trong một sector
size_t countEventsInSector(uint32_t sectorAddress)
{
    size_t eventCount = 0;
    ds1307_time_t eventData;
    uint32_t address = sectorAddress;

    // Đọc từng sự kiện cho đến khi đạt đến giới hạn tối đa
    while (eventCount < MAX_EVENTS)
    {
        flash_read_array(address, (uint8_t *)&eventData, sizeof(ds1307_time_t));

        // Kiểm tra nếu dữ liệu là 0xFF thì chúng ta đã đạt đến cuối sự kiện
        if (eventData.seconds == 0xFF && eventData.minutes == 0xFF)
        {
            break;
        }

        // Tăng số lượng sự kiện
        eventCount++;

        // Di chuyển đến sự kiện tiếp theo
        address += sizeof(ds1307_time_t);
    }

    return eventCount;
}

void saveTimeToFlash(ds1307_time_t* timeData)
{
    // Kiểm tra xem eventIndex có vượt quá MAX_EVENTS hay không
    if (eventIndex >= MAX_EVENTS)
    {
        // Chuyển sang sector khác
        currentSector = switchToNextSector(currentSector);

        // Lưu currentSector vào flash
        saveCurrentSectorToFlash(currentSector);

        // Xoá sector mới


        // Khởi tạo lại event index
        eventIndex = 0;
    }

    // Lưu currentTime vào flash và tăng eventIndex
    currentSector += eventIndex * sizeof(ds1307_time_t);
    flash_write_array(currentSector, (uint8_t*)timeData, sizeof(ds1307_time_t));
    eventIndex++;

}

// Function to read the struct from flash
void readTimeFromFlash(ds1307_time_t* timeData, uint32_t address, size_t index)
{
    address += index * sizeof(ds1307_time_t);
    flash_read_array(address, (uint8_t*)timeData, sizeof(ds1307_time_t));
}

//// Function to save the event index to flash
//void saveEventIndexToFlash(size_t eventIndex)
//{
//    flash_write_array(EVENT_INDEX_ADDRESS, (uint8_t*)&eventIndex, sizeof(size_t));
//}

//// Function to read the event index from flash
//size_t readEventIndexFromFlash()
//{
//    size_t eventIndex = 0xFFFFFFFF; // Giá trị mặc định khi chưa có dữ liệu
//    flash_read_array(EVENT_INDEX_ADDRESS, (uint8_t*)&eventIndex, sizeof(size_t));
//    return eventIndex;
//}

// Function to save the current sector to flash
void saveCurrentSectorToFlash(uint32_t currentSector)
{
    flash_write_array(CURRENT_SECTOR_ADDRESS, (uint8_t*)&currentSector, sizeof(uint32_t));
}

// Function to read the current sector from flash
uint32_t readCurrentSectorFromFlash()
{
    uint32_t currentSector = 0xFFFFFFFF; // Giá trị mặc định khi chưa có dữ liệu
    flash_read_array(CURRENT_SECTOR_ADDRESS, (uint8_t*)&currentSector, sizeof(uint32_t));
    return currentSector;
}

// Function to switch to the next sector
uint32_t switchToNextSector(uint32_t currentSector)
{
    if (currentSector == SECTOR5_ADDRESS)
    {
        return SECTOR6_ADDRESS;
    }
    else
    {
        return SECTOR5_ADDRESS;
    }
}

uint8_t get_index(uint8_t arr[][4]){
	for(uint8_t i = 0; i < 20; i++){
		if(arr[i][0] == 255){
			return i;
		}
	}
	return 0;
}

// row : 10, col : 6
// return index current password , get this password byte arr[index][4]
uint8_t read_password_from_flash(uint32_t address, uint8_t arr[][4], uint16_t rows, uint16_t cols){
	flash_read_2d_array(address, arr, rows, cols);
	uint8_t index = get_index(arr);
	return index;
}

// len : 4
void save_password_to_flash(uint32_t address, uint8_t *arr, uint16_t len, uint8_t index){
	flash_write_array(address + index * 4, arr, len);
}



