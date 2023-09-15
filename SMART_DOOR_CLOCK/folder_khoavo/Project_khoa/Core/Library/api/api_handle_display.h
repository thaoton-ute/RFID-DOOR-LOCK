/**
 * @file       api_handle.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2023-09-01
 * @author     khoa vo
 * @brief      Driver for API_HANDLE
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef LIBRARY_API_API_HANDLE_DISPLAY_H_
#define LIBRARY_API_API_HANDLE_DISPLAY_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "driver_ds1307.h"
#include "driver_i2c_lcd.h"
#include "driver_delay.h"
/* Public defines ----------------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------------- */

/* Public macros ------------------------------------------------------------ */
/* Public variables --------------------------------------------------------- */

/* Public APIs -------------------------------------------------------------- */

void h_display_time();

void h_wrong_card();

void h_wrong_pass();

void h_timeout();

void h_block();

void h_display_enter_new_pass();

void h_display_enter_current_pass();

void h_display_tap_master_card();

void h_display_tap_new_card();

void h_display_choose_mode();

void h_display_open_door();

void h_display_close_door();

void h_save_successful();

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* LIBRARY_API_API_HANDLE_DISPLAY_H_ */

/* End of file -------------------------------------------------------------- */

