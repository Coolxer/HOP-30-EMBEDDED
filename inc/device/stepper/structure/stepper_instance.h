#ifndef STEPPER_INSTANCE_H
#define STEPPER_INSTANCE_H

#include "device/stepper/enum/state.h"
#include "device/stepper/enum/home_step.h"

typedef struct
{
    enum State state;     // 0 - off, 1 - on, 2 - home, 3 - move, 4 - paused
    enum State lastState; // lastState (especially useful in resume function)

    enum HomeStep homeStep; // 0 - fast, 1 - backward, 2 - preciseg
} Instance;

Instance stepper_instance_init();

#endif // STEPPER_INSTANCE_H