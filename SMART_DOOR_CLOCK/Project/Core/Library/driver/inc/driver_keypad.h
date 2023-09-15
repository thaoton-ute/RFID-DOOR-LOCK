/**
 * @file       keypad.h
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
#ifndef INC_API_KEYPAD_H_
#define INC_API_KEYPAD_H_

/* Includes ----------------------------------------------------------- */
#include "bsp_gpio.h"

/* Public defines ----------------------------------------------------- */
#define KEYPAD_ROW		4		/*!Number of rows in the keypad matrix*/
#define KEYPAD_COL  	3		/*!Number of columns in the keypad matrix */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief Structure representing a keypad.
 */
typedef struct
{
	uint32_t row_pins[KEYPAD_ROW];
	uint32_t col_pins[KEYPAD_COL];
	GPIO_TypeDef* row_port[KEYPAD_ROW];
	GPIO_TypeDef* col_port[KEYPAD_COL];
	uint8_t key_debounce_status;
	uint8_t key_is_debouncing;
	uint32_t key_debouce_time;
	uint8_t key_current_status;
	uint8_t key_last_status;
	uint8_t keychar;
	uint8_t press_flag;
}keypad_name;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/**
 * @brief Initializes the 3x4 keypad module with specified pins and ports.
 *
 * This function initializes the keypad module with the provided GPIO pins
 * and ports for the columns and rows of the keypad.
 *
 * @param[in] keypad Pointer to the keypad_name structure.
 * @param[in] COL0_PORT GPIO port for column 0.
 * @param[in] COL0_PIN GPIO pin for column 0.
 * @param[in] COL1_PORT GPIO port for column 1.
 * @param[in] COL1_PIN GPIO pin for column 1.
 * @param[in] COL2_PORT GPIO port for column 2.
 * @param[in] COL2_PIN GPIO pin for column 2.
 * @param[in] ROW0_PORT GPIO port for row 0.
 * @param[in] ROW0_PIN GPIO pin for row 0.
 * @param[in] ROW1_PORT GPIO port for row 1.
 * @param[in] ROW1_PIN GPIO pin for row 1.
 * @param[in] ROW2_PORT GPIO port for row 2.
 * @param[in] ROW2_PIN GPIO pin for row 2.
 * @param[in] ROW3_PORT GPIO port for row 3.
 * @param[in] ROW3_PIN GPIO pin for row 3.
 *
 * @note The GPIO ports and pins for columns and rows must be properly configured
 * before calling this function.
 */
void keypad3x4_init(keypad_name* keypad, GPIO_TypeDef* COL1_PORT, uint32_t COL1_PIN,
										 GPIO_TypeDef* COL2_PORT, uint32_t COL2_PIN,
										 GPIO_TypeDef* COL3_PORT, uint32_t COL3_PIN,
										 GPIO_TypeDef* ROW1_PORT, uint32_t ROW1_PIN,
										 GPIO_TypeDef* ROW2_PORT, uint32_t ROW2_PIN,
										 GPIO_TypeDef* ROW3_PORT, uint32_t ROW3_PIN,
										 GPIO_TypeDef* ROW4_PORT, uint32_t ROW4_PIN);
/**
 * @brief Gets the key value from the pressed key on the keypad.
 *
 * This function scans the keypad and returns the value of the key that is
 * currently pressed. It uses the keypad_name structure to control the scanning
 * process and determine the pressed key's value.
 *
 * @param[in] keypad Pointer to the keypad_name structure.
 * @return The ASCII value of the pressed key, or 0 if no key is pressed.
 */
uint8_t keypad_getkey(keypad_name* keypad);

/**
 * @brief Applies debouncing and filtering to the keypad input.
 *
 * This function applies debouncing and filtering to the keypad input. It is used
 * internally within the keypad module to ensure accurate and reliable detection
 * of key presses and releases.
 *
 * @param[in] keypad Pointer to the keypad_name structure.
 */
void keypad_filter(keypad_name* keypad);

/**
 * @brief Handles the keypad input and triggers callbacks for different events.
 *
 * This function continuously monitors the keypad input using debounced and filtered
 * values. It triggers the appropriate callbacks for key press, release, and hold
 * events based on the detected changes in key status.
 *
 * @param[in] keypad Pointer to the keypad_name structure.
 */
void keypad_handler(keypad_name* keypad);

/**
 * @brief Callback function for when a key is pressed.
 *
 * This callback function is triggered when a key press event is detected by the
 * keypad_handler function. The key parameter represents the ASCII value of the
 * pressed key.
 *
 * @param[in] key The ASCII value of the pressed key.
 */
void keypad_press_callback(uint8_t key);

/**
 * @brief Callback function for when a key is released.
 *
 * This callback function is triggered when a key release event is detected by the
 * keypad_handler function. The key parameter represents the ASCII value of the
 * released key.
 *
 * @param[in] key The ASCII value of the released key.
 */
void keypad_release_callback(uint8_t key);

/**
 * @brief Callback function for when a key is held down.
 *
 * This callback function is triggered when a key hold event is detected by the
 * keypad_handler function. The key parameter represents the ASCII value of the
 * held key.
 *
 * @param[in] key The ASCII value of the held key.
 */
void keypad_hold_callback(uint8_t key);
#endif /* INC_API_KEYPAD_H_ */

/* End of file -------------------------------------------------------- */
