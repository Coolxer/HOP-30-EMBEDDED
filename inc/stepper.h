#ifndef STEPPER_H
#define STEPPER_H

#include <stdint.h> // includes uint8_t data type
#include <stdbool.h> // include bool data type

struct Stepper
{
    char *_name;       // 2-character stepper name (id)

    uint8_t _enable_pin;   // enable pin
    uint8_t _dir_pin;      // direction(dir) pin
    uint8_t _step_pin;     // step pin

    uint8_t _m1, _m2, _m3; // microstepping pins

    uint8_t _endstop_pin;  // associated endstop pin
};

void stepper_init(struct Stepper *s, uint8_t *name, uint8_t enable_pin, uint8_t dir_pin, uint8_t step_pin, uint8_t m1, uint8_t m2, uint8_t m3, uint8_t endstop_pin);
void stepper_setup_gpio(struct Stepper *s); // setups gpio pins

void stepper_enable(struct Stepper *s, bool state); // turns on the motor if the state is true or turns off if its false


#endif // STEPPER_H