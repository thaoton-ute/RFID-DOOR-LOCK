/**
 * @file       bsp_i2c.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2023-08-27
 * @author     khoa vo
 * @brief      BSP for I2C
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef INC_BSP_I2C_H_
#define INC_BSP_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "stm32f4xx_hal.h"
#include <stdbool.h>

/* Public defines ----------------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------------- */

/* Public macros ------------------------------------------------------------ */
/* Public variables --------------------------------------------------------- */
extern I2C_HandleTypeDef *_ds1307_ui2c;

/* Public APIs -------------------------------------------------------------- */
/**
  * @brief  	Transmits in master mode an amount of data in blocking mode.
  * @param  	hi2c 		Pointer to a I2C_HandleTypeDef structure that contains
  *             			the configuration information for the specified I2C.
  * @param  	DevAddress 	Target device address: The device 7 bits address value
  *         				in datasheet must be shifted to the left before calling the interface
  * @param  	pData 		Pointer to data buffer
  * @param  	Size 		Amount of data to be sent
  * @param  	Timeout 	Timeout duration
  * @retval 	true/false
  */
bool bsp_i2C_master_transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/**
  * @brief  	Receives in master mode an amount of data in blocking mode.
  * @param  	hi2c 		Pointer to a I2C_HandleTypeDef structure that contains
  *                			the configuration information for the specified I2C.
  * @param  	DevAddress 	Target device address: The device 7 bits address value
  *         				in datasheet must be shifted to the left before calling the interface
  * @param  	pData 		Pointer to data buffer
  * @param  	Size 		Amount of data to be sent
  * @param  	Timeout 	Timeout duration
  * @retval 	true/false
  */
bool bsp_i2c_master_receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* INC_BSP_I2C_H_ */

/* End of file -------------------------------------------------------------- */
