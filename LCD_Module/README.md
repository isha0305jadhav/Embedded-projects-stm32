# STM32 Nucleo – I2C LCD Module Control

## Goal
The goal of this project is to interface a 16x2 HD44780-compatible LCD module with an STM32 Nucleo board using the I2C protocol.  
The project demonstrates displaying strings, controlling the backlight, enabling/disabling cursor blink, scrolling text, and printing special/custom characters such as smiley faces and diamond shapes.


## Hardware Requirements
- STM32 Nucleo development board (e.g., Nucleo-F446RE)
- 16x2 LCD module with I2C backpack (PCF8574 or similar)
- Micro-USB cable
- Jumper wires


## Software Requirements
- STM32CubeIDE (includes STM32CubeMX)
- ST-LINK driver (for programming the Nucleo board)
- I2C LCD driver library (`lcd_i2c.c`, `lcd_i2c.h`)

## Code Flow
1. Initialize system clock and peripherals.
2. Configure I2C in STM32CubeMX with correct SDA and SCL pins ( PB8 for SDA, PB9 for SCL).
3. Initialize LCD with correct address (0x27) and mode (4-bit). (Read appropriate datasheet for address)
4. Main Operations:
   - Display static strings.
   - Turn backlight ON/OFF using I2C commands.
   - Enable/disable cursor blink.
   - Scroll text left/right.
   - Load and display custom characters (smiley, diamond, arrow, etc.) using CGRAM.

## Necessary Reading / Considerations
- HD44780 LCD Controller command set.
- I2C Protocol Basics:
  - Device addressing.
  - Data and command modes.
- CGRAM (Character Generator RAM)for creating custom symbols.
- Timing Requirements:
  LCD commands require specific delays (in microseconds or milliseconds) to execute.
- I2C Command Sequence:
  - Incorrect sequences can cause garbage text or block patterns.

## Learning Outcomes
- Configuring I2C communication in STM32CubeIDE.
- Initializing and controlling an HD44780-compatible LCD via I2C.
- Implementing LCD control functions:
  - Displaying and positioning strings.
  - Backlight control.
  - Cursor blink/no blink modes.
  - Scrolling text horizontally.
- Creating and Using Custom Characters:
  - Understanding CGRAM mapping.
  - Storing 5x8 pixel patterns for symbols.
  - Writing initialization code for custom patterns.
- Debugging I2C communication issues and validating device address.

## Challenges
- Wrong I2C Command Sequence:
  - Initially, the LCD displayed garbage characters and filled blocks instead of intended text due to sending data before initialization commands were complete.
- Timing Delays:
  - Not adding proper delays between commands caused partial or corrupted displays.
- Custom Character Storage:
  - Misunderstanding CGRAM addressing led to incorrect symbols being shown.
## results
Attached as .mp4 file
