#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif /**/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "serial.h"
#include "twi.h"
#include "pim447.h"

static volatile uint8_t interrupted = 0;
MouseMovement mouseMovement;

void print_movement() {
    print_hex(mouseMovement.x);
    print_hex(mouseMovement.y);
    print_hex(mouseMovement.button);
    uart_putchar('\n');
}

void movement() {
    PIM447_get_mouse_movement(&mouseMovement);
    // Send mouse events
    print_movement();
}

void loop() {
    // if pd2 is high, movement
    if (PIM447_interrupt()) movement();

    //uart_echo();
}


ISR (INT1_vect) {
    if (!interrupted) interrupted = 1;
}

int main(void) {
    // Set Outputs and Inputs
    uart_init();
    TWI_init();
    

    DDRD &= ~_BV(PD3);
    /*
        ISC11   ISC10
        0       0       The low level of INT0 generates an interrupt request.
        0       1       Any logical change on INT0 generates an interrupt request.
        1       0       The falling edge of INT0 generates an interrupt request.
        1       1       The rising edge of INT0 generates an interrupt request.
    */
    EICRA |= (0 << ISC11) | (1 << ISC10);
    EIMSK |= _BV(INT1);

    uart_putstr("Atmega328p with PIM447 over I2C\n");
    
    sei();
    PIM_setup();
    while (1) loop();
}

