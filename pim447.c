#include "twi.h"
#include "pim447.h"

#define PIM_ADR 0x0A
#define PIM_LED 0x00
#define PIM_TRK 0x04
#define PIM_INT 0xF9


unsigned char set_led_color(unsigned char *color) {
    TWI_start_write(PIM_ADR);

    TWI_write(PIM_LED);
    if (TWI_status() != 0x28) return TWI_WRITE_ERR; // Data byte not transmitted

    for (int i = 0; i < 4; i++) {
        TWI_write(*color++);
        if (TWI_status() != 0x28) return TWI_WRITE_ERR;
    }

    TWI_stop();
    return TWI_SUCCESS;
}