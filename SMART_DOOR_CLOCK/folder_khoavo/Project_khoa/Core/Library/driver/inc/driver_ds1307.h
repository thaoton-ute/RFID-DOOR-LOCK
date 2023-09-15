/**
 * @file       rtc_ds1307.h
 * @copyright  
 * @license    
 * @version    1.0.0
 * @date       2023-08-23
 * @author     khoa vo    
 * @brief      Driver for RTC DS1307         
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef INC_RTC_DS1307_H_
#define INC_RTC_DS1307_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "bsp_i2c_1.h"

/* Public defines ----------------------------------------------------------- */
#define DS1307_I2C_CLOCK    100000		// DS1307 I2C clock 

#define DS1307_I2C_ADDR 	0x68		// I2C slave address for DS1307

#define DS1307_REG_SECOND 	0x00		// Second register address
#define DS1307_REG_MINUTE 	0x01		// Minute register address
#define DS1307_REG_HOUR 	0x02		// Hour register address
#define DS1307_REG_DOW 		0x03		// Date of week register address
#define DS1307_REG_DATE		0x04		// Date register address
#define DS1307_REG_MONTH 	0x05		// Month register address
#define DS1307_REG_YEAR 	0x06		// Year register address
#define DS1307_REG_CONTROL 	0x07		// Control register address
#define DS1307_REG_UTC_HR   0x08		// UTC hour register address
#define DS1307_REG_UTC_MIN  0x09		// UTC minute register address
#define DS1307_REG_CENT     0x10		// Cent register address
#define DS1307_TIMEOUT 		1000		// Timeput register address

#define DS1307_CONTROL_OUT 	7			// Bits in control register 
#define DS1307_CONTROL_SQWE 4			// Use to translate bit 1
#define DS1307_CONTROL_RS1 	1
#define DS1307_CONTROL_RS0 	0

/* Public enumerate/structure ----------------------------------------------- */
/**
 * @brief  Result state
 */
typedef enum
{
	DS1307_Result_Ok = 0,				// ok
	DS1307_Result_Error,				// error
	DS1307_Result_DeviceNotConnected 	// not connected
} 
ds1307_result_t;

/**
 * @brief  SQW/OUT pin
 */
typedef enum
{
	DS1307_SQW_1HZ = 0,	// set sqw/out pin at sqw mode, with frequence  1	 Hz
	DS1307_SQW_4096HZ,	//											   4096	 Hz
	DS1307_SQW_8192HZ,	//											   8192	 Hz
	DS1307_SQW_32768HZ, //											   32768 Hz
	DS1307_OUT_HIGH,	// set sqw/out pin at out mode - HIGH
	DS1307_OUT_LOW		// set sqw/out pin at out mode - LOW
} 
ds1307_output_frequency_t;

/**
 * @brief ds1307 struct
 */
typedef struct
{
	uint8_t seconds; // Seconds, from 00 to 59
	uint8_t minutes; // Minutes, from 00 to 59
	uint8_t hours;	 // Hours, 24Hour mode, 00 to 23
	uint8_t dow;	 // Day in a week, from 1 to 7
	uint8_t date;	 // Date in a month, 1 to 31
	uint8_t month;	 // Month in a year, 1 to 12
	uint16_t year;	 // Year, 00 to 99, 00 is 2000 and 99 is 2099
}
ds1307_time_t;

/* Public macros ------------------------------------------------------------ */
/* Public variables --------------------------------------------------------- */

/* Public APIs -------------------------------------------------------------- */
/**
 * @brief         Init the DS1307 RTC module
 * 
 * @param[in]	  hi2c          Pointer to handler of I2C_HandleTypeDe struct
 */
void ds1307_init(I2C_HandleTypeDef *hi2c);

/**
 * @brief 		  Set the clock halt flag of the DS1307 RTC.
 *
 * @param[in]	  halt			Clock halt bit (CH) value (1 to halt, 0 to resume).
 */
