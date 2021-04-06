#ifndef STEPPER_ACCELERATION_H
#define STEPPER_ACCELERATION_H

#include <stdint.h>

typedef struct
{
    float current; // current acceleration set (positive float given by user, but becomes negative during deceleration)

    uint32_t stepsNeededToAccelerate; // steps value calculating after stepper finish accelerating
                                      // value using to know when to start deecelerating (if the target is less or equal this value)
} Acceleration;

Acceleration stepper_acceleration_init();

#endif // STEPPER_ACCELERATION_H