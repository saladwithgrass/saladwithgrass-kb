#include "clocks.h"
#include "../resets/resets.h"
#include <stdint.h>

void delay ( unsigned int x ) {
    unsigned int ra;
    for (ra = 0; ra < x;) {
        if ( (GET32(SYST_CSR) & (1 << 16)) != 0)
            ra++;
    }
}

void init_xosc() {
    PUT32(XOSC_CTRL_RW, 0xAA0);      //1 - 15MHZ
    PUT32(XOSC_STARTUP_RW, 47);      //straight from the datasheet
    PUT32(XOSC_CTRL_SET, 0xFAB000);  //enablekeb

    // make sure that xosc is running and is stable
    while (1) {
        if ( (GET32(XOSC_STATUS_RW) & 0x80000000) != 0) 
            break;
    }
}

void set_ref_clk_to_xosc() {
    // set xosc as reference clock
    PUT32(CLK_REF_CTRL_RW, 2); //XOSC
}

void init_plls() {
    reset_subsystem(RESET_PLL_SYS);
    unreset_subsystem(RESET_PLL_SYS);

    // turn off plls
    PUT32(PLL_SYS_PWR_SET, 0xffffffff);


    const uint32_t fbdiv = 100; // we want to multply the base freq by 100: 12MHz * 100 = 1200 MHz
    const uint32_t postdiv1 = 6;
    const uint32_t postdiv2 = 2;
    // what will happen:
    // XOSC_HZ * fbdiv / (postdiv1 * postdiv2) = 12 * 100 / (6 * 2) = 100 MHz
    // setup ref divider
    PUT32(PLL_SYS_CS_RW, 1);
    // setup feedback divider
    PUT32(PLL_SYS_FBDIV_INT_RW, fbdiv);

    // power PLL and feedback div on
    PUT32(PLL_SYS_PWR_CLR, (
                PLL_SYS_PWR_PD_BITS | 
                PLL_SYS_PWR_VCOPD_BITS
                )
    );

    // wait for PLL to lock
    // while (!(PLL_SYS_CS_RW & (1<<31))) {}

    // setup post divider
    PUT32(PLL_SYS_PRIM_RW, (postdiv1 << 16) | (postdiv2 << 12));
    // turn post dividers on
    PUT32(PLL_SYS_PWR_CLR, PLL_SYS_PWR_POSTDIVPD_BITS);

}

void set_sys_clk_to_pll() {
    PUT32(CLK_SYS_CTRL_RW, (0x1)); //reset/clk_ref
}

void clock_init ( void ) {
    // reset all resuscitation
    PUT32(CLK_SYS_RESUS_CTRL_RW, 0);
    init_xosc();

    set_ref_clk_to_xosc();
    // set clk_ref to default XOSC
    init_plls();
    // PUT32(CLK_SYS_CTRL_RW, 0); //reset/clk_ref
    set_sys_clk_to_pll();

    // configure clocks for cortex m0 
    PUT32(SYST_CSR, 0x00000004);
    PUT32(SYST_RVR, 100000-1);
    PUT32(SYST_CVR, 100000-1);
    PUT32(SYST_CSR, 0x00000005);
}
