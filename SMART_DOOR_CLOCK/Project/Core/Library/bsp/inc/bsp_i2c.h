/**
 * @file       bsp_i2c.h
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     thien cao
 * @author     thien cao
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example    example_file_1.c
 *             Example_1 description
 * @example    example_file_2.c
 *             Example_2 description
 */
/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __INC_BSP_I2C_H
#define __INC_BSP_I2C_H

/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"

/* Public defines ----------------------------------------------------- */
/* None */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief Enumeration for BSP I2C status.
 */
typedef enum {
  BSP_I2C_OK = 0,    /*!< I2C operation success. */
  BSP_I2C_ERROR      /*!< I2C operation error. */
} BSP_I2C_Status;

/**
 * @brief Structure representing BSP I2C handle.
 */
typedef struct {
  I2C_HandleTypeDef *hi2c; /*!< Pointer to the I2C handle structure. */
} BSP_I2C_Handle;

/* Public macros ------------------------------------------------------ */
/* None */

/* Public variables --------------------------------------------------- */
/* None */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief Scan for available I2C device addresses.
 *
 * This function scans for available I2C device addresses on the bus.
 *
 * @param[in] i2c_handle Pointer to the BSP I2C handle structure.
 *
 * @return The detected I2C device address.
 */
uint8_t bsp_i2c_scan_address(BSP_I2C_Handle *i2c_handle);

/**
 * @brief Initialize BSP I2C module.
 *
 * This function initializes the BSP I2C module.
 *
 * @param[in] i2c_handle Pointer to the BSP I2C handle structure.
 * @param[in] hi2c       Pointer to the I2C handle structure.
 */
void bsp_i2c_init(BSP_I2C_Handle *i2c_handle, I2C_HandleTypeDef *hi2c);

/**
 * @brief Transmit data over I2C bus.
 *
 * This function transmits data over the I2C bus to the specified device address.
 *
 * @param[in] i2c_handle    Pointer to the BSP I2C handle structure.
 * @param[in] dev_address   I2C device address.
 * @param[in] data          Pointer to the data buffer.
 * @param[in] size          Size of the data buffer.
 *
 * @return BSP_I2C_Status indicating the transmission status.
 */
BSP_I2C_Status bsp_i2c_transmit(BSP_I2C_Handle *i2c_handle, uint16_t dev_address,
                                uint8_t *data, uint16_t size);

#endif /* INC_BSP_I2C_H_ */

/* End of file -------------------------------------------------------- */
