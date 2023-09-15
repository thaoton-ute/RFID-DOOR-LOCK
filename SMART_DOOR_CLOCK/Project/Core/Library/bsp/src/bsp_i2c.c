/**
 * @file       bsp_i2c.c
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     thien cao
 * @author     thien cao
 *
 * @brief      bsp for i2c
 *
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_i2c.h"

/* Private defines ---------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint8_t bsp_i2c_scan_address(BSP_I2C_Handle *i2c_handle)
{
	uint8_t i2c_address = 0;
	for (i2c_address = 0; i2c_address < 128; i2c_address++)
	{
		if (HAL_I2C_IsDeviceReady(i2c_handle->hi2c, i2c_address << 1, 3, 100) == HAL_OK)
		{
			return i2c_address;
		}
	}
	return 0;
}

void bsp_i2c_init(BSP_I2C_Handle *i2c_handle, I2C_HandleTypeDef *hi2c)
{
	i2c_handle->hi2c = hi2c;
}


BSP_I2C_Status bsp_i2c_transmit(BSP_I2C_Handle *i2c_handle, uint16_t dev_address,
		uint8_t *data, uint16_t size)
{
	if (HAL_I2C_Master_Transmit(i2c_handle->hi2c, dev_address << 1, data, size,
			HAL_MAX_DELAY) != HAL_OK)
	{
		return BSP_I2C_ERROR;
	}
	return BSP_I2C_OK;
}

/* End of file -------------------------------------------------------- */
