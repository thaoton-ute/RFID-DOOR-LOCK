/**
 * @file       pc_uart.h
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       2023-08-09
 * @author     <first_name_1> <last_name_1>
 * @author     <first_name_2> <last_name_2>
 *
 * @brief      driver uart
 *
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_UART_H_
#define INC_UART_H_

/* Includes ----------------------------------------------------------- */
#include "bsp_uart.h"

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/**
 * @brief Initializes the UART communication with the specified UART handle.
 * @param huart: Pointer to the UART handle.
 */
void uart_init(UART_HandleTypeDef *huart);

/**
 * @brief Transmits data over UART with a specified timeout.
 * @param pData: Pointer to the data buffer to be transmitted.
 * @param Size: Size of the data to be transmitted.
 * @param Timeout: Timeout duration (in milliseconds) for the transmission.
 * @return true if the transmission is successful, false otherwise.
 */
bool uart_transmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout);

/**
 * @brief Receives data over UART using interrupt-driven communication.
 * @param pData: Pointer to the data buffer to store the received data.
 * @param Size: Size of the data to be received.
 * @return true if the data is received successfully, false otherwise.
 */
bool uart_receive_it(uint8_t *pData, uint16_t Size);

#endif /* INC_UART_H_ */

/* End of file -------------------------------------------------------- */