void ds1307_set_clock_halt(uint8_t halt);

/**
 * @brief 		  Get the clock halt bit (CH)
 *
 * @return 	      Clock halt value (1 if halted, 0 if not halted).
 */
uint8_t ds1307_get_clock_halt(void);	// Get Clock Halt bit for case use reg second

/**
 * @brief 		  Write a byte to a specific register of the DS1307.
 *
 * @param[in] 	  reg_addr 		Register address to write to.
 * @param[in] 	  val 			Byte value to be written, 0 to 255.
 */
void ds1307_set_reg_byte(uint8_t reg_addr, uint8_t val);

/**
 * @brief 		  Read a byte from a specific register of the DS1307.
 *
 * @param[in] 	  reg_addr 		Register address to read from.
 * 
 * @return 		  Reg byte value.
 */
uint8_t ds1307_get_reg_byte(uint8_t reg_addr);

/**
 * @brief 		  Enable SQW/OUT pin .
 *
 * @param[in] 	  frequency 	output mode 32768Hz, 8192Hz, 4096Hz, 1Hz, Low or High.
 */
void ds1307_enable_output_pin(ds1307_output_frequency_t frequency);

/**
 * @brief 		  Disable SQW/OUT pin, default HIGH .
 */
void ds1307_disable_output_pin(void);

/**
 * @brief 		  Read the current time and date from the DS1307 RTC.
 */
void ds1307_get_date_time(ds1307_time_t *ds1307); 		// get full date and time, storage in ds1307 struct.

/**
 * @brief		  Get time (one specific reg byte)
 * 
 * @return		  time value
 */
uint8_t ds1307_get_dayofweek(void); 					
uint8_t ds1307_get_date(void);
uint8_t ds1307_get_month(void);
uint16_t ds1307_get_year(void);
uint8_t ds1307_get_hour(void);
uint8_t ds1307_get_minute(void);
uint8_t ds1307_get_second(void);

/**
 * @brief 		  Set the time and date for the DS1307 RTC.
 *
 * @param[in] 	  second		Seconds value (0 to 59).
 * @param[in]	  minute		Minutes value (0 to 59).
 * @param[in] 	  hour_24mode 	Hour value in 24-hour format (0 to 23).
 * @param[in] 	  dayofweek 	Day of the week (1 to 7, where 1 represents Sunday).
 * @param[in] 	  date 			Day of the month (1 to 31).
 * @param[in] 	  month 		Month value (1 to 12).
 * @param[in] 	  year 			Year value (2000 to 2099).
 */
void ds1307_set_date_time(uint8_t second, uint8_t minute, uint8_t hour_24mode, uint8_t dayofweek, uint8_t date, uint8_t month, uint16_t year);

/**
 * @brief		  Set time (one specific reg byte)
 * 
 * @param[in]	  ... time value
 */
void ds1307_set_dayofweek(uint8_t dow);				
void ds1307_set_month(uint8_t month);
void ds1307_set_year(uint16_t year);
void ds1307_set_hour(uint8_t hour_24mode);
void ds1307_set_minute(uint8_t minute);
void ds1307_set_second(uint8_t second);
void ds1307_set_timezone(int8_t hr, uint8_t min);

/**
 * @brief 		  Encodes a decimal number to binaty-coded decimal for storage in registers.
 * @param[in] 		  bcd 		 	BCD number to encode.
 * @return 		  Encoded binary-coded decimal value.
 */
uint8_t ds1307_bcd_to_bin(uint8_t bcd);

/**
 * @brief 		  Decodes the raw binary value stored in registers to decimal format.
 * @param 		  bin 				Binary-coded decimal value retrieved from register, 0 to 255.
 * @return 		  Decoded decimal value.
 */
uint8_t ds1307_bin_to_bcd(uint8_t bin);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* INC_RTC_DS1307_H_ */

/* End of file -------------------------------------------------------------- */
