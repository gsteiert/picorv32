// UFM library
#ifndef __UFM_H
#define __UFM_H 1

#include <stdint.h>
#include "efb.h"

#define UFM_ERROR       -1

int32_t ufm_init(efb_t *efb);
int32_t ufm_read_page(uint32_t page, uint8_t *data);

#endif