/**
 * @file       bsp_gpio.h
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
#ifndef INC_BSP_GPIO_H_
#define INC_BSP_GPIO_H_
/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"
/* Public defines ----------------------------------------------------- */


/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */


/* Public function prototypes ----------------------------------------- */

/**
 * @brief bsp_gpio_set_pin
 *
 * This function set pin gpio
 *
 * @param bsp_gpio_port     gpio port
 * @param bsp_gpio_pin      gpio pin
 *
 * @return
 */
void bsp_gpio_set_pin(GPIO_TypeDef *bsp_gpio_port, uint16_t bsp_gpio_pin);

/**
 * @brief bsp_gpio_reset_pin
 *
 * This function reset pin gpio
 *
 * @param bsp_gpio_port     gpio port
 * @param bsp_gpio_pin      gpio pin
 *
 * @return
 */
void bsp_gpio_reset_pin(GPIO_TypeDef *bsp_gpio_port, uint16_t bsp_gpio_pin);

/**
 * @brief bsp_gpio_toggle_pin
 *
 * This function reset pin gpio
 *
 * @param bsp_gpio_port     gpio port
 * @param bsp_gpio_pin      gpio pin
 *
 * @return
 */
void bsp_gpio_toggle_pin(GPIO_TypeDef *bsp_gpio_port, uint16_t bsp_gpio_pin);

/**
 * @brief bsp_gpio_read_pin
 *
 * This function read pin gpio
 *
 * @param bsp_gpio_port     gpio port
 * @param bsp_gpio_pin      gpio pin
 *
 * @return	GPIO_PIN_RESET
 * 			GPIO_PIN_SET
 */
GPIO_PinState bsp_gpio_read_pin(GPIO_TypeDef *bsp_gpio_port, uint16_t bsp_gpio_pin);
#endif /* INC_BSP_GPIO_H_ */

/* End of file -------------------------------------------------------- */
