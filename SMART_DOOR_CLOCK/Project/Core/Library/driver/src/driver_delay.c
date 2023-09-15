/**
 * @file       driver_delay.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2023-09-01
 * @author     khoa vo
 * @brief      driver for DELAY
 * @note       None
 * @example    None
 */

/* Public includes ---------------------------------------------------------- */
#include "driver_delay.h"
#include "bsp_delay.h"
/* Private includes --------------------------------------------------------- */
/* Private defines ---------------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------------- */
/* Private macros ----------------------------------------------------------- */

/* Public variables --------------------------------------------------------- */

/* Private variables -------------------------------------------------------- */

/* Public implementations --------------------------------------------------- */

void time_delay(uint32_t delay)
{
	bsp_delay(delay);
}

void time_get_tick()
{
	bsp_get_tick();
}

/* End of file -------------------------------------------------------------- */

