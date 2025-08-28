// lcd_i2c.h
#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_
#include "stm32f4xx_hal.h"
void lcd_init(void);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_clear(void);
#endif
