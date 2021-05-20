#ifndef STEPPER_H
#define STEPPER_H

#include "stm32f4xx_hal.h"

#include "device/low_voltage/stepper/enum/state.h"

#include "device/low_voltage/stepper/structure/stepper_hardware.h"
#include "device/low_voltage/stepper/structure/stepper_info.h"

#include "device/low_voltage/stepper/structure/stepper_speed.h"
#include "device/low_voltage/stepper/structure/stepper_acceleration.h"
#include "device/low_voltage/stepper/structure/stepper_movement.h"

#include "device/low_voltage/endstop/endstop.h"

#define LEFT (uint8_t *)"0\0"
#define RIGHT (uint8_t *)"1\0"
#define DOWN (uint8_t *)"0\0"
#define UP (uint8_t *)"1\0"

typedef struct
{
    Hardware hardware;
    Info info;

    Speed speed;
    Acceleration acceleration;
    Movement movement;

    enum State state;

    Endstop *minEndstop;
    Endstop *maxEndstop;
} Stepper;

#endif // STEPPER_H