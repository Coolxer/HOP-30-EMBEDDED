#ifndef STEPPER_MOVEMENT_H
#define STEPPER_MOVEMENT_H

#include <stdint.h>

#include "device/low_voltage/stepper/enum/move_type.h"

typedef struct
{
    uint16_t rest;          // number of steps needed to make after resume (saved at PAUSE)
    uint32_t unloadedSteps; // can be bigger than register size, but can be also equal -> this have to been loaded to register in future part-by-part
                            // future mean if current register counted up

    enum MoveType type;

    volatile uint8_t FINISHED_FLAG; // stepper finish movement flag
} Movement;

Movement stepper_movement_init();

#endif // STEPPER_MOVEMENT_H