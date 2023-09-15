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
/**
 * @brief Transmit and receive data using the BSP SPI module.
 * @param ptx_data Pointer to the data to be transmitted.
 * @param prx_data Pointer to the buffer for received data.
 * @param size The number of bytes to transmit and receive.
 * @param timeout Timeout duration for the SPI operation.
 * @return HAL_StatusTypeDef indicating success or failure.
 */
HAL_StatusTypeDef bsp_spi_transmit_receive(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size,uint32_t Timeout);

/**
 * @brief Initialize the BSP SPI module with the specified SPI handle.
 * @param spix Pointer to the SPI handle to be used for communication.
 * @return HAL_StatusTypeDef indicating success or failure.
 */
HAL_StatusTypeDef bspGetSPI(SPI_HandleTypeDef *spix);

#endif /* INC_BSP_SPI_H_ */

/* End of file -------------------------------------------------------- */
