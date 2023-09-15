/*
 * pc_uart.h
 *
 *  Created on: Aug 29, 2023
 *      Author: Admin
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "bsp_uart.h"

void uart_init(UART_HandleTypeDef *huart)
{
	_pc_huart = huart;
}

bool uart_transmit_it(const uint8_t *pData, uint16_t Size)
{
	return bsp_uart_transmit_it(_pc_huart, pData, Size);
}

bool uart_receive_it(uint8_t *pData, uint16_t Size)
{
	return bsp_uart_receive_it(_pc_huart, pData, Size);
}



#endif /* INC_UART_H_ */
