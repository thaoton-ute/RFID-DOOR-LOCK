/**
 * @file       api_handle.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2023-09-01
 * @author     khoa vo
 * @brief      Driver for API_HANDLE
 * @note       None
 * @example    None
 */

/* Public includes ---------------------------------------------------------- */
#include <api_handle_display.h>
#include <stdio.h>

/* Private includes --------------------------------------------------------- */
/* Private defines ---------------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------------- */

/* Private macros ----------------------------------------------------------- */
/* Public variables --------------------------------------------------------- */

/* Private variables -------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */

/* Public implementations --------------------------------------------------- */

void h_display_time()
{
	/* Get time "HH:MM:SS" --> string*/
	ds1307_time_t time;
	static char time_string[15];		// "HH:MM:SS   dow" + ký tự null
	static char date_string[11];	// "DD:MM:YYYY" + ký tự null
	const char *const dow_names[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	ds1307_get_date_time(&time);

 	// Convert time to string
	snprintf(time_string, sizeof(time_string), "%02d:%02d:%02d   %s", time.hours, time.minutes, time.seconds, dow_names[time.dow - 1]);
   	sprintf(date_string, "%02d-%02d-%04d", time.date, time.month, time.year);

   	lcd_clear();
	lcd_display(0, 1, date_string);
	lcd_display(1, 1, time_string);
}

void h_wrong_card()
{
	lcd_clear();
	lcd_display(0, 3, "wrong card");
	lcd_display(1, 3, "wait ...");
	time_delay(2000);
}

void h_wrong_pass()
{
	lcd_clear();
	lcd_display(0, 1, "wrong password");
	lcd_display(1, 2, "enter again");
	time_delay(2000);
}

void h_timeout()
{
	lcd_clear();
	lcd_display(0, 4, "timeout");
	lcd_display(1, 4, "wait ...");
	time_delay(2000);
}

void h_block()
{
	lcd_clear();
	lcd_display(0, 3, "block 60s");
	lcd_display(1, 3, "wait ...");
	time_delay(60000);
}

void h_save_successful()
{
	lcd_clear();
	lcd_display(0, 3, "save is");
	lcd_display(1, 3, "successful");
	time_delay(2000);
}

void h_display_enter_new_pass()
{
	lcd_clear();
	lcd_display(0, 3, "enter new");
	lcd_display(1, 3, "password");
}

void h_display_enter_current_pass()
{
	lcd_clear();
	lcd_display(0, 2, "enter current");
	lcd_display(1, 2, "password");
}

void h_display_tap_master_card()
{
	lcd_clear();
	lcd_display(0, 1, "tap master card");
	lcd_display(1, 3, "");
}

void h_display_tap_new_card()
{
	lcd_clear();
	lcd_display(0, 2, "tap new card");
	lcd_display(1, 3, "");
}

void h_display_choose_mode()
{
	lcd_clear();
	lcd_display(0, 1, "1: add card");
	lcd_display(1, 1, "2: change pass");
}

void h_display_open_door()
{
	lcd_clear();
	lcd_display(0, 3, "open door");
	lcd_display(1, 3, "welcome");
}

void h_display_close_door()
{
	lcd_clear();
	lcd_display(0, 3, "close door");
	lcd_display(1, 4, "");
}

/* End of file -------------------------------------------------------------- */



