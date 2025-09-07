#ifndef RESETS_H
#define RESETS_H
#include <stdint.h>

void reset_subsystem(uint8_t subsytem);
void unreset_subsystem(uint8_t subsytem);
uint8_t is_reset_done(uint8_t subsytem);

#define RESETS_BASE                 0x4000C000

#define RESETS_RESET_RW        (RESETS_BASE+0x0+0x0000)
#define RESETS_RESET_XOR       (RESETS_BASE+0x0+0x1000)
#define RESETS_RESET_SET       (RESETS_BASE+0x0+0x2000)
#define RESETS_RESET_CLR       (RESETS_BASE+0x0+0x3000)

#define RESETS_WDSEL_RW        (RESETS_BASE+0x4+0x0000)
#define RESETS_WDSEL_XOR       (RESETS_BASE+0x4+0x1000)
#define RESETS_WDSEL_SET       (RESETS_BASE+0x4+0x2000)
#define RESETS_WDSEL_CLR       (RESETS_BASE+0x4+0x3000)

#define RESETS_RESET_DONE_RW   (RESETS_BASE+0x8+0x0000)
#define RESETS_RESET_DONE_XOR  (RESETS_BASE+0x8+0x1000)
#define RESETS_RESET_DONE_SET  (RESETS_BASE+0x8+0x2000)
#define RESETS_RESET_DONE_CLR  (RESETS_BASE+0x8+0x3000)


#define RESET_USBCTRL       24 
#define RESET_UART1         23 
#define RESET_UART0         22 
#define RESET_TIMER         21 
#define RESET_TBMAN         20 
#define RESET_SYSINFO       19 
#define RESET_SYSCFG        18 
#define RESET_SPI1          17 
#define RESET_SPI0          16 
#define RESET_RTC           15 
#define RESET_PWM           14 
#define RESET_PLL_USB       13 
#define RESET_PLL_SYS       12 
#define RESET_PIO1          11 
#define RESET_PIO0          10 
#define RESET_PADS_QSPI     9  
#define RESET_PADS_BANK0    8  
#define RESET_JTAG          7  
#define RESET_IO_QSPI       6  
#define RESET_IO_BANK0      5  
#define RESET_I2C1          4  
#define RESET_I2C0          3  
#define RESET_DMA           2  
#define RESET_BUSCTRL       1  
#define RESET_ADC           0  

#endif // !RESETS_H
