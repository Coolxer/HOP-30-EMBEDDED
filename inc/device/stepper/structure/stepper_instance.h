#ifndef STEPPER_INSTANCE_H
#define STEPPER_INSTANCE_H

#include <stdint.h>

#include "enum/stepper_state.h"
#include "enum/home_step.h"

#include "device/stepper/structure/stepper_movement.h"

typedef struct
{
    Movement movement;

    enum State state;     // 0 - off, 1 - on, 2 - home, 3 - move, 4 - paused
    enum State lastState; // lastState (especially useful in resume function)

    enum HomeStep homeStep; // 0 - fast, 1 - backward, 2 - precise

    volatile uint8_t FINISHED_FLAG; // stepper finish movement flag
} Instance;

Instance stepper_instance_init();

#endif // STEPPER_INSTANCE_H