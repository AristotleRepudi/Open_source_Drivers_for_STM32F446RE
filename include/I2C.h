#ifndef I2C_H
#define I2C_H

#include <stdint.h>

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
    volatile uint32_t FLTR;
} I2C_TypeDef;

#define I2C_CR1_PE       (1U << 0)
#define I2C_CR1_START    (1U << 8)
#define I2C_CR1_STOP     (1U << 9)
#define I2C_CR1_ACK      (1U << 10)
#define I2C_SR1_SB       (1U << 0)
#define I2C_SR1_ADDR     (1U << 1)
#define I2C_SR1_BTF      (1U << 2)

#define I2C_SR1_RXNE     (1U << 6)
#define I2C_SR1_TXE      (1U << 7)

#define I2C1 ((I2C_TypeDef *)0x40005400)
#define I2C2 ((I2C_TypeDef *)0x40005800)
#define I2C3 ((I2C_TypeDef *)0x40005C00)

#define I2C_WRITE 0
#define I2C_READ  1

void HAL_I2C_Init(I2C_TypeDef *i2cx);

void I2C_GenerateStart(I2C_TypeDef *i2cx);
void I2C_GenerateStop(I2C_TypeDef *i2cx);

void I2C_SendAddress(I2C_TypeDef *i2cx,uint8_t address,uint8_t rw);

void I2C_WriteByte(I2C_TypeDef *i2cx,uint8_t data);

uint8_t I2C_ReadByte_NACK(I2C_TypeDef *i2cx);

void I2C_WriteRegister(I2C_TypeDef *i2cx,uint8_t slave_addr,uint8_t reg_addr,uint8_t data);

uint8_t I2C_ReadRegister(I2C_TypeDef *i2cx,uint8_t slave_addr,uint8_t reg_addr);

#endif
