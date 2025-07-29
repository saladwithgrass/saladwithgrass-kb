#ifndef PADS_H_
#define PADS_H_
#include "general_defines.h"
#include "../errors/errors.h"
#include <stdint.h>

uint8_t is_valid_pad(uint8_t pad_num);


Error pads_disable_ouput         (uint8_t pad_num);
Error pads_enable_ouput          (uint8_t pad_num);

Error pads_disable_input         (uint8_t pad_num);
Error pads_enable_input          (uint8_t pad_num);

Error pads_set_drive             (uint8_t pad_num, uint8_t value);

Error pads_enable_pullup         (uint8_t pad_num);
Error pads_diable_pullup         (uint8_t pad_num);

Error pads_enable_pulldown       (uint8_t pad_num);
Error pads_disable_pulldown      (uint8_t pad_num);

Error pads_disable_schmidt       (uint8_t pad_num);
Error pads_enable_schmidt        (uint8_t pad_num);

Error pads_enable_fast_slewrate  (uint8_t pad_num);
Error pads_disable_fast_slewrate (uint8_t pad_num);

#define PADS_BANK0_BASE               0x4001c000



#define PADS_BANK0_VOLTAGE_SELECT     0x4001c000

#define PADS_BANK0_GPIO_CTRL(gpio_n)  (PADS_BANK0_BASE + 0x04 * (gpio_n + 1))

#define PADS_BANK0_GPIO00_CTRL        (PADS_BANK0_BASE + 0x04)
#define PADS_BANK0_GPIO01_CTRL        (PADS_BANK0_BASE + 0x08)
#define PADS_BANK0_GPIO02_CTRL        (PADS_BANK0_BASE + 0x0c)
#define PADS_BANK0_GPIO03_CTRL        (PADS_BANK0_BASE + 0x10)
#define PADS_BANK0_GPIO04_CTRL        (PADS_BANK0_BASE + 0x14)
#define PADS_BANK0_GPIO05_CTRL        (PADS_BANK0_BASE + 0x18)
#define PADS_BANK0_GPIO06_CTRL        (PADS_BANK0_BASE + 0x1c)
#define PADS_BANK0_GPIO07_CTRL        (PADS_BANK0_BASE + 0x20)
#define PADS_BANK0_GPIO08_CTRL        (PADS_BANK0_BASE + 0x24)
#define PADS_BANK0_GPIO09_CTRL        (PADS_BANK0_BASE + 0x28)
#define PADS_BANK0_GPIO10_CTRL        (PADS_BANK0_BASE + 0x2c)
#define PADS_BANK0_GPIO11_CTRL        (PADS_BANK0_BASE + 0x30)
#define PADS_BANK0_GPIO12_CTRL        (PADS_BANK0_BASE + 0x34)
#define PADS_BANK0_GPIO13_CTRL        (PADS_BANK0_BASE + 0x38)
#define PADS_BANK0_GPIO14_CTRL        (PADS_BANK0_BASE + 0x3c)
#define PADS_BANK0_GPIO15_CTRL        (PADS_BANK0_BASE + 0x40)
#define PADS_BANK0_GPIO16_CTRL        (PADS_BANK0_BASE + 0x44)
#define PADS_BANK0_GPIO17_CTRL        (PADS_BANK0_BASE + 0x48)
#define PADS_BANK0_GPIO18_CTRL        (PADS_BANK0_BASE + 0x4c)
#define PADS_BANK0_GPIO19_CTRL        (PADS_BANK0_BASE + 0x50)
#define PADS_BANK0_GPIO20_CTRL        (PADS_BANK0_BASE + 0x54)
#define PADS_BANK0_GPIO21_CTRL        (PADS_BANK0_BASE + 0x58)
#define PADS_BANK0_GPIO22_CTRL        (PADS_BANK0_BASE + 0x5c)
#define PADS_BANK0_GPIO23_CTRL        (PADS_BANK0_BASE + 0x60)
#define PADS_BANK0_GPIO24_CTRL        (PADS_BANK0_BASE + 0x64)
#define PADS_BANK0_GPIO25_CTRL        (PADS_BANK0_BASE + 0x68)
#define PADS_BANK0_GPIO26_CTRL        (PADS_BANK0_BASE + 0x6c)
#define PADS_BANK0_GPIO27_CTRL        (PADS_BANK0_BASE + 0x70)
#define PADS_BANK0_GPIO28_CTRL        (PADS_BANK0_BASE + 0x74)
#define PADS_BANK0_GPIO29_CTRL        (PADS_BANK0_BASE + 0x78)
#define PADS_BANK0_SWCLK              (PADS_BANK0_BASE + 0x7c)
#define PADS_BANK0_SWD                (PADS_BANK0_BASE + 0x80)

#endif // !PADS_H_
