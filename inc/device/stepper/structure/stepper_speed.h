#ifndef STEPPER_SPEED_H
#define STEPPER_SPEED_H

#include <stdint.h>

typedef struct
{
    float min,
        max,

        current,
        target,

        homeFastBackward,
        homeSlowForward,
        homePreciseBackward;

    uint32_t lastTimeUpdate;
} Speed;

Speed stepper_speed_init(float min, float max, float homeFastBackward, float homeSlowForward, float homePreciseBackward);

#endif // STEPPER_SPEED_H