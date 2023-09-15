/**
 * @file       bsp_delay.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2023-08-28
 * @author     khoa vo
 * @brief      BSP for DELAY
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef INC_BSP_DELAY_H_
#define INC_BSP_DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "stm32f4xx_hal.h"

/* Public defines ----------------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------------- */

/* Public macros ------------------------------------------------------------ */
/* Public variables --------------------------------------------------------- */

/* Public APIs -------------------------------------------------------------- */
/**
  * @brief This function provides minimum delay (in milliseconds) based
  *        on variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param Delay specifies the delay time length, in milliseconds.
  * @retval None
  */
void bsp_delay(uint32_t delay);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* INC_BSP_DELAY_H_ */

/* End of file -------------------------------------------------------------- */







