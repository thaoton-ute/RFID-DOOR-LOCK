/*
 * test_function.h
 *
 *  Created on: Aug 28, 2023
 *      Author: Admin
 */

#ifndef INC_TEST_FUNCTION_H_
#define INC_TEST_FUNCTION_H_

#include "rtc_ds1307.h"
#include "bsp_delay.h"
#include <stdio.h>
ds1307_time_t time;

    char *time_display()
    {
    	static char time_string[9];		// "HH:MM:SS" + ký tự null

    	ds1307_get_date_time(&time);

    	// Convert time to string
    	sprintf(time_string, "%02d:%02d:%02d", time.hours, time.minutes, time.seconds);

    	return time_string;
    }

    char *date_display()
    {
    	static char date_string[11];	// "DD:MM:YYYY" + ký tự null

    	ds1307_get_date_time(&time);

    	// Convert time to string
    	sprintf(date_string, "%02d-%02d-%04d", time.date, time.month, time.year);

    	return date_string;
    }

void time_delay(uint32_t delay)
{
	bsp_delay(delay);
}

#endif /* INC_TEST_FUNCTION_H_ */
