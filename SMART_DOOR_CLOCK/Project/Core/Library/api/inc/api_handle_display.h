/**
 * @file       api_handle_display.h
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
#ifndef LIBRARY_API_INC_API_HANDLE_DISPLAY_H_
#define LIBRARY_API_INC_API_HANDLE_DISPLAY_H_

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

/* Public function prototypes ----------------------------------------- */

/**
 * @brief Display the current date and time on the API_HANDLE display.
 */
void h_display_time();

/**
 * @brief Display a "wrong card" message on the API_HANDLE display.
 */
void h_wrong_card();

/**
 * @brief Display a "wrong password" message on the API_HANDLE display.
 */
void h_wrong_pass();

/**
 * @brief Display a "timeout" message on the API_HANDLE display.
 */
void h_timeout();

/**
 * @brief Display a "block 60s" message on the API_HANDLE display.
 */
void h_block();

/**
 * @brief Display a "enter new password" message on the API_HANDLE display.
 */
void h_display_enter_new_pass();

/**
 * @brief Display an "enter current password" message on the API_HANDLE display.
 */
void h_display_enter_current_pass();

/**
 * @brief Display a "tap master card" message on the API_HANDLE display.
 */
void h_display_tap_master_card();

/**
 * @brief Display a "tap new card" message on the API_HANDLE display.
 */
void h_display_tap_new_card();

/**
 * @brief Display options for choosing a mode on the API_HANDLE display.
 */
void h_display_choose_mode();

/**
 * @brief Display an "open door" message on the API_HANDLE display.
 */
void h_display_open_door();

/**
 * @brief Display a "close door" message on the API_HANDLE display.
 */
void h_display_close_door();

/**
 * @brief Display a "save is successful" message on the API_HANDLE display.
 */
void h_save_successful();

/**
 * @brief Perform actions to open the door and save the current time.
 */
void open_door();

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* LIBRARY_API_INC_API_HANDLE_DISPLAY_H_ */
/* End of file -------------------------------------------------------------- */


