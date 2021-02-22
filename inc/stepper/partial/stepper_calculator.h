#ifndef STEPPER_CALCULATOR_H
#define STEPPER_CALCULATOR_H

#define MAX_16BIT_VALUE 65535

#include "stepper/stepper.h"

// structure of speed setting registers
typedef struct
{
    uint16_t psc; // prescaler
    uint16_t arr; // autoreload
    uint16_t pul; // pulse

} Speed;

Speed calculate_speed(Stepper *stepper, float speed);
uint16_t calculate_steps(Stepper *stepper, float way);

#endif // STEPPER_CALCULATOR_H