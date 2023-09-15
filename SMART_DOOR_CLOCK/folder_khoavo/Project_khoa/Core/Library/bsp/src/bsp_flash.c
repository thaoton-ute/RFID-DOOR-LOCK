/**
 * @file       bsp_flash.c
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.1
 * @date       2023-08-25
 *
 * @brief      <bsp_flash>
 */


/* Includes ----------------------------------------------------------- */
#include <stdint.h>
#include <string.h>
#include "bsp_flash.h"
/* Public defines ----------------------------------------------------- */
extern FLASH_ProcessTypeDef pFlash;
/* Public enumerate/structure ----------------------------------------- */

/* Public function prototypes ----------------------------------------- */
HAL_StatusTypeDef bsp_flash_unlock(void)
{
	HAL_StatusTypeDef status = HAL_OK;

	  if(READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET)
	  {
	    /* Authorize the FLASH Registers access */
	    WRITE_REG(FLASH->KEYR, FLASH_KEY1);
	    WRITE_REG(FLASH->KEYR, FLASH_KEY2);

	    /* Verify Flash is unlocked */
	    if(READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET)
	    {
	      status = HAL_ERROR;
	    }
	  }
	  return status;
}

HAL_StatusTypeDef bsp_flash_lock(void)
{
  /* Set the LOCK Bit to lock the FLASH Registers access */
  FLASH->CR |= FLASH_CR_LOCK;
  return HAL_OK;
}

HAL_StatusTypeDef bsp_flash_program(uint32_t TypeProgram, uint32_t Address, uint64_t Data)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  {
    if(TypeProgram == FLASH_TYPEPROGRAM_BYTE)
    {
      /*Program byte (8-bit) at a specified address.*/
      bsp_flash_program_byte(Address, (uint8_t) Data);
    }
    else if(TypeProgram == FLASH_TYPEPROGRAM_HALFWORD)
    {
      /*Program halfword (16-bit) at a specified address.*/
      bsp_flash_program_halfword(Address, (uint16_t) Data);
    }
    else if(TypeProgram == FLASH_TYPEPROGRAM_WORD)
    {
      /*Program word (32-bit) at a specified address.*/
      bsp_flash_program_word(Address, (uint32_t) Data);
    }
    else
    {
      /*Program double word (64-bit) at a specified address.*/
      bsp_flash_program_doubleword(Address, Data);
    }

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

    /* If the program operation is completed, disable the PG Bit */
    FLASH->CR &= (~FLASH_CR_PG);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

HAL_StatusTypeDef bsp_flashex_erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *SectorError)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  uint32_t index = 0U;

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /*Initialization of SectorError variable*/
    *SectorError = 0xFFFFFFFFU;

    if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
    {
      /*Mass erase to be done*/
      bsp_flash_mass_erase((uint8_t) pEraseInit->VoltageRange, pEraseInit->Banks);

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

      /* if the erase operation is completed, disable the MER Bit */
      FLASH->CR &= (~FLASH_MER_BIT);
    }
    else
    {
      /* Check the parameters */
      assert_param(IS_FLASH_NBSECTORS(pEraseInit->NbSectors + pEraseInit->Sector));

      /* Erase by sector by sector to be done*/
      for (index = pEraseInit->Sector; index < (pEraseInit->NbSectors + pEraseInit->Sector); index++)
      {
        FLASH_Erase_Sector(index, (uint8_t) pEraseInit->VoltageRange);

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

        /* If the erase operation is completed, disable the SER and SNB Bits */
        CLEAR_BIT(FLASH->CR, (FLASH_CR_SER | FLASH_CR_SNB));

        if (status != HAL_OK)
        {
          /* In case of error, stop erase procedure and return the faulty sector*/
          *SectorError = index;
          break;
        }
      }
    }
    /* Flush the caches to be sure of the data consistency */
    FLASH_FlushCaches();
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

void bsp_flash_mass_erase(uint8_t VoltageRange, uint32_t Banks)
{
  /* Check the parameters */
  assert_param(IS_VOLTAGERANGE(VoltageRange));
  assert_param(IS_FLASH_BANK(Banks));

  /* if the previous operation is completed, proceed to erase all sectors */
  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);

  if (Banks == FLASH_BANK_BOTH)
  {
    /* bank1 & bank2 will be erased*/
    FLASH->CR |= FLASH_MER_BIT;
  }
  else if (Banks == FLASH_BANK_1)
  {
    /*Only bank1 will be erased*/
    FLASH->CR |= FLASH_CR_MER;
  }
  else
  {
    /*Only bank2 will be erased*/
    FLASH->CR |= FLASH_CR_MER;
  }
  FLASH->CR |= FLASH_CR_STRT | ((uint32_t)VoltageRange << 8U);
}

void bsp_flash_program_byte(uint32_t Address, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));

  /* If the previous operation is completed, proceed to program the new data */
  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= FLASH_PSIZE_BYTE;
  FLASH->CR |= FLASH_CR_PG;

  *(__IO uint8_t*)Address = Data;
}

void bsp_flash_program_halfword(uint32_t Address, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));

  /* If the previous operation is completed, proceed to program the new data */
  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= FLASH_PSIZE_HALF_WORD;
  FLASH->CR |= FLASH_CR_PG;

  *(__IO uint16_t*)Address = Data;
}

void bsp_flash_program_word(uint32_t Address, uint32_t Data)
{
  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));

  /* If the previous operation is completed, proceed to program the new data */
  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= FLASH_PSIZE_WORD;
  FLASH->CR |= FLASH_CR_PG;

  *(__IO uint32_t*)Address = Data;
}

void bsp_flash_program_doubleword(uint32_t Address, uint64_t Data)
{
  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));

  /* If the previous operation is completed, proceed to program the new data */
  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= FLASH_PSIZE_DOUBLE_WORD;
  FLASH->CR |= FLASH_CR_PG;

  /* Program first word */
  *(__IO uint32_t*)Address = (uint32_t)Data;

  /* Barrier to ensure programming is performed in 2 steps, in right order
    (independently of compiler optimization behavior) */
  __ISB();

  /* Program second word */
  *(__IO uint32_t*)(Address+4) = (uint32_t)(Data >> 32);
}
/* End of file -------------------------------------------------------- */
