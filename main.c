#include <avr/io.h>
#include "serial.h"
#include "twi.h"
#include "pim447.h"
#include <util/delay.h>

void loop() {
    uart_echo();
}

int main(void) {
    // Set Outputs and Inputs
    uart_init();
    TWI_init();

    uart_putstr("Atmega328p with PIM447 over i2c\n");
    //__no_operation();

    while (1) loop();
}

