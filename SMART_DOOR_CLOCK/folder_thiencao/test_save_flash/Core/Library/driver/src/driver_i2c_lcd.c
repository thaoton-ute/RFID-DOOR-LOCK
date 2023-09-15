/**
 * @file       i2c-lcd.c
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     thien cao
 * @author     thien cao
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example    example_file_1.c
 *             Example_1 description
 * @example    example_file_2.c
 *             Example_2 description
 */

/* Includes ----------------------------------------------------------- */
#include "driver_i2c_lcd.h"
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static BSP_I2C_Handle i2c1_handle;
/* Private function prototypes ---------------------------------------- */

static void lcd_i2c_init(I2C_HandleTypeDef *hi2c);
/* Function definitions ----------------------------------------------- */

static void lcd_i2c_init(I2C_HandleTypeDef *hi2c) {
    bsp_i2c_init(&i2c1_handle, hi2c);
}

void lcd_send_cmd(char cmd) {
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd & 0xf0);
    data_l = ((cmd << 4) & 0xf0);
    data_t[0] = data_u | 0x0C;  // en=1, rs=0
    data_t[1] = data_u | 0x08;  // en=0, rs=0
    data_t[2] = data_l | 0x0C;  // en=1, rs=0
    data_t[3] = data_l | 0x08;  // en=0, rs=0
    bsp_i2c_transmit(&i2c1_handle, SLAVE_ADDRESS_LCD, (uint8_t *)data_t, 4);
}

void lcd_send_data(char data) {
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (data & 0xf0);
    data_l = ((data << 4) & 0xf0);
    data_t[0] = data_u | 0x0D;  // en=1, rs=0
    data_t[1] = data_u | 0x09;  // en=0, rs=0
    data_t[2] = data_l | 0x0D;  // en=1, rs=0
    data_t[3] = data_l | 0x09;  // en=0, rs=0
    bsp_i2c_transmit(&i2c1_handle, SLAVE_ADDRESS_LCD, (uint8_t *)data_t, 4);
}

void lcd_clear(void) {
	lcd_send_cmd (0x80);
    for (int i = 0; i < 70; i++) {
        lcd_send_data(' ');
    }
}

void lcd_goto_xy(int row, int col) {
    switch (row) {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd(col);
}

void lcd_init(I2C_HandleTypeDef *hi2c) {
    lcd_i2c_init(hi2c);
    // 4-bit initialization
    HAL_Delay(50);  // wait for >40ms
    lcd_send_cmd(0x30);
    HAL_Delay(5);  // wait for >4.1ms
    lcd_send_cmd(0x30);
    HAL_Delay(1);  // wait for >100us
    lcd_send_cmd(0x30);
    HAL_Delay(10);
    lcd_send_cmd(0x20);  // 4-bit mode
    HAL_Delay(10);

    // Display initialization
    lcd_send_cmd(0x28);  // Function set --> DL=0 (4-bit mode), N = 1 (2-line display), F = 0 (5x8 characters)
    HAL_Delay(1);
    lcd_send_cmd(0x08);  // Display on/off control --> D=0, C=0, B=0  ---> display off
    HAL_Delay(1);
    lcd_send_cmd(0x01);  // Clear display
    HAL_Delay(1);
    HAL_Delay(1);
    lcd_send_cmd(0x06);  // Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
    HAL_Delay(1);
    lcd_send_cmd(0x0C);  // Display on/off
}

void lcd_send_string(char *str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}

void lcd_display(int row, int col, char *str)
{
	lcd_goto_xy(row, col);
	lcd_send_string(str);
}

void lcd_scroll(){

}
/* End of file -------------------------------------------------------- */
