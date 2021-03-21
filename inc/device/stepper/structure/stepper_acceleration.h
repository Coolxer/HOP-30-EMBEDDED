#ifndef STEPPER_ACCELERATION_H
#define STEPPER_ACCELERATION_H

#include <stdint.h>

typedef struct
{
    float min,
        current,
        max,

        homeFastBackward,
        homeSlowForward,
        homePreciseBackward,

        next;

    uint32_t stepsNeededToFullAccelerate;
} Acceleration;

Acceleration stepper_acceleration_init(float min, float max, float homeFastBackward, float homeSlowForward, float homePreciseBackward);

#endif // STEPPER_ACCELERATION_H