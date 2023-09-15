/**
 * @file       api_keypad..h
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

#ifndef LIBRARY_API_INC_API_KEYPAD_H_
#define LIBRARY_API_INC_API_KEYPAD_H_


/* Includes ----------------------------------------------------------- */
#include "driver_i2c_lcd.h"
#include "driver_keypad.h"

#include "stm32f4xx_hal.h"
/* Public defines ----------------------------------------------------- */
#define  TIMEOUT		10000 	/*TIMEOUT 10000 ms = 10 s*/
/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/**
 * @brief Initializes a keypad with the specified GPIO pins for rows and columns.
 *
 * @param[in] keypad      Pointer to the keypad structure.
 * @param[in] COL1_PORT   GPIO port for column 1.
 * @param[in] COL1_PIN    GPIO pin for column 1.
 * @param[in] COL2_PORT   GPIO port for column 2.
 * @param[in] COL2_PIN    GPIO pin for column 2.
 * @param[in] COL3_PORT   GPIO port for column 3.
 * @param[in] COL3_PIN    GPIO pin for column 3.
 * @param[in] ROW1_PORT   GPIO port for row 1.
 * @param[in] ROW1_PIN    GPIO pin for row 1.
 * @param[in] ROW2_PORT   GPIO port for row 2.
 * @param[in] ROW2_PIN    GPIO pin for row 2.
 * @param[in] ROW3_PORT   GPIO port for row 3.
 * @param[in] ROW3_PIN    GPIO pin for row 3.
 * @param[in] ROW4_PORT   GPIO port for row 4.
 * @param[in] ROW4_PIN    GPIO pin for row 4.
 */
void api_keypad_init(keypad_name *keypad,
					 GPIO_TypeDef *COL1_PORT, uint32_t COL1_PIN,
					 GPIO_TypeDef *COL2_PORT, uint32_t COL2_PIN,
					 GPIO_TypeDef *COL3_PORT, uint32_t COL3_PIN,
					 GPIO_TypeDef *ROW1_PORT, uint32_t ROW1_PIN,
					 GPIO_TypeDef *ROW2_PORT, uint32_t ROW2_PIN,
					 GPIO_TypeDef *ROW3_PORT, uint32_t ROW3_PIN,
					 GPIO_TypeDef *ROW4_PORT, uint32_t ROW4_PIN);

/**
 * @brief Checks if a specific key is pressed and clears the key character.
 *
 * @param[in] keypad     Pointer to the keypad structure.
 * @param[in] key_check  The key to check.
 *
 * @return 1 if the specified key is pressed, 0 otherwise.
 */
uint8_t api_check_button(keypad_name *keypad, uint8_t key_check);

/**
 * @brief Checks if any key is currently pressed and clears the press flag.
 *
 * @param[in] keypad  Pointer to the keypad structure.
 *
 * @return 1 if any key is currently pressed, 0 otherwise.
 */
uint8_t api_check_have_button(keypad_name *keypad);
/**
 * @brief Checks if any key is pressed within a specified timeout period.
 *
 * @param[in] keypad    Pointer to the keypad structure.
 * @param[in] time_out  The timeout duration in milliseconds.
 *
 * @return 1 if any key is pressed within the timeout, 0 otherwise.
 */
uint8_t api_check_button_timeout(keypad_name *keypad, uint8_t key_check, uint32_t time_out);

/**
 * @brief Checks if a specific key is pressed within a specified timeout period and clears the key character.
 *
 * @param[in] keypad     Pointer to the keypad structure.
 * @param[in] key_check  The key to check.
 * @param[in] time_out   The timeout duration in milliseconds.
 *
 * @return 1 if the specified key is pressed within the timeout, 0 otherwise.
 */
uint8_t api_check_have_button_timeout(keypad_name *keypad, uint32_t time_out);

/**
 * @brief Allows the user to enter a password using the keypad and displays it on an LCD screen.
 *
 * @param[in] keypad  Pointer to the keypad structure.
 * @param[in] pass    The array to store the entered password.
 *
 * @return 1 if a complete 4-digit password is entered.
 * @return 0 if timeout
 */
uint8_t api_enter_pass(keypad_name *keypad, uint8_t pass[]);
#endif /* LIBRARY_API_INC_API_KEYPAD_H_ */
/* End of file -------------------------------------------------------- */


