#ifndef STEPPER_H
#define STEPPER_H

#include <stdint.h> // includes uint8_t data type
#include <stdbool.h> // include bool data type

struct Stepper
{
    char *name;       // 2-character stepper name (id)

    uint16_t enable_pin;   // enable pin
    uint16_t dir_pin;      // direction(dir) pin
    uint16_t step_pin;     // step pin

    uint16_t m1, m2, m3; // microstepping pins

    uint16_t endstop_pin;  // associated endstop pin
};

void stepper_init(struct Stepper *s, uint8_t *_name, uint16_t _enable_pin, uint16_t _dir_pin, uint16_t _step_pin, uint16_t _m1, uint16_t _m2, uint16_t _m3, uint16_t _endstop_pin);
void stepper_setup_gpio(struct Stepper *s); // setups gpio pins

void stepper_enable(struct Stepper *s, bool state); // turns on the motor if the state is true or turns off if its false


#endif // STEPPER_H