// simple downcounter for femtosoc

#include <stdint.h>
#include "efb.h"
#include "i2c.h"
#include "disp.h"

#define WB_BASE   0x04000000
#define EFB_BASE  (WB_BASE + 0x0)
#define EFB       ((efb_t *) EFB_BASE)

#define REG_LEDS (*(volatile uint32_t*)0x01000000)
#define DELAY_CNT 500

void delay_ms(int32_t ms) {
    int32_t dly;
    while(ms > 0) {
        ms -= 1;
        dly = DELAY_CNT;
        while(dly > 0) {
        dly -= 1;
        }
    }
}

void main() {
    REG_LEDS = 0x12;
    i2c_init(EFB);
    REG_LEDS = 0x22;
    disp_init();
    REG_LEDS = 0x32;
    disp_fill(0x00);
    REG_LEDS = 0x42;
    disp_whex(0, 7, 0xDEADBEEF);
    disp_whex(0, 5, 0x01234567);
    disp_whex(48, 5, 0x89ABCDEF);
    
/* */
    delay_ms(1000);
    int32_t i = -1;
    while(1) {
        i += 1;
        REG_LEDS = i >> 8;
        EFB->TCOCRSET[0] = i; 
        if ((i & 0xFF)==0) {
            disp_whex(0,7,i);
        }       
        delay_ms(5);
    }
}