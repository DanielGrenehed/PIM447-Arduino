#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif /**/

#include <avr/interrupt.h>
#include <avr/io.h>

#include "twi.h"
#include "pim447.h"


#define PIM_ADR 0x0A
#define PIM_LED 0x00
#define PIM_TRK 0x04
#define PIM_INT 0xF9
#define PIM_INT_EN 2
#define INTERRUPT_PIN PD2


void PIM_setup() {
    // Set PD2 as input
    DDRD &= ~_BV(INTERRUPT_PIN);

    PIM447_set_enable_interrupt();

    // Set LED color
    unsigned char color[4] = { 0x00, 0x45, 0x40, 0x22 };
    PIM447_set_led_color(color);
}


/*
    Call pim447 and set registry pointer
*/
unsigned char PIM447_set_reg(unsigned char reg) {
    TWI_start_write(PIM_ADR);

    TWI_write(reg);
    if (TWI_status() != 0x28) return TWI_WRITE_ERR; // Data byte not transmitted
    return TWI_SUCCESS;
}

/*
    Calls pim447 and set led color 
    (color is a 4 byte array), RGBW
*/
unsigned char PIM447_set_led_color(unsigned char *color) {
    /*
        Set to LED Color registry
        (0x00 - 0x03) RGBW
    */
    unsigned char status = PIM447_set_reg(PIM_LED);
    if (status != TWI_SUCCESS) return status;

    /*
        Write 4 bytes to PIM447
    */
    for (int i = 0; i < 4; i++) {
        TWI_write(*color++);
        if (TWI_status() != 0x28) return TWI_WRITE_ERR;
    }

    /*
        End tansmission and return success
    */
    TWI_stop();
    return TWI_SUCCESS;
}

/*
    Fetches mouse and button movement 
    from pim447
*/
unsigned char PIM447_get_mouse_movement(MouseMovement *out) {
    /*
        Set to trackball data registry
        (0x04 - 0x08)
    */
    unsigned char status = PIM447_set_reg(PIM_TRK);
    if (status != TWI_SUCCESS) return status;

    /*
        Send start read byte 
        then read 5 bytes
    */
    TWI_start_read(PIM_ADR);
    unsigned char movement[5];
    for (int i = 0; i < 4; i++) movement[i] = TWI_read();
    movement[4] = TWI_read_nack();

    /*
        calculate and set mouseMovement
    */ 
    out->x = ((int)movement[1]) - movement[0];
    out->y = ((int)movement[3]) - movement[2];
    out->button = ((movement[4] & 0x80) >> 3);

    /*
        Stop twi and return success
    */
    TWI_stop();
    return TWI_SUCCESS;
}

/*
    Enables interrupt pin(INT) on PIM447
*/
unsigned char PIM447_set_enable_interrupt(void) {
    /*
        Set to interrupt registry
        then enable interrupt
    */
    unsigned char status = PIM447_set_reg(PIM_INT);
    if (status != TWI_SUCCESS) return status; 
    TWI_write(PIM_INT_EN);
    if (TWI_status() != 0x28) return TWI_WRITE_ERR;
    
    /*
        End communication and return success
    */
    TWI_stop();
    return TWI_SUCCESS;
}

/*
    Returns true when pin connected to PIM447
    INT is connected to ground
*/
uint8_t PIM447_interrupt() {
    return (PIND & _BV(INTERRUPT_PIN)) == 0;
}