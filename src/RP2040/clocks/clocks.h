#ifndef CLOCKS_H
#define CLOCKS_H
#include "../general_defines.h"

void delay(unsigned int x);
void clock_init( void );

#define CLOCKS_BASE                 0x40008000


#define CLK_REF_CTRL_RW             (CLOCKS_BASE+0x30+0x0000)
#define CLK_REF_CTRL_XOR            (CLOCKS_BASE+0x30+0x1000)
#define CLK_REF_CTRL_SET            (CLOCKS_BASE+0x30+0x2000)
#define CLK_REF_CTRL_CLR            (CLOCKS_BASE+0x30+0x3000)

#define CLK_SYS_CTRL_RW             (CLOCKS_BASE+0x3C+0x0000)
#define CLK_SYS_CTRL_XOR            (CLOCKS_BASE+0x3C+0x1000)
#define CLK_SYS_CTRL_SET            (CLOCKS_BASE+0x3C+0x2000)
#define CLK_SYS_CTRL_CLR            (CLOCKS_BASE+0x3C+0x3000)



#define CLK_SYS_RESUS_CTRL_RW       (CLOCKS_BASE+0x78+0x0000)
#define CLK_SYS_RESUS_CTRL_XOR      (CLOCKS_BASE+0x78+0x1000)
#define CLK_SYS_RESUS_CTRL_SET      (CLOCKS_BASE+0x78+0x2000)
#define CLK_SYS_RESUS_CTRL_CLR      (CLOCKS_BASE+0x78+0x3000)


#define XOSC_BASE                   0x40024000

#define XOSC_CTRL_RW                (XOSC_BASE+0x00+0x0000)
#define XOSC_CTRL_XOR               (XOSC_BASE+0x00+0x1000)
#define XOSC_CTRL_SET               (XOSC_BASE+0x00+0x2000)
#define XOSC_CTRL_CLR               (XOSC_BASE+0x00+0x3000)

#define XOSC_STATUS_RW              (XOSC_BASE+0x04+0x0000)
#define XOSC_STATUS_XOR             (XOSC_BASE+0x04+0x1000)
#define XOSC_STATUS_SET             (XOSC_BASE+0x04+0x2000)
#define XOSC_STATUS_CLR             (XOSC_BASE+0x04+0x3000)

#define XOSC_STARTUP_RW             (XOSC_BASE+0x0C+0x0000)
#define XOSC_STARTUP_XOR            (XOSC_BASE+0x0C+0x1000)
#define XOSC_STARTUP_SET            (XOSC_BASE+0x0C+0x2000)
#define XOSC_STARTUP_CLR            (XOSC_BASE+0x0C+0x3000)

#define SYST_CSR 0xE000E010
#define SYST_RVR 0xE000E014
#define SYST_CVR 0xE000E018

#endif // !CLOCKS_H
