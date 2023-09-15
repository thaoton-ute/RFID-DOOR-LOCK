/**
 * @file       bsp_flash.h
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.1
 * @date       2023-08-25
 *
 * @brief      <bsp_flash>
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_BSP_FLASH_H_
#define INC_BSP_FLASH_H_

/* Includes ----------------------------------------------------------- */
#include <stdint.h>
#include <string.h>
#include "stm32f4xx_hal.h"

/* Public defines ----------------------------------------------------- */
#define __HAL_LOCK(__HANDLE__)                                           \
		do{                                        \
			if((__HANDLE__)->Lock == HAL_LOCKED)   \
			{                                      \
				return HAL_BUSY;                    \
			}                                      \
			else                                   \
			{                                      \
				(__HANDLE__)->Lock = HAL_LOCKED;    \
			}                                      \
		}while (0U)
#define FLASH_TIMEOUT_VALUE       50000U /* 50 s */
#define FLASH_BANK_1     1U /*!< Bank 1   */
#define FLASH_BANK_2     2U /*!< Bank 2   */
#define FLASH_BANK_BOTH  ((uint32_t)FLASH_BANK_1 | FLASH_BANK_2) /*!< Bank1 and Bank2  */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  Unlock the FLASH Option Control Registers access.
 * @retval HAL Status
 */
HAL_StatusTypeDef bsp_flash_unlock(void);

/**
 * @brief  Locks the FLASH control register access
 * @retval HAL Status
 */
HAL_StatusTypeDef bsp_flash_lock(void);

/**
 * @brief  Program data into FLASH memory.
 * @param  TypeProgram: Type of FLASH program operation (byte, halfword, word, doubleword)
 * @param  Address: FLASH memory address to start programming
 * @param  Data: Data to be programmed
 * @retval HAL Status
 */
HAL_StatusTypeDef bsp_flash_program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);

/**
 * @brief  Erase FLASH sectors based on the provided erase configuration.
 * @param  pEraseInit: Pointer to a FLASH_EraseInitTypeDef structure that contains the configuration information for the erasing process
 * @param  SectorError: Pointer to variable that will contain the faulty sector in case of error
 * @retval HAL Status
 */
HAL_StatusTypeDef bsp_flashex_erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *SectorError);

/**
 * @brief  Perform a mass erase of FLASH memory.
 * @param  VoltageRange: FLASH voltage range to be used for the mass erase
 * @param  Banks: Specifies the banks to be erased (FLASH_BANK_1, FLASH_BANK_2, or FLASH_BANK_BOTH)
 * @retval None
 */
void bsp_flash_mass_erase(uint8_t VoltageRange, uint32_t Banks);

/**
 * @brief  Program a byte of data into FLASH memory.
 * @param  Address: FLASH memory address to start programming
 * @param  Data: Byte of data to be programmed
 * @retval None
 */
void bsp_flash_program_byte(uint32_t Address, uint8_t Data);

/**
 * @brief  Program a halfword (16-bit) of data into FLASH memory.
 * @param  Address: FLASH memory address to start programming
 * @param  Data: Halfword of data to be programmed
 * @retval None
 */
void bsp_flash_program_halfword(uint32_t Address, uint16_t Data);

/**
 * @brief  Program a word (32-bit) of data into FLASH memory.
 * @param  Address: FLASH memory address to start programming
 * @param  Data: Word of data to be programmed
 * @retval None
 */
void bsp_flash_program_word(uint32_t Address, uint32_t Data);

/**
 * @brief  Program a doubleword (64-bit) of data into FLASH memory.
 * @param  Address: FLASH memory address to start programming
 * @param  Data: Doubleword of data to be programmed
 * @retval None
 */
void bsp_flash_program_doubleword(uint32_t Address, uint64_t Data);

#endif /* INC_BSP_FLASH_H_ */

/* End of file -------------------------------------------------------- */
