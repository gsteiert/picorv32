// simple downcounter for femtosoc

#include <stdint.h>

#define reg_leds (*(volatile uint32_t*)0x01000000)
#define DELAY_CNT 1000

#define TCCR0 (*(volatile uint32_t*)0x04000178)
#define TCCR1 (*(volatile uint32_t*)0x0400017C)
#define TCTOPSET0 (*(volatile uint32_t*)0x04000180)
#define TCTOPSET1 (*(volatile uint32_t*)0x04000184)
#define TCOCRSET0 (*(volatile uint32_t*)0x04000188)
#define TCOCRSET1 (*(volatile uint32_t*)0x0400018C)
#define TCCR2 (*(volatile uint32_t*)0x04000190)


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
    // TCTOPSET0 = 0x00;
    // TCTOPSET1 = 0x01;
    // TCOCRSET0 = 0x10;
    // TCOCRSET1 = 0x00;
    // TCCR0 = 0x22;
    // TCCR1 = 0x1A;
    delay_ms(1000);
    int32_t i = -1;
    while(1) {
        i -= 1;
        reg_leds = i >> 7;
        TCOCRSET0 = i;        
        delay_ms(5);
    }
}