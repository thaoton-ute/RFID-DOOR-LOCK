/**
 * @file       bsp_i2c.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2023-08-27
 * @author     khoa vo
 * @brief      BSP for I2C
 * @note       None
 * @example    None
 */

/* Public includes ---------------------------------------------------------- */
#include "bsp_i2c_1.h"

/* Private includes --------------------------------------------------------- */
/* Private defines ---------------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------------- */
/* Private macros ----------------------------------------------------------- */

/* Public variables --------------------------------------------------------- */
I2C_HandleTypeDef *_ds1307_ui2c;

/* Private variables -------------------------------------------------------- */

/* Public implementations --------------------------------------------------- */

bool bsp_i2C_master_transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	if (HAL_I2C_Master_Transmit(hi2c, DevAddress, pData, Size, Timeout) != HAL_OK)
		return false;
	else
		return true;
}

bool bsp_i2c_master_receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	if (HAL_I2C_Master_Receive(hi2c, DevAddress, pData, Size, Timeout) != HAL_OK)
		return false;
	else
		return true;
}
