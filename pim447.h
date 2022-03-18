#ifndef PIM447_H
#define PIM447_H

// set led color
unsigned char set_led_color(unsigned char *color);
// interrupt

// button press
// trackball movement
typedef struct {
    int x, y, button;
} MouseMovement;

unsigned char get_mouse_movement(MouseMovement *);

#endif /* ifndef PIM447_H */