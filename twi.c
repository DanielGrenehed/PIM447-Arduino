#define __AVR_ATmega328P__
#include <avr/io.h>
#include <avr/interrupt.h>
#include "twi.h"

#define TW_SCL_PIN			PORTC5
#define TW_SDA_PIN			PORTC4

void TWI_init(void) {

    DDRC  |= _BV(TW_SDA_PIN) | _BV(TW_SCL_PIN);
    PORTC |= (1 << TW_SDA_PIN) | (1 << TW_SCL_PIN); // pullup
    DDRC  &= ~((1 << TW_SDA_PIN) | (1 << TW_SCL_PIN));

    TWSR = 0x00; // Set prescaler value to 1
    TWBR = 0x18; // 16MHz / 16 + 2 * TWBR(24) * PSV(1) == 250kHz
    TWCR |= _BV(TWEN); // Enable TWI

}

void loop_until_TWI_interrupt() {
    while (!(TWCR & _BV(TWINT)));
}

void TWI_start(void) {
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTA); // reset flag and set startrs
    loop_until_TWI_interrupt();
}

uint8_t TWI_start_write(uint8_t address) {
    TWI_start();

    TWI_SDA_W(address);
    return TWI_status();
}

uint8_t TWI_start_read(uint8_t address) {
    TWI_start();

    TWI_SDA_R(address);
    return TWI_status();
}

void TWI_stop(void) {
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
}

void TWI_write(uint8_t data) {
    TWDR = data;
    TWCR = _BV(TWINT) | _BV(TWEN);
    loop_until_TWI_interrupt();
}

void TWI_SDA_R(uint8_t address) {
    TWI_write((address << 1) | 1);
}

void TWI_SDA_W(uint8_t address) {
    TWI_write((address << 1) & (~1));
}

uint8_t TWI_status(void) { 
    return TWSR & 0xF8;
}

uint8_t TWI_read(void) {
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
    loop_until_TWI_interrupt();
    return TWDR;
}

uint8_t TWI_read_nack(void) {
    TWCR = _BV(TWINT) | _BV(TWEN);
    loop_until_TWI_interrupt();
    return TWDR;
}