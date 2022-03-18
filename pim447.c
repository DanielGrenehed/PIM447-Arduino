#include "twi.h"
#include "pim447.h"
#include "serial.h"

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

unsigned char get_mouse_movement(MouseMovement *out) {
    TWI_start_write(PIM_ADR);

    TWI_write(PIM_TRK);
    if (TWI_status() != 0x28) return TWI_WRITE_ERR; // Data byte not transmitted

    TWI_start_read(PIM_ADR);
    unsigned char movement[5];

    for (int i = 0; i < 4; i++) {
        movement[i] = TWI_read();
    }
    movement[4] = TWI_read_nack();
    out->x = movement[1] - movement[0];
    out->y = movement[3] - movement[2];
    out->button = movement[4] & 0x80;

    TWI_stop();
    return TWI_SUCCESS;
}