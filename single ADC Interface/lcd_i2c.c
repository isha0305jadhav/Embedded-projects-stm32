#include "lcd_i2c.h"
#include <string.h>

/* ====== PCF8574 <-> HD44780 low-level helpers ====== */

static void lcd_i2c_write(LCD_I2C_HandleTypeDef *lcd, uint8_t data)
{
    HAL_I2C_Master_Transmit(lcd->hi2c, lcd->addr, &data, 1, 10);
}

// Pulse EN high->low to latch current bus state into LCD
static void lcd_pulse_enable(LCD_I2C_HandleTypeDef *lcd, uint8_t data)
{
    lcd_i2c_write(lcd, data | LCD_EN_BIT);
    HAL_Delay(1);
    lcd_i2c_write(lcd, data & (uint8_t)~LCD_EN_BIT);
    HAL_Delay(1);
}

// Send upper nibble already positioned in bits7..4, with mode (RS bit)
static void lcd_write4(LCD_I2C_HandleTypeDef *lcd, uint8_t nibble, uint8_t mode)
{
    uint8_t d = (nibble & 0xF0) | lcd->backlight | mode; // RW=0 always
    lcd_i2c_write(lcd, d);
    lcd_pulse_enable(lcd, d);
}

static void lcd_send_cmd(LCD_I2C_HandleTypeDef *lcd, uint8_t cmd)
{
    lcd_write4(lcd, (uint8_t)(cmd & 0xF0), 0);                 // RS=0
    lcd_write4(lcd, (uint8_t)((cmd << 4) & 0xF0), 0);          // RS=0
}

static void lcd_send_data(LCD_I2C_HandleTypeDef *lcd, uint8_t data)
{
    uint8_t mode = LCD_RS_BIT; // RS=1 for data
    lcd_write4(lcd, (uint8_t)(data & 0xF0), mode);
    lcd_write4(lcd, (uint8_t)((data << 4) & 0xF0), mode);
}

/* ====== Public API ====== */

void LCD_Init(LCD_I2C_HandleTypeDef *lcd,
              I2C_HandleTypeDef *hi2c,
              uint16_t i2c_addr_8bit,
              uint8_t cols,
              uint8_t rows)
{
    lcd->hi2c      = hi2c;
    lcd->addr      = i2c_addr_8bit;      // e.g., (0x27<<1) or (0x3F<<1)
    lcd->backlight = LCD_BACKLIGHT_BIT;  // start with backlight ON
    lcd->cols      = cols;
    lcd->rows      = rows;

    HAL_Delay(50); // power-up wait

    // 4-bit initialization sequence (per HD44780 datasheet)
    lcd_write4(lcd, 0x30, 0); HAL_Delay(5);
    lcd_write4(lcd, 0x30, 0); HAL_Delay(5);
    lcd_write4(lcd, 0x30, 0); HAL_Delay(1);
    lcd_write4(lcd, 0x20, 0); HAL_Delay(1); // set 4-bit

    // Function set: 4-bit, 2 line, 5x8 dots
    lcd_send_cmd(lcd, 0x28);
    // Display ON, cursor OFF, blink OFF
    lcd_send_cmd(lcd, 0x0C);
    // Clear display
    LCD_Clear(lcd);
    // Entry mode: increment, no shift
    lcd_send_cmd(lcd, 0x06);
}

void LCD_Clear(LCD_I2C_HandleTypeDef *lcd)
{
    lcd_send_cmd(lcd, 0x01);
    HAL_Delay(2);
}

void LCD_Home(LCD_I2C_HandleTypeDef *lcd)
{
    lcd_send_cmd(lcd, 0x02);
    HAL_Delay(2);
}

void LCD_SetCursor(LCD_I2C_HandleTypeDef *lcd, uint8_t col, uint8_t row)
{
    static const uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    if (row >= lcd->rows) row = (uint8_t)(lcd->rows - 1U);
    lcd_send_cmd(lcd, (uint8_t)(0x80 | (col + row_offsets[row])));
}

void LCD_Print(LCD_I2C_HandleTypeDef *lcd, const char *s)
{
    while (*s) {
        lcd_send_data(lcd, (uint8_t)*s++);
    }
}

void LCD_Backlight(LCD_I2C_HandleTypeDef *lcd, uint8_t on)
{
    lcd->backlight = on ? LCD_BACKLIGHT_BIT : 0x00;
    // Update PCF8574 output to reflect BL bit immediately (no LCD change)
    lcd_i2c_write(lcd, lcd->backlight);
    HAL_Delay(1);
}

void LCD_DisplayOn(LCD_I2C_HandleTypeDef *lcd)
{
    lcd_send_cmd(lcd, 0x0C); // display on, cursor off, blink off
}

void LCD_DisplayOff(LCD_I2C_HandleTypeDef *lcd)
{
    lcd_send_cmd(lcd, 0x08); // display off
}
