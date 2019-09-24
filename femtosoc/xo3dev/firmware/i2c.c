// I2C library

#include <stdint.h>
#include "i2c.h"

volatile efb_t *i2c_efb;

int32_t i2c_init(efb_t *efb) {
    i2c_efb = efb;
    i2c_efb->I2C_2_CR = 0x80;
    return 0;
}

int32_t i2c_wbyte(i2c_cmd_t cmd, uint8_t data) {
    if (i2c_efb->I2C_2_SR & I2C_BUSY) {
        while(!(i2c_efb->I2C_2_SR & I2C_TRRDY));
    }
    i2c_efb->I2C_2_TXDR = data;
    i2c_efb->I2C_2_CMDR = cmd;
    return 0;
}

int32_t i2c_rbyte(i2c_cmd_t cmd) {
    i2c_efb->I2C_2_CMDR = cmd;
    while(!(i2c_efb->I2C_2_SR & I2C_TRRDY));
    return (i2c_efb->I2C_2_RXDR);
}

int32_t i2c_stop() {
    if (i2c_efb->I2C_2_SR & I2C_BUSY) {
        while(!(i2c_efb->I2C_2_SR & I2C_TRRDY));
    }
    i2c_efb->I2C_2_CMDR = I2C_STOP;
    while(i2c_efb->I2C_2_SR & I2C_BUSY);
    return 0;
}