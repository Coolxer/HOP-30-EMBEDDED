#ifndef STEPPER_CALCULATOR_H
#define STEPPER_CALCULATOR_H

#define MAX_16BIT_VALUE 65535

#include "stepper/stepper.h"

void calculate_speed(Stepper *stepper, uint16_t speed);

#endif // STEPPER_CALCULATOR_H