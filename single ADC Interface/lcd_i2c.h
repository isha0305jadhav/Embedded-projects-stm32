#ifndef __LCD_I2C_H__
#define __LCD_I2C_H__

#include "stm32f4xx_hal.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// PCF8574 bit definitions (common backpack mapping)
#define LCD_BACKLIGHT_BIT   0x08
#define LCD_EN_BIT          0x04
#define LCD_RW_BIT          0x02
#define LCD_RS_BIT          0x01

typedef struct {
    I2C_HandleTypeDef *hi2c;
    uint16_t addr;      // 8-bit HAL address (7-bit << 1), e.g., (0x27<<1)
    uint8_t backlight;  // 0 or LCD_BACKLIGHT_BIT
    uint8_t cols;
    uint8_t rows;
} LCD_I2C_HandleTypeDef;

/* Public API (matches your main.c usage) */
void LCD_Init(LCD_I2C_HandleTypeDef *lcd,
              I2C_HandleTypeDef *hi2c,
              uint16_t i2c_addr_8bit,
              uint8_t cols,
              uint8_t rows);

void LCD_Clear(LCD_I2C_HandleTypeDef *lcd);
void LCD_Home(LCD_I2C_HandleTypeDef *lcd);
void LCD_SetCursor(LCD_I2C_HandleTypeDef *lcd, uint8_t col, uint8_t row);
void LCD_Print(LCD_I2C_HandleTypeDef *lcd, const char *s);
void LCD_Backlight(LCD_I2C_HandleTypeDef *lcd, uint8_t on);
void LCD_DisplayOn(LCD_I2C_HandleTypeDef *lcd);
void LCD_DisplayOff(LCD_I2C_HandleTypeDef *lcd);

#ifdef __cplusplus
}
#endif
#endif /* __LCD_I2C_H__ */
