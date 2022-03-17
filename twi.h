#ifndef TWI_H
#define TWI_H

void TWI_init(void);

void loop_until_TWI_interrupt();

void TWI_start(void);

void TWI_stop(void);

void TWI_write(unsigned char data);

unsigned char TWI_status(void);

unsigned char TWI_read(void);

unsigned char TWI_read_nack(void);

#endif /* ifndef TWI_H */