#ifndef STEPPER_SPEED_H
#define STEPPER_SPEED_H

#include "device/low_voltage/stepper/enum/speed_type.h"
#include "device/low_voltage/stepper/enum/speed_state.h"

#include <stdint.h>

typedef struct
{
    float current, // current speed is increasing / decreasing in time (only if acceleration is set, otherwise current is target speed initially)
        target;    // destination speed set by user

    uint32_t lastTimeUpdate; // last time speed was updated (using to smooth accelerate)

    enum SpeedType type;
    enum SpeedState state;
} Speed;

Speed stepper_speed_init();

#endif // STEPPER_SPEED_H