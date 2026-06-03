#include "GPIO.h"


//You forgot to turn on the clk? Did you forget to eat?
void GPIO_Peripheral_Clk(GPIO_TypeDef *GPIOx){
        uint32_t x=((uint32_t)GPIOx-(uint32_t)GPIO_BASE)/0x400;
    RCC_AHB1ENR|=(1<<x);
}

void GPIO_Init(GPIO_TypeDef *GPIOx,GPIO_PinConfig_t *GPIO_PinConfig){
    GPIO_Peripheral_Clk(GPIOx);

    //New lines since reader doesn't go insane

    // Clear field before writing new configuration
    GPIOx->GPIO_MODER&=~(3U<<(2*GPIO_PinConfig->PinNumber));
    GPIOx->GPIO_MODER|=(GPIO_PinConfig->Mode<<(2*GPIO_PinConfig->PinNumber));

    GPIOx->GPIO_OTYPER &=~(1U << GPIO_PinConfig->PinNumber);
    GPIOx->GPIO_OTYPER|=(GPIO_PinConfig->OutputType<<GPIO_PinConfig->PinNumber);

    GPIOx->GPIO_OSPEEDR&=~(3U<<(2*GPIO_PinConfig->PinNumber));
    GPIOx->GPIO_OSPEEDR|=(GPIO_PinConfig->Speed<<(2*GPIO_PinConfig->PinNumber));

    GPIOx->GPIO_PUPDR&=~(3U<<(2*GPIO_PinConfig->PinNumber));
    GPIOx->GPIO_PUPDR|=(GPIO_PinConfig->PuPdControl<<(2*GPIO_PinConfig->PinNumber));

    if(GPIO_PinConfig->Mode==GPIO_MODE_AF){
        if(GPIO_PinConfig->PinNumber<8){
            GPIOx->GPIO_AFRL&=~(15U<<(4*GPIO_PinConfig->PinNumber));
            GPIOx->GPIO_AFRL|=(GPIO_PinConfig->AltFunctionMode<<(4*GPIO_PinConfig->PinNumber));
        }
        else{
            uint8_t temp=(GPIO_PinConfig->PinNumber)-8;
            GPIOx->GPIO_AFRH&=~(15U<<(4*temp));
            GPIOx->GPIO_AFRH|=(GPIO_PinConfig->AltFunctionMode<<(4*temp));
        }
    }
}

void GPIO_WritePin(GPIO_TypeDef *GPIOx,uint8_t Pin, GPIO_PinState_t val){
    //Pretty self-Explanatory, BSRR-Bit set and reset register
    if(val==GPIO_PinState_SET)
        GPIOx->GPIO_BSRR=(1U<<Pin);
    else
        GPIOx->GPIO_BSRR=(1U<<(Pin+16));
}

uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint8_t Pin){
    return (GPIOx->GPIO_IDR>>Pin)&1U;
    //Classic shift and mask to snatch the bit we want
}

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint8_t Pin){
    GPIOx->GPIO_ODR^=(1U<<Pin);
    //XOR to toggle
}


