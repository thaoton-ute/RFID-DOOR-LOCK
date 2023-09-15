/**
 * @file       <file_name>.h
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     <first_name_1> <last_name_1>
 * @author     <first_name_2> <last_name_2>
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
#ifndef INC_DISPLAY_MANAGER_H_
#define INC_DISPLAY_MANAGER_H_

/* Includes ----------------------------------------------------------- */
#include "i2c-lcd.h"
#include "keypad.h"
#include "password.h"
#include "stm32f1xx_hal.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
typedef enum {
	MODE0_DISPLAY_TIMER,
	MODE1_INSERT_PASSWORD,
	MODE2_CHANGE_PASSWORD
}state_lcd;
/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief Initializes the display module using the provided I2C handler.
 *
 * This function initializes the LCD display module using the provided I2C
 * handler for communication. It internally calls the lcd_init() function.
 *
 * @param[in] hi2c Pointer to the I2C handler used for communication.
 */
void display_init(	I2C_HandleTypeDef *hi2c, keypad_name *keypad,
					GPIO_TypeDef *COL1_PORT, uint32_t COL1_PIN,
					GPIO_TypeDef *COL2_PORT, uint32_t COL2_PIN,
					GPIO_TypeDef *COL3_PORT, uint32_t COL3_PIN,
					GPIO_TypeDef *ROW1_PORT, uint32_t ROW1_PIN,
					GPIO_TypeDef *ROW2_PORT, uint32_t ROW2_PIN,
					GPIO_TypeDef *ROW3_PORT, uint32_t ROW3_PIN,
					GPIO_TypeDef *ROW4_PORT, uint32_t ROW4_PIN);
void display_handle(keypad_name *keypad);
void display();
#endif /* INC_DISPLAY_MANAGER_H_ */

/* End of file -------------------------------------------------------- */
