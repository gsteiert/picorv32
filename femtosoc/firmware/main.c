// simple downcounter for femtosoc

#include <stdint.h>

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
        reg_leds = i;
        delay_ms(500);
    }
}