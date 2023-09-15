/**
 * @file       bsp_spi.h
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.1
 * @date       2023-08-25
 *
 * @brief      <BSP layer of SPI>
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_BSP_SPI_H_
#define INC_BSP_SPI_H_

/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"

/* Public defines ----------------------------------------------------- */


/* Public function prototypes ----------------------------------------- */
HAL_StatusTypeDef bsp_spi_transmit_receive(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size,uint32_t Timeout);
HAL_StatusTypeDef bspGetSPI(SPI_HandleTypeDef *spix);

#endif /* INC_BSP_SPI_H_ */

/* End of file -------------------------------------------------------- */

