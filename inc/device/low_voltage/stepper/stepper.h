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

#define LEFT 0
#define RIGHT 1
#define DOWN "0\0"
#define UP "1\0"

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