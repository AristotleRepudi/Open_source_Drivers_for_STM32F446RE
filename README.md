# STM32F446RE Drivers

Register-level peripheral drivers written completely from scratch for the STM32F446RE microcontroller in C using Bare-Metal programming.

## Overview

This repository documents my journey into low-level Embedded Systems and Firmware Development by implementing peripheral drivers directly from the STM32F446RE Reference Manual without relying on vendor libraries such as STM32 HAL or LL.

The goal is to understand how microcontrollers work internally by interacting directly with peripheral registers, startup code, linker scripts, vector tables, and hardware interfaces.

Open Source software has enabled incredible projects such as Linux, GCC, Git, and countless Embedded tools. This project is my way of learning in public and contributing back to the community.

---

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

Status: ✅ Complete

---

### I2C Driver

Features:

* Master Mode Operation
* START Condition Generation
* STOP Condition Generation
* 7-Bit Addressing
* Transmit Mode
* Receive Mode
* Single Byte Read
* Register Read
* Register Write
* Support for I2C1, I2C2 and I2C3
* OLED Communication Verified

Status: ✅ Complete

---

## Project Structure

```text
STM32F446RE_Drivers/
│
├── Drivers/
│   ├── GPIO/
│   │   ├── GPIO.c
│   │   └── GPIO.h
│   │
│   └── I2C/
│       ├── I2C.c
│       └── I2C.h
│
│
└── README.md
```

---

## Example

### GPIO

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

### I2C

```c
HAL_I2C_Init(I2C1);

I2C_WriteRegister(I2C1,0x3D,0x00,0xAF);
```

---

## Supported Peripherals

| Peripheral | Status         |
| ---------- | -------------- |
| GPIO       | ✅ Complete     |
| I2C        | ✅ Complete     |
| USART      | 🚧 In Progress |
| SPI        | 🚧 Planned     |
| EXTI       | 🚧 Planned     |
| Timers     | 🚧 Planned     |
| ADC        | 🚧 Planned     |
| PWM        | 🚧 Planned     |
| DMA        | 🚧 Planned     |

---

## Learning Objectives

* Register-Level Programming
* Embedded C
* Bare-Metal Firmware Development
* Peripheral Driver Design
* Hardware Abstraction
* Cortex-M Architecture
* Startup Code and Boot Process
* Linker Scripts
* Memory Layout
* Debugging with GDB and OpenOCD

---

## Future Goals

* Interrupt-driven Drivers
* DMA Support
* Reusable Driver Framework
* SSD1306 OLED Library
* FreeRTOS Integration
* Unit Testing Infrastructure
* Continuous Integration using GitHub Actions

---

## Author

ECE Student passionate about:

* Embedded Systems
* Firmware Development
* STM32 Microcontrollers
* Linux
* Open Source Software

---

## License

Licensed under the MIT License.
