#ifndef TWI_H
#define TWI_H

#define TWI_START_ERR 2
#define TWI_ADDRESS_ERR 3
#define TWI_WRITE_ERR 4
#define TWI_NACK_RECV 5
#define TWI_SUCCESS 1

void TWI_init(void);

void loop_until_TWI_interrupt();

void TWI_start(void);
unsigned char TWI_start_write(unsigned char address);
unsigned char TWI_start_read(unsigned char address);


void TWI_stop(void);

void TWI_write(unsigned char data);

void TWI_SDA_R(unsigned char address);

void TWI_SDA_W(unsigned char address);

unsigned char TWI_status(void);

unsigned char TWI_read(void);

unsigned char TWI_read_nack(void);

#endif /* ifndef TWI_H */