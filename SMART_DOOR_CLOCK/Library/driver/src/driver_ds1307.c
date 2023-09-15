/**
 * @file       rtc_ds1307.c
 * @copyright  
 * @license    
 * @version    1.0.0
 * @date       2023-08-23
 * @author     khoa vo
 * @brief      Driver for RTC DS1307
 * @note       None
 * @example    None
 */

/* Public includes ---------------------------------------------------------- */
#include "rtc_ds1307.h"

/* Private includes --------------------------------------------------------- */
/* Private defines ---------------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------------- */

/* Private macros ----------------------------------------------------------- */
/* Public variables --------------------------------------------------------- */

/* Private variables -------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */

/* Public implementations --------------------------------------------------- */
/*----------------------------------Init--------------------------------------*/
void ds1307_init(I2C_HandleTypeDef *hi2c)
{
  _ds1307_ui2c = hi2c;
  ds1307_set_clock_halt(0);

  //Check if device is connected
  // if (...)
  //   return TM_DS1307_Result_DeviceNotConnected;
  // else
  //   return TM_DS1307_Result_Ok;
}

void ds1307_set_clock_halt(uint8_t halt)
{
  uint8_t clock_halt = (halt ? 1 << 7 : 0);
  ds1307_set_reg_byte(DS1307_REG_SECOND, clock_halt | (ds1307_get_reg_byte(DS1307_REG_SECOND) & 0x7f));
}

uint8_t ds1307_get_clock_halt(void)
{
  return (ds1307_get_reg_byte(DS1307_REG_SECOND) & 0x80) >> 7;
}

/*-----------------------------Get and Set register-------------------- ------*/
void ds1307_set_reg_byte(uint8_t reg_addr, uint8_t val)
{
  uint8_t bytes[2] = {reg_addr, val};
  bsp_i2C_master_transmit(_ds1307_ui2c, DS1307_I2C_ADDR << 1, bytes, 2, DS1307_TIMEOUT);
}

uint8_t ds1307_get_reg_byte(uint8_t reg_addr)
{
  uint8_t val;
  bsp_i2C_master_transmit(_ds1307_ui2c, DS1307_I2C_ADDR << 1, &reg_addr, 1, DS1307_TIMEOUT);
  bsp_i2c_master_receive(_ds1307_ui2c, DS1307_I2C_ADDR << 1, &val, 1, DS1307_TIMEOUT);
  return val;
}

/*----------------------------------SQW/OUT pin-------------------------------*/
void ds1307_enable_output_pin(ds1307_output_frequency_t frequency)
{
    uint8_t temp;
    if (frequency == DS1307_SQW_1HZ) 
    {
        temp = 1 << DS1307_CONTROL_OUT | 1 << DS1307_CONTROL_SQWE;
    } 
    else if (frequency == DS1307_SQW_4096HZ) 
    {
        temp = 1 << DS1307_CONTROL_OUT | 1 << DS1307_CONTROL_SQWE | 1 << DS1307_CONTROL_RS0;
    } 
    else if (frequency == DS1307_SQW_8192HZ) 
    {
        temp =  1 << DS1307_CONTROL_OUT |  1 << DS1307_CONTROL_SQWE | 1 << DS1307_CONTROL_RS1;
    } 
    else if (frequency == DS1307_SQW_32768HZ) 
    {
        temp = 1 << DS1307_CONTROL_OUT |  1 << DS1307_CONTROL_SQWE | 1 << DS1307_CONTROL_RS1 | 1 << DS1307_CONTROL_RS0;
    } 
    else if (frequency == DS1307_OUT_HIGH) 
    {
        temp = 1 << DS1307_CONTROL_OUT;
    } 
    else if (frequency == DS1307_OUT_LOW) 
    {
        temp = 0;
    }
    ds1307_set_reg_byte(DS1307_REG_CONTROL, temp);
}

void ds1307_disable_output_pin(void)
{
    ds1307_enable_output_pin(DS1307_OUT_HIGH);
}

/*-----------------------------------Get time--------------------------------*/
/* Get full time */
void ds1307_get_date_time(ds1307_time_t *ds1307)
{
    uint16_t cen;
    ds1307->seconds=ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_SECOND) & 0x7f);
    ds1307->minutes=ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_MINUTE));
    ds1307->hours=ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_HOUR) & 0x3f);
    ds1307->dow=ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_DOW));
    ds1307->date=ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_DATE));
    ds1307->month=ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_MONTH));
    cen = ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_CENT));
    ds1307->year=ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_YEAR)) + (cen * 100);
}

