/**
 * @file       bsp_uart.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2023-08-27
 * @author     khoa vo
 * @brief      BSP for UART
 * @note       None
 * @example    None
 */

/* Public includes ---------------------------------------------------------- */
#include "bsp_uart.h"

/* Private includes --------------------------------------------------------- */
/* Private defines ---------------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------------- */
/* Private macros ----------------------------------------------------------- */

/* Public variables --------------------------------------------------------- */
UART_HandleTypeDef *_pc_huart;

/* Private variables -------------------------------------------------------- */

/* Public implementations --------------------------------------------------- */

bool bsp_uart_transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	if (HAL_UART_Transmit(huart, pData, Size, Timeout) != HAL_OK)
		return false;
	else
		return true;
}


bool bsp_uart_receive_it(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
	if (HAL_UART_Receive_IT(huart, pData, Size) != HAL_OK)
		return false;
	else
		return true;
}

//HAL_UART_TxCpltCallback
/* End of file -------------------------------------------------------------- */

