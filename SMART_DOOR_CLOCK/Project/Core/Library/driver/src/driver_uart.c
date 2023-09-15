/**
 * @file       driver_uart.c
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     <first_name_1> <last_name_1>
 * @author     <first_name_2> <last_name_2>
 *
 * @brief      driver uart file
 */
/* Includes ----------------------------------------------------------- */
#include "driver_uart.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
void uart_init(UART_HandleTypeDef *huart)
{
	_pc_huart = huart;
}

bool uart_transmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	return bsp_uart_transmit(_pc_huart, pData, Size, Timeout);
}

bool uart_receive_it(uint8_t *pData, uint16_t Size)
{
	return bsp_uart_receive_it(_pc_huart, pData, Size);
}

/* End of file -------------------------------------------------------- */
