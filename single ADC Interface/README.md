**STM32 Nucleo – LM35 Temperature Sensor Interfacing with I²C LCD**
**Goal**
nterface an LM35 analog temperature sensor with an STM32 Nucleo board using the ADC peripheral. Display the measured temperature in °C on a 16×2 I²C LCD module.Demonstrate ADC sampling, oversampling/averaging, and real-time display updates.

**Hardware Requirements**
- STM32 Nucleo development board (e.g., NUCLEO-F446RE)
- LM35 analog temperature sensor
- 16×2 LCD with I²C backpack (PCF8574)
- Micro-USB cable (for programming + power)
- Jumper wires and Bread board

**Connections:**
- LM35 VCC → 5V (or 3.3V if board only supports 3.3V analog input)
- LM35 GND → GND
- LM35 OUT → Nucleo ADC pin (e.g., PA0 / ADC1_IN0)
- LCD connections same as before:
- VCC → 5V
- GND → GND
- SDA → PB9
- SCL → PB8

**Software Requirements**

STM32CubeIDE (includes STM32CubeMX + HAL libraries)

ST-LINK driver (for programming/debugging)

**Code Flow**

- Initialize system clock and peripherals.

- Configure ADC1 in STM32CubeMX:

- Resolution: 10-bit

- Channel: IN0 (PA0) connected to LM35 output.

- Sampling time: set appropriately for stable readings.

- Configure I²C1 for LCD as before (PB8 SCL, PB9 SDA).

**Necessary Reading / Considerations**

LM35 Datasheet: Output is 10 mV/°C linearly proportional to temperature.

STM32 ADC Basics: Resolution, reference voltage (Vref+), sampling time.

Conversion Formula:

T=(ADCvalue/ADCmax)×Vref10 mV
T=10 mV(ADCvalue/ADCmax)×vref

**Learning Outcomes**
Configure and use ADC peripheral in STM32 with HAL.

Apply oversampling/averaging to reduce noise in sensor readings.

Convert ADC counts → voltage → temperature.

Understand practical aspects of sensor calibration and display formatting.

**Challenges**

Noise in ADC readings: Required averaging/oversampling for stable results.

Voltage reference accuracy: ADC depends on stable Vref; fluctuations cause measurement errors.

Formatting values: Converting float temperature values into LCD-friendly strings.

Temperature drift: Sensor placement and self-heating may affect accuracy.
