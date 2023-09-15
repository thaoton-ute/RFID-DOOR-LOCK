/**
 * @file       <file_name>.c
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
#include "api_keypad.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
uint16_t count1 = 0;
uint16_t count2 = 0;
uint16_t count3 = 0;
/* Function definitions ----------------------------------------------- */
void api_keypad_init(keypad_name *keypad,
					 GPIO_TypeDef *COL1_PORT, uint32_t COL1_PIN,
					 GPIO_TypeDef *COL2_PORT, uint32_t COL2_PIN,
					 GPIO_TypeDef *COL3_PORT, uint32_t COL3_PIN,
					 GPIO_TypeDef *ROW1_PORT, uint32_t ROW1_PIN,
					 GPIO_TypeDef *ROW2_PORT, uint32_t ROW2_PIN,
					 GPIO_TypeDef *ROW3_PORT, uint32_t ROW3_PIN,
					 GPIO_TypeDef *ROW4_PORT, uint32_t ROW4_PIN){
	keypad3x4_init(	keypad, COL1_PORT, COL1_PIN, COL2_PORT, COL2_PIN,
							COL3_PORT, COL3_PIN, ROW1_PORT, ROW1_PIN,
							ROW2_PORT, ROW2_PIN, ROW3_PORT, ROW3_PIN,
							ROW4_PORT, ROW4_PIN);
}

uint8_t api_check_button(keypad_name *keypad, uint8_t key_check){
	if (keypad->keychar == key_check) { //key char is the var save the key button
		keypad->keychar = 0;
		return 1;
	}
	return 0;
}
uint8_t api_check_have_button(keypad_name *keypad) {
	keypad_handler(keypad);
	if (keypad->press_flag) {
		keypad->press_flag = 0;
		return 1;
	}
	return 0;
}

uint8_t api_check_have_button_timeout(keypad_name *keypad, uint32_t time_out) {
	uint32_t time_current = HAL_GetTick();
	while (HAL_GetTick() - time_current < time_out) {
		keypad_handler(keypad);
		if(keypad->press_flag){
			keypad->press_flag = 0;
			return 1;
		}
	}
	return 0;
}

uint8_t api_check_button_timeout(keypad_name *keypad, uint8_t key_check, uint32_t time_out) {
	uint32_t time_current = HAL_GetTick();
	while (HAL_GetTick() - time_current < time_out) {
		keypad_handler(keypad);
		if(keypad->keychar == key_check){
			keypad->keychar = 0;
			return 1;
		}
	}
	return 0;
}

uint8_t api_enter_pass(keypad_name *keypad, uint8_t pass[]) {
	static uint8_t index_display_lcd = 5;
	static uint8_t index_pass = 0;
	lcd_goto_xy(0, 1);
	lcd_send_string("ENTER PASSWORD");
	while (api_check_have_button_timeout(keypad, 10000)) {
		lcd_goto_xy(1, index_display_lcd);
		if (keypad->keychar <= '9' && keypad->keychar >= '0') {
			pass[index_pass++] = keypad->keychar;
			lcd_send_data(keypad->keychar);
			HAL_Delay(200);
			lcd_goto_xy(1, index_display_lcd);
			lcd_send_data('*');
			index_display_lcd++;
		} else {
			for (uint8_t i = 0; i < 4; i++) {
				lcd_goto_xy(1, 3);
				lcd_send_string("Enter num 0-9");
				HAL_Delay(500);
				lcd_goto_xy(1, 3);
				lcd_send_string("             ");
				HAL_Delay(500);
			}
			lcd_goto_xy(1, 5);
			if (index_pass == 1) {
				lcd_send_string("*");
			} else if (index_pass == 2) {
				lcd_send_string("**");
			} else if (index_pass == 3) {
				lcd_send_string("***");
			}
		}
		if (index_pass == 4) {
			index_pass = 0;
			index_display_lcd = 5;
			return 1;
		}
	}
	return 0;
}


/* End of file -------------------------------------------------------- */


