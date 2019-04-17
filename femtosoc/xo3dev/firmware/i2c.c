// I2C library

#include <stdint.h>
#include "i2c.h"

volatile efb_t *i2c_efb;

int32_t i2c_init(efb_t *efb) {
    i2c_efb = efb;
    i2c_efb->I2C_2_CR = 0x80;
    return i2c_efb->I2C_2_SR;
}

int32_t i2c_wbyte(i2c_cmd_t cmd, uint8_t data) {
    int32_t status = i2c_efb->I2C_2_SR;
    if (status & I2C_BUSY) {
        while((status & I2C_TRRDY)!=I2C_TRRDY) {
            status = i2c_efb->I2C_2_SR;
        }
    }
    i2c_efb->I2C_2_TXDR = data;
    i2c_efb->I2C_2_CMDR = cmd;
    return i2c_efb->I2C_2_SR;
}

int32_t i2c_rbyte(i2c_cmd_t cmd) {
    int trrdy = (i2c_efb->I2C_2_SR & I2C_TRRDY) ;
    while( !trrdy ) {
        trrdy = (i2c_efb->I2C_2_SR & I2C_TRRDY) ;
    }
    i2c_efb->I2C_2_CMDR = cmd;
    trrdy = (i2c_efb->I2C_2_SR & I2C_TRRDY) ;
    while( !trrdy ) {
        trrdy = (i2c_efb->I2C_2_SR & I2C_TRRDY) ;
    }
    return (i2c_efb->I2C_2_RXDR);
}

int32_t i2c_stop() {
    int32_t status = i2c_efb->I2C_2_SR;
    if (status & I2C_BUSY) {
        while((status & I2C_TRRDY)!=I2C_TRRDY) {
            status = i2c_efb->I2C_2_SR;
        }
    }
    i2c_efb->I2C_2_CMDR = I2C_STOP;
    status = i2c_efb->I2C_2_SR;
    while(status & I2C_BUSY) {
        status = i2c_efb->I2C_2_SR;
    }
    return i2c_efb->I2C_2_SR;
}