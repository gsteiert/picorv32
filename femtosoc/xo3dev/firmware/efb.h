#include <stdint.h>

#define __I    volatile const
#define __O    volatile
#define __IO   volatile

typedef struct
{
    __IO uint32_t PLL0[32]; // 0x00-0x1F PLL0 Dynamic Access
    __IO uint32_t PLL1[32]; // 0x20-0x3F PLL1 Dynamic Access
    __IO uint32_t I2C_1_CR; // 0x40 I2C Control
    __IO uint32_t I2C_1_CMDR; // 0x41 I2C Command
    __IO uint32_t I2C_1_BR[2]; // 0x42-0x43 I2C Clock Pre-scale
    __O  uint32_t I2C_1_TXDR; // 0x44 I2C Transmit Data
    __I  uint32_t I2C_1_SR; // 0x45 I2C Status
    __I  uint32_t I2C_1_GCDR; // 0x46 I2C General Call
    __I  uint32_t I2C_1_RXDR; // 0x47 I2C Receive Data
    __IO uint32_t I2C_1_IRQ; // 0x48 I2C Interrupt Request
    __IO uint32_t I2C_1_IRQEN; // 0x49 I2C Interrupt Request Enable
    __IO uint32_t I2C_2_CR; // 0x4A I2C Control
    __IO uint32_t I2C_2_CMDR; // 0x4B I2C Command
    __IO uint32_t I2C_2_BR[2]; // 0x4C-0x4D I2C Clock Pre-scale
    __O  uint32_t I2C_2_TXDR; // 0x4E I2C Transmit Data
    __I  uint32_t I2C_2_SR; // 0x4F I2C Status
    __I  uint32_t I2C_2_GCDR; // 0x50 I2C General Call
    __I  uint32_t I2C_2_RXDR; // 0x51 I2C Receive Data
    __IO uint32_t I2C_2_IRQ; // 0x52 I2C Interrupt Request
    __IO uint32_t I2C_2_IRQEN; // 0x53 I2C Interrupt Request Enable
    __IO uint32_t SPICR0; // 0x54 SPI Control Register 0
    __IO uint32_t SPICR1; // 0x55 SPI Control Register 1
    __IO uint32_t SPICR2; // 0x56 SPI Control Register 2
    __IO uint32_t SPIBR; // 0x57 SPI Clock Pre-scale
    __IO uint32_t SPICSR; // 0x58 SPI Master Chip Select
    __O  uint32_t SPITXDR; // 0x59 SPI Transmit Data
    __I  uint32_t SPISR; // 0x5A SPI Status
    __I  uint32_t SPIRXDR; // 0x5B SPI Receive Data
    __IO uint32_t SPIIRQ; // 0x5C SPI Interrupt Request
    __IO uint32_t SPIIRQEN; // 0x5D SPI Interrupt Request Enable
    __IO uint32_t TCCR0; // 0x5E Timer/Counter Control Register 0
    __IO uint32_t TCCR1; // 0x5F Timer/Counter Control Register 1
    __O  uint32_t TCTOPSET[2]; // 0x60-0x61 Timer/Counter Set Top Counter Value
    __O  uint32_t TCOCRSET[2]; // 0x62-0x63 Timer/Counter Set Compare Counter Value
    __IO uint32_t TCCR2; // 0x64 Timer/Counter Control Register 2
    __I  uint32_t TCCNT[2]; // 0x65-0x66 Timer/Counter Counter Value 
    __I  uint32_t TCTOP[2]; // 0x67-0x68 Timer/Counter Current Top Counter Value
    __I  uint32_t TCOCR[2]; // 0x69-0x6A Timer/Counter Current Compare Counter Value
    __I  uint32_t TCICR[2]; // 0x6B-0x6C Timer/Counter Current Capture Counter Value
    __IO uint32_t TCSR0; // 0x6D Timer/Counter Status Register
    __IO uint32_t TCIRQ; // 0x6E Timer/Counter Interrupt Request
    __IO uint32_t TCIRQEN; // 0x6F Timer/Counter Interrupt Request Enable
    __IO uint32_t CFGCR; // 0x70 Configuration Control
    __O  uint32_t CFGTXDR; // 0x71 Configuration Transmit Data
    __I  uint32_t CFGSR; // 0x72 Configuration Status
    __I  uint32_t CFGRXDR; // 0x73 Configuration Receive Data
    __IO uint32_t CFGIRQ; // 0x74 Configuration Interrupt Request
    __IO uint32_t CFGIRQEN; // 0x75 Configuration Interrupt Request Enable
    __I  uint32_t UNUSED; // 0x76 Reserved Register
    __I  uint32_t EFBIRQ; // 0x77 EFB Interrupt Source
}  efb_t;
