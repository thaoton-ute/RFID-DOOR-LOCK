/**
 * @file       bsp_delay.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2023-08-28
 * @author     khoa vo
 * @brief      BSP for DELAY
 * @note       None
 * @example    None
 */

/* Public includes ---------------------------------------------------------- */
#include "bsp_delay.h"

/* Private includes --------------------------------------------------------- */
/* Private defines ---------------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------------- */
/* Private macros ----------------------------------------------------------- */

/* Public variables --------------------------------------------------------- */

/* Private variables -------------------------------------------------------- */

/* Function definitions ----------------------------------------------- */

void bsp_delay(uint32_t delay)
{
	HAL_Delay(delay);
}

void bsp_get_tick()
{
	HAL_GetTick();
}


/* End of file -------------------------------------------------------------- */
