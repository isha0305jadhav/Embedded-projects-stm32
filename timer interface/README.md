A simple embedded project that interfaces an HD44780-compatible 16×2 LCD (via I²C backpack) with an STM32 Nucleo board. It demonstrates I²C communication and timer-based periodic updates (e.g., refreshing text every fixed interval or driving a non-blocking heartbeat).
Objective:
Interface a 16×2 LCD to an STM32 Nucleo using I²C and display text/numbers. Use an STM32 hardware timer to trigger periodic, non-blocking tasks (e.g., update a counter or sensor reading every 500 ms).
Practice clean HAL-based peripheral configuration, modular driver design, and basic embedded timing techniques.

Hardware Required

STM32 Nucleo board (e.g., NUCLEO-F446RE)

16×2 LCD with I²C backpack (PCF8574)

USB cable for programming

Connections:

LCD VCC → Nucleo 5V (or 3.3V if your backpack supports it)

LCD GND → GND

LCD SDA → SDA (PB9)

LCD SCL → SCL (PB8)

Software Required

STM32CubeIDE (HAL drivers)

ST-Link (bundled with Nucleo for flashing/debug)

 Build & Run

Enable I²C (e.g., I2C1)

Mode: I²C

Speed: 100 kHz or 400 kHz

Pins: SDA (PB9), SCL (PB8)

Enable TIM2 (or any general-purpose timer)

Prescaler/Period → e.g., 1 kHz tick or 500 ms interrupt

Timer:

Configure a hardware timer to generate an interrupt at a fixed rate (e.g., every 1 ms or 500 ms).

In the ISR callback, set a flag or increment a software counter.

In the main loop, act on the flag to update the LCD 

Learning Outcomes

Configure and use I²C on STM32 with the HAL.

Understand LCD command flow over I²C (PCF8574 → HD44780).

Implement timer-driven, non-blocking periodic tasks.

Challenges:
Implement ISR and working with timer-(timer calculations)

Do Less in ISRs: Only set flags or counters in timer callbacks; do I²C/LCD writes in while(1).

