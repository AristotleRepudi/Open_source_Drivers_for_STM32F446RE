#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

typedef struct{
    volatile uint32_t GPIO_MODER;
    volatile uint32_t GPIO_OTYPER;
    volatile uint32_t GPIO_OSPEEDR;
    volatile uint32_t GPIO_PUPDR;
    volatile uint32_t GPIO_IDR;
    volatile uint32_t GPIO_ODR;
    volatile uint32_t GPIO_BSRR;
    volatile uint32_t GPIO_LCKR;
    volatile uint32_t GPIO_AFRL;
    volatile uint32_t GPIO_AFRH;
} GPIO_TypeDef;

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    uint32_t RESERVED2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
} RCC_TypeDef;

typedef struct{
    uint8_t PinNumber;
    uint8_t Mode;
    uint8_t Speed;
    uint8_t PuPdControl;
    uint8_t OutputType;
    uint8_t AltFunctionMode;
} GPIO_PinConfig_t;

typedef enum{
    GPIO_PinState_RESET=0,
    GPIO_PinState_SET
}GPIO_PinState_t;

#define RCC ((RCC_TypeDef *)0x40023800)
#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830)
#define GPIO_BASE 0x40020000
#define GPIOA ((GPIO_TypeDef *)0x40020000)
#define GPIOB ((GPIO_TypeDef*)0x40020400)
#define GPIOC ((GPIO_TypeDef*)0x40020800)
#define GPIOD ((GPIO_TypeDef*)0x40020C00)
#define GPIOE ((GPIO_TypeDef*)0x40021000)
#define GPIO_MODE_INPUT 0
#define GPIO_MODE_OUTPUT 1
#define GPIO_MODE_AF 2
#define GPIO_MODE_ANALOG 3
#define GPIO_SPEED_LOW 0
#define GPIO_SPEED_MEDIUM 1
#define GPIO_SPEED_HIGH 2
#define GPIO_SPEED_VERY_HIGH 3
#define OUTPUT_TYPE_PP 0
#define OUTPUT_TYPE_OD 1
#define PUPD_NO_PUPD 0
#define PUPD_PULL_UP 1
#define PUPD_PULL_DOWN 2
#define HIGH 1
#define LOW 0
//Yeah, define everything like a maniac

//Now prototypes, because we don't want to be like those people
// who write the entire code in main
// and then wonder why it looks like a mess
void GPIO_Peripheral_Clk(GPIO_TypeDef *GPIOx);
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *GPIO_PinConfig);
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8_t Pin, GPIO_PinState_t val);
uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint8_t Pin);
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint8_t Pin);

#endif
