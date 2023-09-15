/**
 * @file       api_flash.c
 * @brief      Flash Memory Management for Passwords and Time Events
 * @version    1.0.0
 * @date       2023-09-01
 * @author     Khoa Vo
 * @note       This module handles storage and retrieval of time events and passwords in flash memory.
 * @example    None
 */

/* Public includes ---------------------------------------------------------- */
#include "api_flash.h"
#include "api_handle_display.h"
#include "driver_flash.h"
#include "driver_uart.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* Private includes --------------------------------------------------------- */
/* Private defines ---------------------------------------------------------- */
#define MAX_EVENTS 100 // Maximum number of door open events that can be stored

// Base addresses of each flash memory sector
#define SECTOR5_ADDRESS 0x08020000 // Sector 5
#define SECTOR6_ADDRESS 0x08040000 // Sector 6

// Base address for storing event_index and current_sector
#define CURRENT_SECTOR_ADDRESS 0x08010004

// Maximum number of passwords that can be stored
#define MAX_PASSWORDS 100

// Sector 3 address for password storage
#define SECTOR3_ADDRESS 0x0800C000

/* Private macros ----------------------------------------------------------- */
/* Public variables --------------------------------------------------------- */
// Event and current sector counters
volatile size_t event_index;
volatile uint32_t current_sector;

// Password and current sector counters
volatile size_t password_index;
volatile uint32_t password_sector = SECTOR3_ADDRESS;

uint8_t stored_password[PASSWORD_LENGTH];
/* Private variables -------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */

/* Public implementations --------------------------------------------------- */

void flash_load()
{
    // Read the initial value of current_sector from flash
    current_sector = read_current_sector_from_flash();
    // Check if the data read from flash is valid
    if (current_sector == (uint32_t)SECTOR5_ADDRESS || current_sector == (uint32_t)SECTOR6_ADDRESS)
    {
        // Count the number of events stored in the current sector
        event_index = count_event_in_sector(current_sector);
    }
    else
    {
        // If current_sector is invalid, initialize with the default value
        event_index = 0;
        current_sector = SECTOR5_ADDRESS; // or another default value if needed

        // Save the default value to flash
        save_current_sector_to_flash(current_sector);
    }
}

size_t count_event_in_sector(uint32_t sector_address)
{
    size_t event_count = 0;
    ds1307_time_t event_data;
    uint32_t address = sector_address;

    // Read each event until the maximum limit is reached
    while (event_count < MAX_EVENTS)
    {
        flash_read_array(address, (uint8_t *)&event_data, sizeof(ds1307_time_t));

        // Check if the data is 0xFF, indicating the end of events
        if (event_data.seconds == 0xFF && event_data.minutes == 0xFF)
        {
            break;
        }

        // Increment the event count
        event_count++;

        // Move to the next event
        address += sizeof(ds1307_time_t);
    }

    return event_count;
}

void save_time_to_flash(ds1307_time_t *timeData)
{
    // Check if event_index exceeds MAX_EVENTS
    if (event_index >= MAX_EVENTS)
    {
        // Switch to another sector
        current_sector = switch_to_next_sector(current_sector);

        // Save current_sector to flash
        save_current_sector_to_flash(current_sector);

        // Erase the new sector (Not implemented in this code)

        // Reset event index
        event_index = 0;
    }

    uint32_t address = current_sector;
    // Save currentTime to flash and increment event_index
    address += event_index * sizeof(ds1307_time_t);
    flash_write_array(address, (uint8_t *)timeData, sizeof(ds1307_time_t));
    event_index++;
}

void read_time_from_flash(ds1307_time_t *timeData, size_t index)
{
    uint32_t address = current_sector;
    address += index * sizeof(ds1307_time_t);
    flash_read_array(address, (uint8_t *)timeData, sizeof(ds1307_time_t));
}

void save_current_sector_to_flash(uint32_t current_sector)
{
    flash_write_array(CURRENT_SECTOR_ADDRESS, (uint8_t *)&current_sector, sizeof(uint32_t));
}

uint32_t read_current_sector_from_flash()
{
    uint32_t current_sector = 0xFFFFFFFF; // Default value when no data is available
    flash_read_array(CURRENT_SECTOR_ADDRESS, (uint8_t *)&current_sector, sizeof(uint32_t));
    return current_sector;
}

uint32_t switch_to_next_sector(uint32_t current_sector)
{
    if (current_sector == SECTOR5_ADDRESS)
    {
        return SECTOR6_ADDRESS;
    }
    else
    {
        return SECTOR5_ADDRESS;
    }
}

void flash_read_and_send_uart()
{
    ds1307_time_t stored_time;
    char timeString[20];
    for (size_t i = 0; i < event_index; i++)
    {
        read_time_from_flash(&stored_time, i);
        sprintf(timeString, "%02d/%02d/%04d %02d:%02d:%02d",
                stored_time.date, stored_time.month, stored_time.year,
                stored_time.hours, stored_time.minutes, stored_time.seconds);
        uart_transmit((uint8_t *)timeString, strlen(timeString), 300);
        char newline = '\n';
        uart_transmit((uint8_t *)&newline, 1, 100);
    }
}

//////////////// Password Management /////////////////////////

void flash_load_password()
{
//		uint8_t arr[4] = {56,56,56,56};
//		save_password_to_flash(arr);
    // Read the number of passwords from flash and increment the corresponding index
    password_index = count_password_in_sector(password_sector);
}

size_t count_password_in_sector(uint32_t sector_address)
{
    size_t password_count = 0;
    uint8_t password_data[PASSWORD_LENGTH];
    uint32_t address = sector_address;

    // Read each password until the maximum limit is reached
    while (password_count < MAX_PASSWORDS)
    {
        flash_read_array(address, password_data, PASSWORD_LENGTH);

        // Check if the data is 0xFF, indicating the end of passwords
        if (password_data[0] == 0xFF && password_data[1] == 0xFF &&
            password_data[2] == 0xFF && password_data[3] == 0xFF)
        {
            break;
        }

        // Increment the password count
        password_count++;

        // Move to the next password
        address += PASSWORD_LENGTH;
    }

    return password_count;
}

void save_password_to_flash(uint8_t *password_data)
{
    // Check if password_index exceeds MAX_PASSWORDS
    if (password_index >= MAX_PASSWORDS)
    {
        // You may add handling for switching to a new password sector here

        // Reset password_index
        password_index = 0;
    }

    uint32_t address = password_sector;
    // Save the password to flash
    address += password_index * PASSWORD_LENGTH;
    flash_write_array(address, password_data, PASSWORD_LENGTH);

    // Increment password_index
    password_index++;
}

void read_password_from_flash(uint8_t *password_data, size_t index)
{
    uint32_t address = password_sector;
    address += index * PASSWORD_LENGTH;
    flash_read_array(address, password_data, PASSWORD_LENGTH);
}

bool check_password(uint8_t *enteredPassword)
{
    // Check the last stored password (corresponding to the last index)
    if (password_index > 0)
    {
        read_password_from_flash(stored_password, password_index - 1);

        // Compare the entered password with the last stored password
        if (memcmp(enteredPassword, stored_password, PASSWORD_LENGTH) == 0)
        {
            return true; // Passwords match
        }
    }

    return false; // Passwords do not match
}
