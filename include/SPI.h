#ifndef SPI_H
#define SPI_H

#include <stdint.h>

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;
    volatile uint32_t I2SCFGR;
    volatile uint32_t I2SPR;
} SPI_TypeDef;

typedef struct {
    uint32_t DeviceMode;      
    uint32_t BusConfig;       
    uint32_t SclkSpeed;       
    uint32_t DFF;             
    uint32_t CPOL;            
    uint32_t CPHA;            
    uint32_t SSM;             
} SPI_Config_t;

typedef struct {
    SPI_TypeDef *pSPIx;      
    SPI_Config_t SPIConfig;
} SPI_Handle_t;

#define SPI_CR1_CPHA        0
#define SPI_CR1_CPOL        1
#define SPI_CR1_MSTR        2
#define SPI_CR1_BR          3
#define SPI_CR1_SPE         6
#define SPI_CR1_LSBFIRST    7
#define SPI_CR1_SSI         8
#define SPI_CR1_SSM         9
#define SPI_CR1_RXONLY      10
#define SPI_CR1_DFF         11
#define SPI_CR1_CRCNEXT     12
#define SPI_CR1_CRCEN       13
#define SPI_CR1_BIDIOE      14
#define SPI_CR1_BIDIMODE    15
#define SPI_SLAVE           0
#define SPI_MASTER          (1U << SPI_CR1_MSTR)
#define SPI_FULL_DUPLEX     0
#define SPI_HALF_DUPLEX     (1U << SPI_CR1_BIDIMODE)
#define SPI_SIMPLEX_RX      (1U << SPI_CR1_RXONLY)
#define SPI_DIV2            (0U << SPI_CR1_BR)
#define SPI_DIV4            (1U << SPI_CR1_BR)
#define SPI_DIV8            (2U << SPI_CR1_BR)
#define SPI_DIV16           (3U << SPI_CR1_BR)
#define SPI_DIV32           (4U << SPI_CR1_BR)
#define SPI_DIV64           (5U << SPI_CR1_BR)
#define SPI_DIV128          (6U << SPI_CR1_BR)
#define SPI_DIV256          (7U << SPI_CR1_BR)
#define SPI_DFF_8BIT        0
#define SPI_DFF_16BIT       (1U << SPI_CR1_DFF)
#define SPI_CPOL_LOW        0
#define SPI_CPOL_HIGH       (1U << SPI_CR1_CPOL)
#define SPI_CPHA_LOW        0
#define SPI_CPHA_HIGH       (1U << SPI_CR1_CPHA)
#define SPI_SSM_DI          0
#define SPI_SSM_EN          (1U << SPI_CR1_SSM)
#define SPI_ENABLE          (1U << SPI_CR1_SPE)
#define SPI_DISABLE         0



#define SPI1    ((SPI_TypeDef *)0x40013000) 
#define SPI2    ((SPI_TypeDef *)0x40003800)
#define SPI3    ((SPI_TypeDef *)0x40003C00)
#define SPI4    ((SPI_TypeDef *)0x40013400)

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_PeriClockControl(SPI_TypeDef *spix);
void SPI_Transmit(SPI_TypeDef *spix,uint8_t *pData,uint32_t length);

void SPI_Receive(SPI_TypeDef *spix,uint8_t *pData,uint32_t length);
#endif
