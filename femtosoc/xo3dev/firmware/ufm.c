// UFM library

#include <stdint.h>
#include "efb.h"
#include "ufm.h"

volatile efb_t *ufm_efb;

int32_t ufm_init(efb_t *efb) {
    ufm_efb = efb;
    ufm_efb->CFGCR = 0x80;  // open frame
    ufm_efb->CFGTXDR = 0x74; 
    ufm_efb->CFGTXDR = 0x08;
    ufm_efb->CFGTXDR = 0x00;
    ufm_efb->CFGTXDR = 0x00;
    ufm_efb->CFGCR = 0x00;  // close frame
    return 0;
}

int32_t ufm_read_page(uint32_t page, uint8_t *data){
        ufm_efb->CFGCR = 0x80;  // open frame
        ufm_efb->CFGTXDR = 0xB4; // Set UFM Address
        ufm_efb->CFGTXDR = 0x00;
        ufm_efb->CFGTXDR = 0x00;
        ufm_efb->CFGTXDR = 0x00;
        ufm_efb->CFGTXDR = 0x40; // UFM Address
        ufm_efb->CFGTXDR = 0x00;
        ufm_efb->CFGTXDR = (page >> 8); // 
        ufm_efb->CFGTXDR = page;   // wishbone implementation ignores higher bits
        ufm_efb->CFGCR = 0x00;  // close frame
        ufm_efb->CFGCR = 0x80;  // open frame
        ufm_efb->CFGTXDR = 0xCA; // Read UFM
        ufm_efb->CFGTXDR = 0x10;
        ufm_efb->CFGTXDR = 0x00;
        ufm_efb->CFGTXDR = 0x01; // 1 page
        for (int i= 0; i < 16; i++){
            data[i] = ufm_efb->CFGRXDR;  // read byte
        }
        ufm_efb->CFGCR = 0x00;  // close frame
    return 0;
}
