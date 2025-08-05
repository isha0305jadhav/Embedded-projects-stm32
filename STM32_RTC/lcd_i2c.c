#include "lcd_i2c.h"
#include "stm32f4xx_hal.h"
#include "string.h"
static I2C_HandleTypeDef *_lcd_i2c;
#define LCD_BACKLIGHT         0x08
#define LCD_ENABLE            0x04
#define LCD_CMD               0x00
#define LCD_DATA              0x01

static void LCD_Write_Nibble(uint8_t nibble, uint8_t mode)
{
	uint8_t data_arr[2];
	uint8_t data = nibble | LCD_BACKLIGHT | mode;

	data_arr[0] = data | LCD_ENABLE;
	data_arr[1] = data;

	HAL_I2C_Master_Transmit(_lcd_i2c, LCD_ADDR, data_arr, 2, HAL_MAX_DELAY);
}

void LCD_Write(uint8_t data, uint8_t mode)
{
	LCD_Write_Nibble(data & 0xF0, mode);
	LCD_Write_Nibble( (data<<4) & 0xF0, mode);
}

void LCD_Send_Cmd(char cmd)
{
	LCD_Write(cmd, LCD_CMD);
}

void LCD_Send_Data(char data)
{
	LCD_Write(data, LCD_DATA);
}
void LCD_Send_String(char *str)
{
	while(*str){
		LCD_Send_Data(*str++);
	}
}
void LCD_Set_Cursor(uint8_t row, uint8_t col)
{
	uint8_t addr = (row ==0)?(0x80+col):(0xC0+col);
	LCD_Send_Cmd(addr);
}
void LCD_Clear(void)
{
	LCD_Send_Cmd(0x01);
	HAL_Delay(2);
}

void LCD_Init(I2C_HandleTypeDef *hi2c)
{
	_lcd_i2c = hi2c;
	HAL_Delay(50);

	LCD_Send_Cmd(0x30);
	HAL_Delay(5);
	LCD_Send_Cmd(0x30);
	HAL_Delay(1);
	LCD_Send_Cmd(0x30);
	HAL_Delay(10);
	LCD_Send_Cmd(0x20);
	LCD_Send_Cmd(0x28);
	LCD_Send_Cmd(0x08);
	LCD_Send_Cmd(0x01);
	HAL_Delay(2);
	LCD_Send_Cmd(0x06);
	LCD_Send_Cmd(0x0C);
	LCD_Clear();
}
