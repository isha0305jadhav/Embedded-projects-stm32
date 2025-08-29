# STM32 Nucleo – Internal RTC Date & Time Printing

## Goal
The goal of this project is to use the STM32’s internal Real-Time Clock (RTC) peripheral to keep track of date and time, and display the results on a serial terminal or an LCD module.  

## Hardware Requirements
- STM32 Nucleo development board (e.g., Nucleo-F446RE)
- Micro-USB cable (for programming and serial communication)
- 16x2 I2C LCD module to display date and time

## Software Requirements
- STM32CubeIDE (includes STM32CubeMX)
- ST-LINK driver (for programming the Nucleo board)

##  Necessary Reading / Considerations
- RTC Basics:
  - RTC runs independently from the main CPU clock using a low-speed oscillator.
  - Backup domain allows RTC to keep running during resets or power loss when a backup battery is connected.
- Clock Source Options:
  - LSI (internal)
- Backup Registers:
  - Can be used to store time settings and avoid resetting on power cycles.
- Formatting:
  - `HAL_RTC_GetTime()` and `HAL_RTC_GetDate()` must be called in the correct order to prevent stale data.

---

## Learning Outcomes
- Configuring the internal RTC peripheral in STM32Cube.
- Selecting and enabling the correct RTC clock source.
- Understanding the difference between LSE and LSI oscillators.
- Using HAL functions:
  - `HAL_RTC_SetTime()`
  - `HAL_RTC_SetDate()`
  - `HAL_RTC_GetTime()`
  - `HAL_RTC_GetDate()`
- Formatting time and date for human-readable output.
- Integrating RTC with an LCD for real-time display.
## Results
Attched as .mp4 file
