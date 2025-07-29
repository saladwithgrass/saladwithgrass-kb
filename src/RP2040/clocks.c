#include "clocks.h"

void delay ( unsigned int x ) {
    unsigned int ra;
    for (ra = 0; ra < x;) {
        if ( (GET32(SYST_CSR) & (1 << 16)) != 0)
            ra++;
    }
}

void clock_init ( void ) {
    // reset all resuscitation
    PUT32(CLK_SYS_RESUS_CTRL_RW, 0);

    PUT32(XOSC_CTRL_RW, 0xAA0);      //1 - 15MHZ
    PUT32(XOSC_STARTUP_RW, 47);      //straight from the datasheet
    PUT32(XOSC_CTRL_SET, 0xFAB000);  //enablekeb

    // make sure that xosc is running and is stable
    while (1) {
        if ( (GET32(XOSC_STATUS_RW) & 0x80000000) != 0) 
            break;
    }

    // set xosc as reference clock
    PUT32(CLK_REF_CTRL_RW, 2); //XOSC
    // set clk_ref to default XOSC
    PUT32(CLK_SYS_CTRL_RW, 0); //reset/clk_ref

    // configure clocks for cortex m0 
    PUT32(SYST_CSR, 0x00000004);
    PUT32(SYST_RVR, 100000-1);
    PUT32(SYST_CVR, 100000-1);
    PUT32(SYST_CSR, 0x00000005);
}
