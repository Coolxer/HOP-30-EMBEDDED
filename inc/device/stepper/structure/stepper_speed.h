#ifndef STEPPER_SPEED_H
#define STEPPER_SPEED_H

#include <stdint.h>

#include "device/stepper/enum/speed_state.h"

typedef struct
{
    float min,
        max,

        current, // current speed is increasing / decreasing in time (only if acceleration is set, otherwise current is target speed initially)
        target,  // destination speed set by user

        homeFastBackward,
        homeSlowForward,
        homePreciseBackward;

    uint32_t lastTimeUpdate; // last time speed was updated (using to smooth accelerate)

    enum SpeedState state;
} Speed;

Speed stepper_speed_init(float min, float max, float homeFastBackward, float homeSlowForward, float homePreciseBackward);

#endif // STEPPER_SPEED_H