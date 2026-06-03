# STM32F446RE Drivers

Register-level peripheral drivers written from scratch for the STM32F446RE microcontroller in C, Baremetal.

## Overview

This Repo's main intent is for me to learn and open source Drivers for my STM32, I like Open Sourcing my work! Open Sourcing helps people connect and create awesome things like Linux, GCC and what not!

## Current Drivers

### GPIO Driver

Features:

* GPIO Initialization
* Input Mode
* Output Mode
* Alternate Function Mode
* Analog Mode
* Push-Pull Configuration
* Open-Drain Configuration
* Pull-Up / Pull-Down Configuration
* GPIO Read
* GPIO Write
* GPIO Toggle

## Project Structure

```text
STM32F446RE_Drivers/
│
├── Drivers/
│   └── GPIO/
│       ├── GPIO.c
│       └── GPIO.h
│
└── README.md
```

## Example

```c
GPIO_PinConfig_t LedConfig;

LedConfig.PinNumber = 5;
LedConfig.Mode = GPIO_MODE_OUTPUT;
LedConfig.Speed = GPIO_SPEED_HIGH;
LedConfig.OutputType = OUTPUT_TYPE_PP;
LedConfig.PuPdControl = PUPD_NO_PUPD;

GPIO_Init(GPIOA, &LedConfig);

while(1)
{
    GPIO_TogglePin(GPIOA, 5);
}
```

## Supported Peripherals

| Peripheral | Status |
|------------|---------|
| GPIO | ✅ Complete |
| USART | 🚧 Planned |
| SPI | 🚧 Planned |
| I2C | 🚧 Planned |
| EXTI | 🚧 Planned |
| Timers | 🚧 Planned |
| ADC | 🚧 Planned |

## Goals

* Learn embedded systems through register-level programming
* Build reusable peripheral drivers
* Understand STM32 hardware architecture
* Create a complete driver library from scratch

## What I Am Learning

* Register-level programming
* Peripheral initialization
* Bit manipulation
* Hardware abstraction
* Baremetal firmware development
* Embedded driver architecture

## Author

ECE Student passionate about Embedded Systems, Firmware Development, and STM32 Microcontrollers.

## License

Licensed under the MIT License.
