/**
 * @file       api_flash.h
 * @brief      Driver for Flash Memory Operations
 * @version    1.0.0
 * @date       2023-09-06
 * @author     Khoa Vo
 * @brief      Flash for password and time
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef LIBRARY_API_INC_API_FLASH_H_
#define LIBRARY_API_INC_API_FLASH_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "stm32f4xx_hal.h"
#include "driver_ds1307.h"
#include "main.h"

/* Public defines ----------------------------------------------------------- */
#define PASSWORD_LENGTH 4 // Length of password

/* Public enumerate/structure ----------------------------------------------- */

/* Public macros ------------------------------------------------------------ */
/* Public variables --------------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/**
 * @brief Initializes the flash module, reads the current sector, and counts stored events.
 */
void flash_load();

/**
 * @brief Counts the number of events stored in a given flash memory sector.
 *
 * @param sectorAddress The base address of the flash memory sector.
 * @return The number of events stored in the sector.
 */
size_t count_event_in_sector(uint32_t sector_address);

/**
 * @brief Saves a time event to the flash memory.
 *
 * @param timeData Pointer to the time event structure to be saved.
 */
void save_time_to_flash(ds1307_time_t* timeData);

/**
 * @brief Reads a time event from the flash memory.
 *
 * @param timeData Pointer to the time event structure to store the read data.
 * @param index The index of the time event to read.
 */
void read_time_to_flash(ds1307_time_t* timeData, size_t index);

/**
 * @brief Saves the current sector to the flash memory.
 *
 * @param currentSector The current flash memory sector to be saved.
 */
void save_current_sector_to_flash(uint32_t current_sector);

/**
 * @brief Read the current flash memory sector from flash.
 *
 * @return The address of the current flash memory sector.
 */
uint32_t read_current_sector_from_flash();

/**
 * @brief Switch to the next flash memory sector.
 *
 * @param currentSector The address of the current flash memory sector.
 * @return The address of the next flash memory sector.
 */
uint32_t switch_to_next_sector(uint32_t current_sector);

/**
 * @brief Read and send time data from flash memory via UART.
 */
void flash_read_and_send_uart();


//------------------------------------------------------------------------------------------

/**
 * @brief Load password data from flash memory.
 */
void flash_load_password();

/**
 * @brief Count the number of passwords stored in a flash memory sector.
 *
 * @param sectorAddress The address of the flash memory sector.
 * @return The count of passwords in the sector.
 */
size_t count_password_in_sector(uint32_t sector_address);

/**
 * @brief Save password data to flash memory.
 *
 * @param passwordData Pointer to the password data to be saved.
 */
void save_password_to_flash(uint8_t* passwordData);

/**
 * @brief Read password data from flash memory.
 *
 * @param passwordData Pointer to the password data where data will be stored.
 * @param index The index of the password data to read.
 */
void read_password_from_flash(uint8_t* passwordData, size_t index);

/**
 * @brief Check if the entered password matches the stored password.
 *
 * @param enteredPassword Pointer to the entered password.
 * @return true if the entered password matches the stored password, otherwise false.
 */
bool check_password(uint8_t* enteredPassword);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* LIBRARY_API_INC_API_FLASH_H_ */
/* End of file -------------------------------------------------------------- */
