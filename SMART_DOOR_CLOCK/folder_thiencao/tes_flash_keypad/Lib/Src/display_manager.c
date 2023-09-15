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
#include "display_manager.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */


/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */


/* Private variables -------------------------------------------------- */


/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void display_init(	I2C_HandleTypeDef *hi2c, keypad_name *keypad,
					GPIO_TypeDef *COL1_PORT, uint32_t COL1_PIN,
					GPIO_TypeDef *COL2_PORT, uint32_t COL2_PIN,
					GPIO_TypeDef *COL3_PORT, uint32_t COL3_PIN,
					GPIO_TypeDef *ROW1_PORT, uint32_t ROW1_PIN,
					GPIO_TypeDef *ROW2_PORT, uint32_t ROW2_PIN,
					GPIO_TypeDef *ROW3_PORT, uint32_t ROW3_PIN,
					GPIO_TypeDef *ROW4_PORT, uint32_t ROW4_PIN) {

	lcd_init(hi2c);
	keypad3x4_init(	keypad, COL1_PORT, COL1_PIN, COL2_PORT, COL2_PIN,
							COL3_PORT, COL3_PIN, ROW1_PORT, ROW1_PIN,
							ROW2_PORT, ROW2_PIN, ROW3_PORT, ROW3_PIN,
							ROW4_PORT, ROW4_PIN);
}
void display() {
	static uint32_t time;
	if (HAL_GetTick() - time >= 500) {
		lcd_goto_xy(0,4);

		lcd_send_string("WELCOME");
		lcd_goto_xy(1,3);
		lcd_send_string("SMART DOOR");
		HAL_Delay(500);
	//	lcd_clear();
	//	lcd_clear();
		time = HAL_GetTick();
	}
}
void display_handle(keypad_name *keypad) {
	keypad_handler(keypad);
	display();
}
/* End of file -------------------------------------------------------- */


