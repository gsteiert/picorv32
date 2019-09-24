// I2C library
#ifndef __I2C_H
#define __I2C_H 1

#include <stdint.h>
#include "efb.h"

#define I2C_ERROR       -1
#define I2C_TRRDY       (1 << 2)
#define I2C_BUSY        (1 << 6)
#define I2C_READ_BIT    0x01

typedef enum {
    I2C_IDLE = 0x04,            // do nothing
    I2C_WRITE = 0x14,           // write byte
    I2C_READ = 0x24,            // Read byte
    I2C_STOP = 0x44,            // Stop 
    I2C_READ_NACK_STOP = 0x6C,  // Read, Nack and Stop
    I2C_START = 0x94            // Start
} i2c_cmd_t;


int32_t i2c_init(efb_t *efb);
int32_t i2c_wbyte(i2c_cmd_t cmd, uint8_t data);
int32_t i2c_rbyte(i2c_cmd_t cmd);
int32_t i2c_stop();

#endif