/* Get one specific register byte */
uint8_t ds1307_get_dayofweek(void)
{
  return ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_DOW));
}

uint8_t ds1307_get_date(void)
{
  return ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_DATE));
}

uint8_t ds1307_get_month(void)
{
  return ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_MONTH));
}

uint16_t ds1307_get_year(void)
{
  uint16_t cen = ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_CENT)) * 100;
  return ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_YEAR)) + cen;
}

uint8_t ds1307_get_hour(void)
{
  return ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_HOUR) & 0x3f);
}

uint8_t ds1307_get_minute(void)
{
  return ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_MINUTE));
}

uint8_t ds1307_get_second(void)
{
  return ds1307_bin_to_bcd(ds1307_get_reg_byte(DS1307_REG_SECOND) & 0x7f);
}

/*-----------------------------------Set time--------------------------------*/

/* Set full time */
void ds1307_set_date_time(uint8_t second, uint8_t minute, uint8_t hour_24mode, uint8_t dayofweek, uint8_t date, uint8_t month, uint16_t year)
{
    ds1307_set_reg_byte(DS1307_REG_SECOND, ds1307_bcd_to_bin(second | ds1307_get_clock_halt())); //second Second, 0 to 59
    ds1307_set_reg_byte(DS1307_REG_MINUTE, ds1307_bcd_to_bin(minute));  //minute Minute, 0 to 59
    ds1307_set_reg_byte(DS1307_REG_HOUR, ds1307_bcd_to_bin(hour_24mode & 0x3f));//hour_24mode Hour in 24h format, 0 to 23.
    ds1307_set_reg_byte(DS1307_REG_DOW, ds1307_bcd_to_bin(dayofweek));  //dayOfWeek - Days since last Sunday, 1 to 7.
    ds1307_set_reg_byte(DS1307_REG_DATE, ds1307_bcd_to_bin(date));      //date - Day of month, 1 to 31.
    ds1307_set_reg_byte(DS1307_REG_MONTH, ds1307_bcd_to_bin(month));    //month - Month, 1 to 12.
    ds1307_set_reg_byte(DS1307_REG_CENT, ds1307_bcd_to_bin(year / 100));                   //year - Year, 2000 - 2099
    ds1307_set_reg_byte(DS1307_REG_YEAR, ds1307_bcd_to_bin(year % 100));// ex: 2023 --> CENT=20 and YEAR=23
}

/* Set one specific register byte */
void ds1307_set_dayofweek(uint8_t dayofweek)
{
  ds1307_set_reg_byte(DS1307_REG_DOW, ds1307_bcd_to_bin(dayofweek));
}

void ds1307_set_date(uint8_t date)
{
  ds1307_set_reg_byte(DS1307_REG_DATE, ds1307_bcd_to_bin(date));
}

void ds1307_set_month(uint8_t month)
{
  ds1307_set_reg_byte(DS1307_REG_MONTH, ds1307_bcd_to_bin(month));
}

void ds1307_set_year(uint16_t year)
{
  ds1307_set_reg_byte(DS1307_REG_CENT, year / 100);
  ds1307_set_reg_byte(DS1307_REG_YEAR, ds1307_bcd_to_bin(year % 100));
}

void ds1307_set_hour(uint8_t hour_24mode)
{
  ds1307_set_reg_byte(DS1307_REG_HOUR, ds1307_bcd_to_bin(hour_24mode & 0x3f));
}

void ds1307_set_minute(uint8_t minute)
{
  ds1307_set_reg_byte(DS1307_REG_MINUTE, ds1307_bcd_to_bin(minute));
}

void ds1307_set_second(uint8_t second)
{
  uint8_t clock_halt = ds1307_get_clock_halt();
  ds1307_set_reg_byte(DS1307_REG_SECOND, ds1307_bcd_to_bin(second | clock_halt));
}

/*---------------------------------Convert BCD - BIN-------------------------------*/
uint8_t ds1307_bin_to_bcd(uint8_t bin)
{
  return (((bin & 0xf0) >> 4) * 10) + (bin & 0x0f);
}

uint8_t ds1307_bcd_to_bin(uint8_t bcd)
{
  return (bcd % 10 + ((bcd / 10) << 4));
}

/* End of file -------------------------------------------------------------- */



