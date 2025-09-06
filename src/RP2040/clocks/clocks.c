#include "clocks.h"

void delay_ms ( unsigned int ms ) {
    unsigned int ra;
    for (ra = 0; ra < ms;) {
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

    // power pll off
    PUT32(PLL_SYS_PWR_SET, 0xffffffff);  // Clear PD and VCOPD
    // reset PLL
    PUT32(PLL_SYS_CS_RW, (1<<31));
    // ureset PLL
    PUT32(PLL_SYS_CS_RW, 0);

    // set feedback divisor to 125
    PUT32(PLL_SYS_FBDIV_INT_RW, 125);
    PUT32(PLL_SYS_PRIM_RW,  (6 << 16) | (2 << 12));

    // power pll back on
    PUT32(PLL_SYS_PWR_CLR, 0xffffffff);

    // wait for lock
    while (1) {
        if ( (GET32(PLL_SYS_CS_RW) & (1 << 31)) != 0)  // Check LOCK bit
            break;
    }

    // set xosc as reference clock
    PUT32(CLK_REF_CTRL_RW, 2); //XOSC
    // set clk_ref to default XOSC
    PUT32(CLK_SYS_CTRL_RW, (0x00 << 5) | 0x1); // set sys ref clock to aux(0x1) and aux to pll_sys(0x00<<5)

    // configure clocks for cortex m0 
    PUT32(SYST_CSR, 0x00000004);
    PUT32(SYST_RVR, DEFAULT_SYS_KHZ - 1);
    PUT32(SYST_CVR, DEFAULT_SYS_KHZ - 1);
    PUT32(SYST_CSR, 0x00000005);
}

