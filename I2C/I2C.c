#include <stdint.h>
#include "GPIO.h"
#include "I2C.h"

void HAL_I2C_Init(I2C_TypeDef *i2cx)
{
if (i2cx == I2C1)
{
    RCC->APB1ENR |= (1U << 21); // Enable I2C1 clock
    RCC->AHB1ENR |= (1U << 1);  // Enable GPIOB clock

    // Pins 8 and 9
    GPIOB->GPIO_MODER &= ~((3U << 16) | (3U << 18));
    GPIOB->GPIO_MODER |=  ((2U << 16) | (2U << 18)); 

    GPIOB->GPIO_OTYPER |= ((1U << 8) | (1U << 9));       

    GPIOB->GPIO_PUPDR &= ~((3U << 16) | (3U << 18));
    GPIOB->GPIO_PUPDR |=  ((1U << 16) | (1U << 18)); 

    GPIOB->GPIO_AFRH  &= ~((15U << 0) | (15U << 4));
    GPIOB->GPIO_AFRH  |=  ((4U << 0) | (4U << 4)); 
    
    I2C1->CR2   = 42;
    I2C1->CCR   = 210;
    I2C1->TRISE = 43;

    I2C1->CR1 |= (1U << 10); // ACK
    I2C1->CR1 |= (1U << 0);  // PE
}
else if (i2cx == I2C2)
{
    RCC->APB1ENR |= (1U << 22); // Enable I2C2 clock
    RCC->AHB1ENR |= (1U << 1);  // Enable GPIOB clock

    // Pins 10 and 11
    GPIOB->GPIO_MODER &= ~((3U << 20) | (3U << 22));
    GPIOB->GPIO_MODER |=  ((2U << 20) | (2U << 22)); 

    GPIOB->GPIO_OTYPER |= ((1U << 10) | (1U << 11));       

    GPIOB->GPIO_PUPDR &= ~((3U << 20) | (3U << 22));
    GPIOB->GPIO_PUPDR |=  ((1U << 20) | (1U << 22)); 

    GPIOB->GPIO_AFRH  &= ~((15U << 8) | (15U << 12));
    GPIOB->GPIO_AFRH  |=  ((4U << 8) | (4U << 12)); 
    
    I2C2->CR2   = 42;
    I2C2->CCR   = 210;
    I2C2->TRISE = 43;

    I2C2->CR1 |= (1U << 10); // ACK
    I2C2->CR1 |= (1U << 0);  // PE
}
else if (i2cx == I2C3)
{
    RCC->APB1ENR |= (1U << 23); // Enable I2C3 clock
    RCC->AHB1ENR |= ((1U << 0) | (1U << 2)); // Enable GPIOA and GPIOC clock

    // Pin A8
    GPIOA->GPIO_MODER  &= ~(3U << 16);
    GPIOA->GPIO_MODER  |=  (2U << 16);
    GPIOA->GPIO_OTYPER |=  (1U << 8);
    GPIOA->GPIO_PUPDR  &= ~(3U << 16);
    GPIOA->GPIO_PUPDR  |=  (1U << 16);
    GPIOA->GPIO_AFRH   &= ~(15U << 0);
    GPIOA->GPIO_AFRH   |=  (4U << 0); 
    
    // Pin C9
    GPIOC->GPIO_MODER  &= ~(3U << 18);
    GPIOC->GPIO_MODER  |=  (2U << 18);
    GPIOC->GPIO_OTYPER |=  (1U << 9);
    GPIOC->GPIO_PUPDR  &= ~(3U << 18);
    GPIOC->GPIO_PUPDR  |=  (1U << 18);
    GPIOC->GPIO_AFRH   &= ~(15U << 4);
    GPIOC->GPIO_AFRH   |=  (4U << 4);

    I2C3->CR2   = 42;
    I2C3->CCR   = 210;
    I2C3->TRISE = 43;

    I2C3->CR1 |= (1U << 10); // ACK
    I2C3->CR1 |= (1U << 0);  // PE
}

}

void I2C_GenerateStart(I2C_TypeDef *i2cx)
{
    i2cx->CR1 |= I2C_CR1_START;

    while (!(i2cx->SR1 & I2C_SR1_SB));
}

void I2C_SendAddress(I2C_TypeDef *i2cx, uint8_t address, uint8_t rw)
{
    volatile uint32_t temp;

    i2cx->DR = (address << 1) | rw;

    while (!(i2cx->SR1 & I2C_SR1_ADDR));

    /* Clear ADDR flag sequence */
    temp = i2cx->SR1;
    temp = i2cx->SR2;
    (void)temp;
}

void I2C_WriteByte(I2C_TypeDef *i2cx, uint8_t data)
{
    while (!(i2cx->SR1 & I2C_SR1_TXE));

    i2cx->DR = data;

    while (!(i2cx->SR1 & I2C_SR1_BTF));
}

void I2C_GenerateStop(I2C_TypeDef *i2cx)
{
    i2cx->CR1 |= I2C_CR1_STOP;
}

void I2C_WriteRegister(I2C_TypeDef *i2cx, uint8_t slave_addr, uint8_t reg_addr, uint8_t data)
{
    I2C_GenerateStart(i2cx);
    I2C_SendAddress(i2cx, slave_addr, I2C_WRITE);
    I2C_WriteByte(i2cx, reg_addr);
    I2C_WriteByte(i2cx, data);
    I2C_GenerateStop(i2cx);
}

uint8_t I2C_ReadByte_NACK(I2C_TypeDef *i2cx)
{
    i2cx->CR1 &= ~I2C_CR1_ACK;

    while (!(i2cx->SR1 & I2C_SR1_RXNE));

    return (uint8_t)i2cx->DR;
}

uint8_t I2C_ReadRegister(I2C_TypeDef *i2cx, uint8_t slave_addr, uint8_t reg_addr)
{
    uint8_t data;

    I2C_GenerateStart(i2cx);
    I2C_SendAddress(i2cx, slave_addr, I2C_WRITE);
    I2C_WriteByte(i2cx, reg_addr);

    I2C_GenerateStart(i2cx);
    I2C_SendAddress(i2cx, slave_addr, I2C_READ);

    data = I2C_ReadByte_NACK(i2cx);
    I2C_GenerateStop(i2cx);

    /* Restore ACK for future multiple byte reads if needed */
    i2cx->CR1 |= I2C_CR1_ACK;

    return data;
}

