#include "lcd_i2c.h"
#include "stm32f4xx_hal.h"
#include "string.h"
#include "stdio.h"

extern I2C_HandleTypeDef hi2c1;
#define slave_address_lcd (0x27 << 1)  // shift 7-bit to 8-bit for HAL

void lcd_send_cmd(char cmd)
{
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = cmd & 0xF0;
    data_l = (cmd << 4) & 0xF0;
    data_t[0] = data_u | 0x0C;
    data_t[1] = data_u | 0x08;
    data_t[2] = data_l | 0x0C;
    data_t[3] = data_l | 0x08;
    HAL_I2C_Master_Transmit(&hi2c1, slave_address_lcd, data_t, 4, 100);
}

void lcd_send_data(char data)
{
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = data & 0xF0;
    data_l = (data << 4) & 0xF0;
    data_t[0] = data_u | 0x0D;
    data_t[1] = data_u | 0x09;
    data_t[2] = data_l | 0x0D;
    data_t[3] = data_l | 0x09;
    HAL_I2C_Master_Transmit(&hi2c1, slave_address_lcd, data_t, 4, 100);
}

void lcd_init(void)
{
    HAL_Delay(50);             // wait for >40ms after power on
    lcd_send_cmd(0x33);        // Initialize
    lcd_send_cmd(0x32);        // Set to 4-bit mode
    lcd_send_cmd(0x28);        // 4-bit, 2 line, 5x8 dots
    lcd_send_cmd(0x0C);        // Display on, cursor off
    lcd_send_cmd(0x06);        // Entry mode, cursor right, no shift
    lcd_send_cmd(0x01);        // Clear display
    HAL_Delay(2);              // wait for >1.52ms after clear
}


void lcd_send_string(char *str)
{
    while (*str)
    {
        lcd_send_data(*str++);
    }
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send_cmd(addr);
}

void lcd_clear(void)
{
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}
