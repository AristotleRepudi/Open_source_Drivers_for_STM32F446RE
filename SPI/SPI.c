#include <stdint.h>
#include "SPI.h"
#include "GPIO.h"

void SPI_PeriClockControl(SPI_TypeDef *spix)
{
    if(spix == SPI1)
        RCC->APB2ENR |= (1U << 12);

    else if(spix == SPI2)
        RCC->APB1ENR |= (1U << 14);

    else if(spix == SPI3)
        RCC->APB1ENR |= (1U << 15);

    else if(spix == SPI4)
        RCC->APB2ENR |= (1U << 13);
}

void SPI_GPIO_Init(SPI_TypeDef *spix)
{
    if(spix == SPI1)
    {
        RCC->AHB1ENR |= (1U << 0);

        GPIOA->GPIO_MODER   &= ~((3U << (5*2)) | (3U << (6*2)) | (3U << (7*2)));
        GPIOA->GPIO_MODER   |=  ((2U << (5*2)) | (2U << (6*2)) | (2U << (7*2)));

        GPIOA->GPIO_OTYPER  &= ~((1U << 5) | (1U << 6) | (1U << 7));

        GPIOA->GPIO_OSPEEDR &= ~((3U << (5*2)) | (3U << (6*2)) | (3U << (7*2)));
        GPIOA->GPIO_OSPEEDR |=  ((3U << (5*2)) | (3U << (6*2)) | (3U << (7*2)));

        GPIOA->GPIO_PUPDR   &= ~((3U << (5*2)) | (3U << (6*2)) | (3U << (7*2)));

        GPIOA->GPIO_AFRL    &= ~((0xFU << (5*4)) | (0xFU << (6*4)) | (0xFU << (7*4)));
        GPIOA->GPIO_AFRL    |=  ((0x5U << (5*4)) | (0x5U << (6*4)) | (0x5U << (7*4)));
    }
    else if(spix == SPI2)
    {
        RCC->AHB1ENR |= (1U << 1);

        GPIOB->GPIO_MODER   &= ~((3U << (13*2)) | (3U << (14*2)) | (3U << (15*2)));
        GPIOB->GPIO_MODER   |=  ((2U << (13*2)) | (2U << (14*2)) | (2U << (15*2)));

        GPIOB->GPIO_OTYPER  &= ~((1U << 13) | (1U << 14) | (1U << 15));

        GPIOB->GPIO_OSPEEDR &= ~((3U << (13*2)) | (3U << (14*2)) | (3U << (15*2)));
        GPIOB->GPIO_OSPEEDR |=  ((3U << (13*2)) | (3U << (14*2)) | (3U << (15*2)));

        GPIOB->GPIO_PUPDR   &= ~((3U << (13*2)) | (3U << (14*2)) | (3U << (15*2)));

        GPIOB->GPIO_AFRH    &= ~((0xFU << ((13-8)*4)) | (0xFU << ((14-8)*4)) | (0xFU << ((15-8)*4)));
        GPIOB->GPIO_AFRH    |=  ((0x5U << ((13-8)*4)) | (0x5U << ((14-8)*4)) | (0x5U << ((15-8)*4)));
    }
    else if(spix == SPI3)
    {
        RCC->AHB1ENR |= (1U << 2);

        GPIOC->GPIO_MODER   &= ~((3U << (10*2)) | (3U << (11*2)) | (3U << (12*2)));
        GPIOC->GPIO_MODER   |=  ((2U << (10*2)) | (2U << (11*2)) | (2U << (12*2)));

        GPIOC->GPIO_OTYPER  &= ~((1U << 10) | (1U << 11) | (1U << 12));

        GPIOC->GPIO_OSPEEDR &= ~((3U << (10*2)) | (3U << (11*2)) | (3U << (12*2)));
        GPIOC->GPIO_OSPEEDR |=  ((3U << (10*2)) | (3U << (11*2)) | (3U << (12*2)));

        GPIOC->GPIO_PUPDR   &= ~((3U << (10*2)) | (3U << (11*2)) | (3U << (12*2)));

        GPIOC->GPIO_AFRH    &= ~((0xFU << ((10-8)*4)) | (0xFU << ((11-8)*4)) | (0xFU << ((12-8)*4)));
        GPIOC->GPIO_AFRH    |=  ((0x6U << ((10-8)*4)) | (0x6U << ((11-8)*4)) | (0x6U << ((12-8)*4)));
    }
}

void SPI_Init(SPI_Handle_t *spi)
{
    SPI_PeriClockControl(spi->pSPIx);

    SPI_GPIO_Init(spi->pSPIx);

    uint32_t temp = 0;

    temp |= spi->SPIConfig.DeviceMode;
    temp |= spi->SPIConfig.BusConfig;
    temp |= spi->SPIConfig.SclkSpeed;
    temp |= spi->SPIConfig.DFF;
    temp |= spi->SPIConfig.CPOL;
    temp |= spi->SPIConfig.CPHA;
    temp |= spi->SPIConfig.SSM;

    spi->pSPIx->CR1 = temp;

    if(spi->SPIConfig.SSM == SPI_SSM_EN)
    {
        spi->pSPIx->CR1 |= (1U << SPI_CR1_SSI);
    }

    spi->pSPIx->CR1 |= (1U << SPI_CR1_SPE);
}

void SPI_Transmit(SPI_TypeDef *spix, uint8_t *pData, uint32_t length)
{
    while(length > 0)
    {
        while(!(spix->SR & (1U << 1)));

        if(spix->CR1 & (1U << SPI_CR1_DFF))
        {
            spix->DR = *((uint16_t*)pData);

            pData += 2;
            length -= 2;
            if(length < 2)
            break;
        }
        
        else
        {
            *((volatile uint8_t*)&spix->DR) = *pData;

            pData++;
            length--;
        }
    }

    while(spix->SR & (1U << 7));
}

void SPI_Receive(SPI_TypeDef *spix, uint8_t *pData, uint32_t length)
{
    for(uint32_t i = 0; i < length; i++)
    {
        while(!(spix->SR & (1U<<1)));
        spix->DR = 0xFF;

        while(!(spix->SR & (1U<<0)));

        pData[i] = (uint8_t)spix->DR;
    }
}

