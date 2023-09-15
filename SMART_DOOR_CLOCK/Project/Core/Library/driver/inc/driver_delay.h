/**
 * @file       driver_delay.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2023-09-01
 * @author     khoa vo
 * @brief      Driver for delay
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef LIBRARY_DRIVER_INC_DRIVER_DELAY_H_
#define LIBRARY_DRIVER_INC_DRIVER_DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
/* Public defines ----------------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------------- */
/* Public macros ------------------------------------------------------------ */
/* Public variables --------------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief Delay the program execution for a specified duration.
 *
 * @param[in] delay The duration to delay in milliseconds.
 */
void time_delay(uint32_t delay);

/**
 * @brief Get the current system tick count.
 *
 * This function retrieves the current system tick count, which is often used for timing purposes.
 */
void time_get_tick();

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* LIBRARY_DRIVER_INC_DRIVER_DELAY_H_ */

/* End of file -------------------------------------------------------------- */

