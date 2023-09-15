
/**
 * @file       ic2-lcd.h
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     thien cao
 * @author     thien cao
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example    example_file_1.c
 *             Example_1 description
 * @example    example_file_2.c
 *             Example_2 description
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __I2C_LCD_H
#define __I2C_LCD_H

/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"
#include "bsp_i2c.h"

/* Public defines ----------------------------------------------------- */
#define SLAVE_ADDRESS_LCD 0x27 /*!< I2C address of the LCD module */

/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief Initialize the LCD module over I2C communication.
 *
 * This function initializes the LCD module over I2C communication.
 *
 * @param[in] hi2c Pointer to the I2C handle structure.
 */
void lcd_init(I2C_HandleTypeDef *hi2c);

/**
 * @brief Send command to the LCD module.
 *
 * This function sends a command to the LCD module.
 *
 * @param[in] cmd The command to be sent to the LCD module.
 */
void lcd_send_cmd(char cmd);

/**
 * @brief Send data to the LCD module.
 *
 * This function sends data to the LCD module.
 *
 * @param[in] data The data to be sent to the LCD module.
 */
void lcd_send_data(char data);

/**
 * @brief Clear the LCD module display.
 */
void lcd_clear(void);

/**
 * @brief Set the cursor position on the LCD module display.
 *
 * @param[in] row The row where the cursor should be placed (0 or 1).
 * @param[in] col The column where the cursor should be placed (0-15).
 */
void lcd_goto_xy(int row, int col);

/**
 * @brief Send a string to the LCD module for display.
 *
 * @param[in] str The string to be displayed on the LCD module.
 */
void lcd_send_string(char *str);

/**
 * @brief Display a string on the LCD module at the specified row and column.
 *
 * @param[in] row The row where the string should be displayed (0 or 1 for a 2-line LCD).
 * @param[in] col The column where the string should start displaying (0-15 for a 16-character wide LCD).
 * @param[in] str The string to be displayed on the LCD module.
 */
void lcd_display(int row, int col, char *str);

#endif // __I2C_LCD_H

/* End of file -------------------------------------------------------- */
