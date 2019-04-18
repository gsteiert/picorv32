// Display Library
#include <stdint.h>
#include "efb.h"
#include "i2c.h"
#include "disp.h"

volatile efb_t *disp_efb;

int32_t disp_init(efb_t *efb) {
    disp_efb = efb;
    disp_efb->CFGCR = 0x80;  // open frame
    disp_efb->CFGTXDR = 0x74;
    disp_efb->CFGTXDR = 0x08;
    disp_efb->CFGTXDR = 0x00;
    disp_efb->CFGTXDR = 0x00;
    disp_efb->CFGCR = 0x00;  // close frame

    i2c_wbyte(I2C_START, DISP_I2C_ADDR);
    i2c_wbyte(I2C_WRITE, DISP_COMMAND); 
    i2c_wbyte(I2C_WRITE, 0xAE);  // Display Off
    i2c_stop();

    i2c_wbyte(I2C_START, DISP_I2C_ADDR);
    i2c_wbyte(I2C_WRITE, DISP_COMMAND); 
    i2c_wbyte(I2C_WRITE, 0xA1);  // Segment Re-map
    i2c_stop();

    i2c_wbyte(I2C_START, DISP_I2C_ADDR);
    i2c_wbyte(I2C_WRITE, DISP_COMMAND); 
    i2c_wbyte(I2C_WRITE, 0x8D);  // Charge Pump Command
    i2c_stop();
    i2c_wbyte(I2C_START, DISP_I2C_ADDR);
    i2c_wbyte(I2C_WRITE, DISP_COMMAND); 
    i2c_wbyte(I2C_WRITE, 0x14);  // Charge Pump Enabled
    i2c_stop();

    i2c_wbyte(I2C_START, DISP_I2C_ADDR);
    i2c_wbyte(I2C_WRITE, DISP_COMMAND); 
    i2c_wbyte(I2C_WRITE, 0xAF);  // Display On
    i2c_stop();
    
    return 0x00;
}


int32_t disp_fill(uint8_t data){
    int32_t i, j;
    for (i = 0; i < 8 ; i++) {
        i2c_wbyte(I2C_START, DISP_I2C_ADDR);
        i2c_wbyte(I2C_WRITE, DISP_COMMAND); 
        i2c_wbyte(I2C_WRITE, (0xB0|i));  // Page i
        i2c_stop();
        i2c_wbyte(I2C_START, DISP_I2C_ADDR);
        i2c_wbyte(I2C_WRITE, DISP_COMMAND); 
        i2c_wbyte(I2C_WRITE, 0x10);  // Column 0x0_
        i2c_stop();
        i2c_wbyte(I2C_START, DISP_I2C_ADDR);
        i2c_wbyte(I2C_WRITE, DISP_COMMAND); 
        i2c_wbyte(I2C_WRITE, 0x00);  // Column 0x_0
        i2c_stop();
        for (j= 0; j < 128; j++){
            i2c_wbyte(I2C_START, DISP_I2C_ADDR);
            i2c_wbyte(I2C_WRITE, DISP_DATA); 
            i2c_wbyte(I2C_WRITE, data);  // fill data
            i2c_stop();
        }
    }
    return 0x00;
}


int32_t disp_whex(uint32_t x, uint32_t y, uint32_t data){
    i2c_wbyte(I2C_START, DISP_I2C_ADDR);
    i2c_wbyte(I2C_WRITE, DISP_COMMAND); 
    i2c_wbyte(I2C_WRITE, (0xB0|y));  // Page y
    i2c_stop();
    i2c_wbyte(I2C_START, DISP_I2C_ADDR);
    i2c_wbyte(I2C_WRITE, DISP_COMMAND); 
    i2c_wbyte(I2C_WRITE, (0x10|((x>>4)&0x0F)));  // Column x high nibble
    i2c_stop();
    i2c_wbyte(I2C_START, DISP_I2C_ADDR);
    i2c_wbyte(I2C_WRITE, DISP_COMMAND); 
    i2c_wbyte(I2C_WRITE, (x&0x0F));  // Column x low nibble
    i2c_stop();
    static int32_t h, i, j;
    for (i = 7; i >= 0 ; i--) {
        h = ((data >> (i << 2))&0x0F)+DISP_1ST_PAGE;
        disp_efb->CFGCR = 0x80;  // open frame
        disp_efb->CFGTXDR = 0xB4; // Set UFM Address
        disp_efb->CFGTXDR = 0x00;
        disp_efb->CFGTXDR = 0x00;
        disp_efb->CFGTXDR = 0x00;
        disp_efb->CFGTXDR = 0x40; // UFM Address
        disp_efb->CFGTXDR = 0x00;
        disp_efb->CFGTXDR = (h >> 8); // 
        disp_efb->CFGTXDR = h;   // wishbone implementation ignores higher bits
        disp_efb->CFGCR = 0x00;  // close frame
        disp_efb->CFGCR = 0x80;  // open frame
        disp_efb->CFGTXDR = 0xCA; // Read UFM
        disp_efb->CFGTXDR = 0x10;
        disp_efb->CFGTXDR = 0x00;
        disp_efb->CFGTXDR = 0x01; // 1 page
        for (j= 0; j < 5; j++){
            i2c_wbyte(I2C_START, DISP_I2C_ADDR);
            i2c_wbyte(I2C_WRITE, DISP_DATA); 
            i2c_wbyte(I2C_WRITE, (disp_efb->CFGRXDR));  // hex digit data
            i2c_stop();
        }
        disp_efb->CFGCR = 0x00;  // close frame
        i2c_wbyte(I2C_START, DISP_I2C_ADDR);
        i2c_wbyte(I2C_WRITE, DISP_DATA); 
        i2c_wbyte(I2C_WRITE, 0x00);  
        i2c_stop();

    }
    return 0x00;
}
