#include <avr/io.h>
#include "serial.h"
#include "twi.h"
#include "pim447.h"
#include <util/delay.h>

MouseMovement mouseMovement;
void loop() {
    uart_putchar(get_mouse_movement(&mouseMovement) + 48);
    print_hex(mouseMovement.x);
    print_hex(mouseMovement.y);
    print_hex(mouseMovement.button);

    unsigned char color[4] = { 0x00, 0x55, 0x00, 0x55 };
    uart_putchar(set_led_color(color) + 48);
    uart_echo();
}

int main(void) {
    // Set Outputs and Inputs
    uart_init();
    TWI_init();

    uart_putstr("Atmega328p with PIM447 over I2S\n");
    //__no_operation();
    

    while (1) loop();
}

