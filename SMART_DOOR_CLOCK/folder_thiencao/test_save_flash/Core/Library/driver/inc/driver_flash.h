/**
 * @file       flash.h
 * @brief      Header file for Flash memory operations
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.1
 * @date       2023-08-25
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

/* Includes ----------------------------------------------------------- */
#include <stdint.h>
#include <string.h>
#include "bsp_flash.h"
/* Public defines ----------------------------------------------------- */
#define MAX_COLS 6

/* Public enumerate/structure ----------------------------------------- */

#pragma pack(1)
typedef struct
{
    uint8_t no;
    uint8_t ssid[30];
    uint8_t pass[30];
} wifi_info_t;
#pragma pack()

/* Public function prototypes ----------------------------------------- */

/**
 * @brief Erase a sector of Flash memory.
 * @param address: Start address of the sector to be erased
 * @return None
 */
void flash_erase_sector2(uint32_t address);

/**
 * @brief Write an integer value to Flash memory.
 * @param address: Address where the integer will be written
 * @param value: Integer value to be written
 * @return None
 */
void flash_write_int(uint32_t address, int value);

/**
 * @brief Write a float value to Flash memory.
 * @param address: Address where the float will be written
 * @param f: Float value to be written
 * @return None
 */
void flash_write_float(uint32_t address, float f);

/**
 * @brief Write an array of bytes to Flash memory.
 * @param address: Start address where the array will be written
 * @param arr: Pointer to the array of bytes
 * @param len: Length of the array
 * @return None
 */
void flash_write_array(uint32_t address, uint8_t *arr, uint16_t len);

/**
 * @brief Write a structure to Flash memory.
 * @param address: Address where the structure will be written
 * @param dta: Structure to be written
 * @return None
 */
void flash_write_struct(uint32_t address, wifi_info_t dta);

/**
 * @brief Read an integer value from Flash memory.
 * @param address: Address to read the integer value from
 * @return Read integer value
 */
int flash_read_int(uint32_t address);

/**
 * @brief Read a float value from Flash memory.
 * @param address: Address to read the float value from
 * @return Read float value
 */
float flash_read_float(uint32_t address);

/**
 * @brief Read an array of bytes from Flash memory.
 * @param address: Address to start reading the array from
 * @param arr: Pointer to store the read array
 * @param len: Length of the array to read
 * @return None
 */
void flash_read_array(uint32_t address, uint8_t *arr, uint16_t len);

/**
 * @brief Read a structure from Flash memory.
 * @param address: Address to read the structure from
 * @param dta: Pointer to store the read structure
 * @return None
 */
void flash_read_struct(uint32_t address ,wifi_info_t *dta);

/**
 * @brief Write a 2D array to Flash memory.
 *
 * This function writes a 2D array to a specified address in Flash memory.
 *
 * @param address: Address in Flash memory where the 2D array will be written to.
 * @param arr: Pointer to the 2D array containing the data to be written.
 * @param rows: Number of rows in the 2D array.
 * @param cols: Number of columns in the 2D array.
 */
void flash_write_2d_array(uint32_t address, uint8_t arr[][MAX_COLS], uint16_t rows, uint16_t cols);

/**
 * @brief Read a structure from Flash memory.
 *
 * This function reads a structure from a specified address in Flash memory and
 * stores it in the provided structure pointer.
 *
 * @param address: Address in Flash memory to read the structure from.
 * @param dta: Pointer to the structure where the read data will be stored.
 */
void flash_read_struct(uint32_t address, wifi_info_t *dta);

/**
 * @brief Write a 2D array to Flash memory.
 *
 * This function writes a 2D array to a specified address in Flash memory.
 *
 * @param address: Address in Flash memory where the 2D array will be written to.
 * @param arr: Pointer to the 2D array containing the data to be written.
 * @param rows: Number of rows in the 2D array.
 * @param cols: Number of columns in the 2D array.
 */
void flash_write_2d_array(uint32_t address, uint8_t arr[][MAX_COLS], uint16_t rows, uint16_t cols);

/**
 * @brief Read a 2D array from Flash memory.
 *
 * This function reads a 2D array from a specified address in Flash memory and stores
 * it in the provided 2D array.
 *
 * @param address: Address in Flash memory to read the 2D array from.
 * @param arr: Pointer to the 2D array where the read data will be stored.
 * @param rows: Number of rows in the 2D array.
 * @param cols: Number of columns in the 2D array.
 */
void flash_read_2d_array(uint32_t address, uint8_t arr[][MAX_COLS], uint16_t rows, uint16_t cols);

#endif /* INC_FLASH_H_ */

/* End of file -------------------------------------------------------- */
