/**
 * @file       bsp_spi.c
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.1
 * @date       2023-08-25
 *
 * @brief      <BSP layer of SPI>
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_spi.h"
#include "string.h"
#include "main.h"
/* Public function prototypes ----------------------------------------- */
SPI_HandleTypeDef *bspSPI;

HAL_StatusTypeDef bspGetSPI(SPI_HandleTypeDef *spix)
{
	if(!spix) return HAL_ERROR;
	bspSPI = spix;
	return HAL_OK;
}

HAL_StatusTypeDef bsp_spi_transmit_receive(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size,uint32_t Timeout)
{
	if(!bspSPI) return HAL_ERROR;
	while(!__HAL_SPI_GET_FLAG(bspSPI,SPI_FLAG_TXE));
	HAL_SPI_TransmitReceive(bspSPI, pTxData,pRxData,Size, Timeout);
	while(__HAL_SPI_GET_FLAG(bspSPI,SPI_FLAG_BSY));	/*!< Send byte through the SPI1 peripheral */
	return HAL_OK;
}

/* End of file -------------------------------------------------------- */
