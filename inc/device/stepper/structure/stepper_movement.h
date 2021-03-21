#ifndef STEPPER_MOVEMENT_H
#define STEPPER_MOVEMENT_H

#include <stdint.h>

#include "device/stepper/partial/stepper_calculator.h"

typedef struct
{
    uint16_t rest; // how many steps need to make after resume stepper movement [need to resume]

    Way_params way; // params of way value [movement params: laps and arr]
} Movement;

Movement stepper_movement_init();

#endif // STEPPER_MOVEMENT_H