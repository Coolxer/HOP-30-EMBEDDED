#ifndef STEPPER_MOVEMENT_H
#define STEPPER_MOVEMENT_H

#include <stdint.h>

typedef struct
{
    uint16_t rest;   // number of steps needed to make after resume (saved at PAUSE)
    uint32_t target; // long target (can be bigger than register size, but can be also equal) -> this have to been loaded to register in future
                     // future mean if current register counted up

    volatile uint8_t FINISHED_FLAG; // stepper finish movement flag
} Movement;

Movement stepper_movement_init();

#endif // STEPPER_MOVEMENT_H