// Display library
#ifndef __DISP_H
#define __DISP_H 1

#include <stdint.h>
#include "efb.h"

#define DISP_I2C_ADDR  0x78
#define DISP_COMMAND   0x00
#define DISP_DATA      0x40
#define DISP_1ST_PAGE  3456

int32_t disp_init(efb_t *efb);
int32_t disp_fill(uint8_t data);
int32_t disp_whex(uint32_t x, uint32_t y, uint32_t data);

#endif