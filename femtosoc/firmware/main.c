// simple downcounter for femtosoc

#include <stdint.h>
#include "efb.h"

#define WB_BASE   0x04000000
#define EFB_BASE  (WB_BASE + 0x0)
#define EFB       ((efb_t *) EFB_BASE)

#define reg_leds (*(volatile uint32_t*)0x01000000)
#define DELAY_CNT 1000



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
    delay_ms(1000);
    int32_t i = -1;
    while(1) {
        i -= 1;
        reg_leds = i >> 8;
        EFB->TCOCRSET[0] = i;        
        delay_ms(5);
    }
}