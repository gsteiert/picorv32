// simple downcounter for femtosoc

#include <stdint.h>

#define reg_leds (*(volatile uint32_t*)0x04000000)
#define DELAY_CNT 600000

void main() {
    int32_t i = -1;
    int32_t dly = 0;
    while(1) {
        i -= 1;
        reg_leds = i;
        dly = DELAY_CNT;
        while(dly > 0) {
            dly -= 1;
        }
    }

}