# STM32F446RE Drivers

Register-level peripheral drivers written completely from scratch for the STM32F446RE microcontroller using Embedded C and Bare-Metal programming.

## Overview

This repository documents my journey into low-level Embedded Systems and Firmware Development by implementing peripheral drivers directly from the STM32F446RE Reference Manual without relying on STM32 HAL, LL libraries, or other vendor-provided abstractions.

The primary objective of this project is to develop a deep understanding of how microcontrollers operate internally by interacting directly with:

* Peripheral Registers
* Memory-Mapped I/O
* Cortex-M4 Architecture
* Startup Code
* Vector Tables
* Linker Scripts
* Interrupts and Exceptions
* Hardware Communication Protocols

Rather than treating peripherals as black boxes, every driver in this repository is built from the ground up using only the reference manual, datasheet, and ARM Cortex-M documentation.

Open Source software has enabled incredible projects such as Linux, GCC, Git, OpenOCD, and countless Embedded tools. This project is my way of learning in public and contributing back to the Embedded Systems community.

---

## Hardware Platform

**Microcontroller:** STM32F446RE

**Core:** ARM Cortex-M4F

**Development Board:** Nucleo-F446RE

---

## Toolchain

Developed using:

* ARM GCC Toolchain
* GNU Make
* OpenOCD
* GDB
* Git
* GitHub
* Ubuntu Linux

No STM32 HAL or LL libraries are used.

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

* Master Mode Communication
* START Condition Generation
* STOP Condition Generation
* 7-Bit Addressing
* Blocking Transmit
* Blocking Receive
* Register Read
* Register Write
* Support for I2C1, I2C2, and I2C3
* SSD1306 OLED Communication Verified

Status: ✅ Complete

---

### SPI Driver

Features:

* Master Mode Operation
* Full Duplex Communication
* CPOL Configuration
* CPHA Configuration
* Software Slave Management (SSM)
* Configurable Clock Prescaler
* 8-Bit Data Frame Support
* 16-Bit Data Frame Support
* Blocking Transmit
* Blocking Receive
* Support for SPI1, SPI2, SPI3, and SPI4

Status: ✅ Complete

---

## Supported Peripherals

| Peripheral | Status         |
| ---------- | -------------- |
| GPIO       | ✅ Complete     |
| I2C        | ✅ Complete     |
| SPI        | ✅ Complete     |
| USART      | 🚧 In Progress |
| EXTI       | 📋 Planned     |
| Timers     | 📋 Planned     |
| ADC        | 📋 Planned     |
| PWM        | 📋 Planned     |
| DMA        | 📋 Planned     |

---

## Project Structure

```text
STM32F446RE_Drivers/
│
├── GPIO/
│   ├── GPIO.c
│   └── GPIO.h
│
├── I2C/
│   ├── I2C.c
│   └── I2C.h
│
├── SPI/
│   ├── SPI.c
│   └── SPI.h
│
├── include/
│
├── linker.ld
│
├── startup_stm32f446xx.s
│
└── README.md
```

---

## Example Usage

### GPIO

```c
GPIO_PinConfig_t LedConfig;

LedConfig.PinNumber    = 5;
LedConfig.Mode         = GPIO_MODE_OUTPUT;
LedConfig.Speed        = GPIO_SPEED_HIGH;
LedConfig.OutputType   = OUTPUT_TYPE_PP;
LedConfig.PuPdControl  = PUPD_NO_PUPD;

GPIO_Init(GPIOA, &LedConfig);

while(1)
{
    GPIO_TogglePin(GPIOA, 5);
}
```

### I2C

```c
I2C_Handle_t hi2c1;

hi2c1.pI2Cx = I2C1;

I2C_Init(&hi2c1);

I2C_WriteRegister(
    I2C1,
    OLED_ADDRESS,
    0x00,
    0xAF
);
```

### SPI

```c
SPI_Handle_t hspi1;

hspi1.pSPIx = SPI1;

hspi1.SPIConfig.DeviceMode = SPI_MASTER;
hspi1.SPIConfig.BusConfig  = SPI_FULL_DUPLEX;
hspi1.SPIConfig.SclkSpeed  = SPI_DIV16;
hspi1.SPIConfig.DFF        = SPI_DFF_8BIT;
hspi1.SPIConfig.CPOL       = SPI_CPOL_LOW;
hspi1.SPIConfig.CPHA       = SPI_CPHA_LOW;
hspi1.SPIConfig.SSM        = SPI_SSM_EN;

SPI_Init(&hspi1);

SPI_Transmit(
    SPI1,
    txBuffer,
    sizeof(txBuffer)
);
```

---

## Learning Objectives

This repository focuses on understanding:

* Register-Level Programming
* Embedded C
* Firmware Architecture
* Peripheral Driver Development
* Hardware Abstraction Design
* Cortex-M4 Internals
* Memory-Mapped I/O
* Startup Code
* Vector Tables
* Linker Scripts
* Interrupt Handling
* Debugging with GDB and OpenOCD
* Embedded Linux Development Workflow

---

## Future Goals

Planned additions include:

* USART Driver
* Interrupt-Driven Drivers
* DMA Support
* EXTI Driver
* General Purpose Timers
* PWM Driver
* ADC Driver
* SSD1306 OLED Graphics Library
* FreeRTOS Integration
* Unit Testing Infrastructure
* Continuous Integration using GitHub Actions
* Documentation Website

---

## Why This Project?

Many Embedded projects rely heavily on vendor libraries that abstract away hardware details.

While those libraries are valuable in production environments, this project focuses on understanding what happens beneath those abstractions.

By implementing drivers directly from the reference manual, I aim to build a stronger foundation in:

* Embedded Systems
* Firmware Engineering
* Real-Time Systems
* ARM Cortex-M Architecture
* Hardware-Software Integration

---

## Author

ECE Student passionate about:

* Embedded Systems
* Firmware Development
* STM32 Microcontrollers
* ARM Architecture
* Linux
* Open Source Software

---

## License

Licensed under the MIT License.

