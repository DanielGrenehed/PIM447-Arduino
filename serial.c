#define __AVR_ATmega328P__ 
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 38400
#define FOSC 16000000

// p183      

void uart_init(void) {
    // Enable Transmitting and Receiving
    UCSR0B |= _BV(TXEN0) | _BV(RXEN0); 
    // Usart Control and Status Register (B)

    // Frame settings
    UCSR0C |= _BV(UCSZ01);
    UCSR0C |= _BV(UCSZ00);
    // no parity
    UCSR0C &= ~_BV(UPM01) &~_BV(UPM00);
    // 1 stop bit
    UCSR0C &= ~_BV(USBS0); 
    // Set Baud rate
    uint16_t ubrrn = FOSC/(16*BAUD) -1;
    UBRR0 = ubrrn;
}

void uart_putchar(char chr) {
    if (chr == '\n') uart_putchar('\r');
    while (!(UCSR0A & _BV(UDRE0))) ; // blocking
    UDR0 = chr;
}


void uart_putstr(const char *str) {
    int i = 0;
    while (*(str+i) != 0) {
        uart_putchar(*(str+i));
        i++;
    }
}

char uart_getchar(void) {
    while (!(UCSR0A & _BV(RXC0))); // blocking
    return UDR0;
}

void uart_echo(void) {
    uart_putchar(uart_getchar());
}

#include "serial.h"
