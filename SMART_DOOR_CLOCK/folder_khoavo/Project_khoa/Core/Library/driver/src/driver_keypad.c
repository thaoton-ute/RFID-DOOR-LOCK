/**
 * @file       keypad.c
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

/* Includes ----------------------------------------------------------- */
#include "driver_keypad.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
const uint8_t key_code[KEYPAD_ROW][KEYPAD_COL] =
{
		{'#','0','*'},
		{'9','8','7'},
		{'6','5','4'},
		{'3','2','1'},
};
uint32_t keypad_start_pressing = 0;
uint8_t keypad_is_press = 0;
/* Private function prototypes ---------------------------------------- */
/**
 * @brief Selects a specific row of the keypad for scanning.
 *
 * This function selects the specified row of the keypad for scanning by pulling
 * the corresponding row pin low.
 *
 * @param[in] keypad Pointer to the keypad_name structure.
 * @param[in] row The index of the row to select (0 to KEYPAD_ROW - 1).
 */
static void keypad_select_row(keypad_name* keypad, uint8_t row);

/**
 * @brief Unselects all rows of the keypad after scanning.
 *
 * This function unselects all rows of the keypad after scanning by releasing
 * all row pins (setting them to high).
 *
 * @param[in] keypad Pointer to the keypad_name structure.
 */
static void keypad_unselect_row(keypad_name* keypad);

/* Function definitions ----------------------------------------------- */

void keypad3x4_init(keypad_name* keypad, GPIO_TypeDef* COL0_PORT, uint32_t COL0_PIN,
										 GPIO_TypeDef* COL1_PORT, uint32_t COL1_PIN,
										 GPIO_TypeDef* COL2_PORT, uint32_t COL2_PIN,
										 GPIO_TypeDef* ROW0_PORT, uint32_t ROW0_PIN,
										 GPIO_TypeDef* ROW1_PORT, uint32_t ROW1_PIN,
										 GPIO_TypeDef* ROW2_PORT, uint32_t ROW2_PIN,
										 GPIO_TypeDef* ROW3_PORT, uint32_t ROW3_PIN)
{
	keypad->col_port[0] = COL0_PORT;
	keypad->col_pins[0] = COL0_PIN;
	keypad->col_port[1] = COL1_PORT;
	keypad->col_pins[1] = COL1_PIN;
	keypad->col_port[2] = COL2_PORT;
	keypad->col_pins[2] = COL2_PIN;

	keypad->row_port[0] = ROW0_PORT;
	keypad->row_pins[0] = ROW0_PIN;
	keypad->row_port[1] = ROW1_PORT;
	keypad->row_pins[1] = ROW1_PIN;
	keypad->row_port[2] = ROW2_PORT;
	keypad->row_pins[2] = ROW2_PIN;
	keypad->row_port[3] = ROW3_PORT;
	keypad->row_pins[3] = ROW3_PIN;

	keypad->key_current_status = 0;
	keypad->key_debouce_time = 0;
	keypad->key_debounce_status = 0;
	keypad->key_is_debouncing = 0;
	keypad->key_last_status = 0;
}
static void keypad_select_row(keypad_name* keypad, uint8_t row){
	bsp_gpio_reset_pin(keypad->row_port[row], keypad->row_pins[row]);
}
static void keypad_unselect_row(keypad_name* keypad){
	for (uint8_t row = 0; row < KEYPAD_ROW; row++){
		bsp_gpio_set_pin(keypad->row_port[row], keypad->row_pins[row]);
	}
}
uint8_t keypad_getkey(keypad_name* keypad){
	for (uint8_t row = 0; row < KEYPAD_ROW; row++){
		keypad_unselect_row(keypad);
		keypad_select_row(keypad, row);
		for (uint8_t col = 0; col < KEYPAD_COL; col++){
			if(!bsp_gpio_read_pin(keypad->col_port[col], keypad->col_pins[col])){
				return key_code[row][col];
			}
		}
	}
	return 0;
}
void keypad_filter(keypad_name* keypad){
	uint8_t key = keypad_getkey(keypad); // get the key status
	// state handle filter
	if(key != keypad->key_debounce_status){
		keypad->key_is_debouncing = 1;
		keypad->key_debouce_time = HAL_GetTick();
		keypad->key_debounce_status = key;
	}
	// finish filter
	if(keypad->key_is_debouncing && (HAL_GetTick() - keypad->key_debouce_time >= 50)){
		keypad->key_current_status = keypad->key_debounce_status;
		keypad->key_is_debouncing = 0;
	}
}
void keypad_handler(keypad_name* keypad){
	keypad_filter(keypad);
	if(keypad->key_current_status != keypad->key_last_status){
		if(keypad->key_current_status != 0){ // button is switch
			keypad_is_press = 1;
			keypad_start_pressing = HAL_GetTick();
			keypad_press_callback(keypad->key_current_status);
		}
		else{
			keypad_is_press = 0;
			keypad_release_callback(keypad->key_last_status);
		}
		keypad->key_last_status = keypad->key_current_status;
	}
	if(keypad_is_press && HAL_GetTick() - keypad_start_pressing > 2000){
		keypad_hold_callback(keypad->key_current_status);
		keypad_is_press = 0;
	}
}
/* End of file -------------------------------------------------------- */
