#define __AVR_ATmega328P__
#include <avr/io.h>
#include <avr/interrupt.h>
#include "twi.h"

void TWI_init(void) {

    TWSR = 0x00; // Set prescaler value to 1
    TWBR = 0x18; // 16MHz / 16 + 2 * TWBR(24) * PSV(1) == 250kHz
    TWCR |= _BV(TWEN); // Enable TWI

}

void loop_until_TWI_interrupt() {
    while ((TWCR & _BV(TWINT)) == 0);
}

void TWI_start(void) {
    TWCR |= _BV(TWINT) | _BV(TWSTA); // reset flag and set start
    loop_until_TWI_interrupt();
}

void TWI_stop(void) {
    TWCR |= _BV(TWINT) | _BV(TWSTO);
}

void TWI_write(uint8_t data) {
    TWDR = data;
    TWCR |= _BV(TWINT);
    loop_until_TWI_interrupt();
}

uint8_t TWI_status(void) {
    return TWSR & 0xF8;
}

uint8_t TWI_read(void) {
    TWCR |= _BV(TWINT) | _BV(TWEA);
    loop_until_TWI_interrupt();
    return TWDR;
}

uint8_t TWI_read_nack(void) {
    TWCR |= _BV(TWINT);
    loop_until_TWI_interrupt();
    return TWDR;
}