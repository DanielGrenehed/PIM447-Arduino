#ifndef PIM447_H
#define PIM447_H

typedef struct { int x, y, button; } MouseMovement;

void PIM_setup();

unsigned char PIM447_set_led_color(unsigned char *color);

unsigned char PIM447_get_mouse_movement(MouseMovement *);

unsigned char PIM447_set_enable_interrupt(void);

unsigned char PIM447_interrupt();

#endif /* ifndef PIM447_H */