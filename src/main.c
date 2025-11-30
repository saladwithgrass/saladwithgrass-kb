#include "bsp/board_api.h"
#include "class/hid/hid_device.h"
#include "device/usbd.h"
#include "tusb.h"

int main() {
    board_init();
    tud_init(BOARD_TUD_RHPORT);
    while(1) {
        tud_task();
    }

}
