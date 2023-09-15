/**
 * @file       bsp_gpio.c
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
#include "bsp_gpio.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void bsp_gpio_set_pin(GPIO_TypeDef *bsp_gpio_port, uint16_t bsp_gpio_pin){
	HAL_GPIO_WritePin(bsp_gpio_port, bsp_gpio_pin, GPIO_PIN_SET);
}
void bsp_gpio_reset_pin(GPIO_TypeDef *bsp_gpio_port, uint16_t bsp_gpio_pin){
	HAL_GPIO_WritePin(bsp_gpio_port, bsp_gpio_pin, GPIO_PIN_RESET);
}
void bsp_gpio_toggle_pin(GPIO_TypeDef *bsp_gpio_port, uint16_t bsp_gpio_pin){
	HAL_GPIO_TogglePin(bsp_gpio_port, bsp_gpio_pin);
}
GPIO_PinState bsp_gpio_read_pin(GPIO_TypeDef *bsp_gpio_port, uint16_t bsp_gpio_pin){
	return HAL_GPIO_ReadPin(bsp_gpio_port, bsp_gpio_pin);
}
/* End of file -------------------------------------------------------- */
