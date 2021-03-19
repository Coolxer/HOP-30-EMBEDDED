#ifndef STEPPER_H
#define STEPPER_H

#include "stm32f4xx_hal.h"

#include "device/stepper/structure/stepper_hardware.h"
#include "device/stepper/structure/stepper_info.h"
#include "device/stepper/structure/stepper_instance.h"
#include "device/stepper/structure/stepper_speed.h"
#include "device/stepper/structure/stepper_acceleration.h"

#include "device/endstop/endstop.h"

// defines helpful macros
enum
{
    LEFT = 0,
    RIGHT = 1,

    DOWN = 0,
    UP = 1,
};

typedef struct
{
    Hardware hardware;
    Info info;
    Instance instance;

    Speed speed;
    Acceleration acceleration;

    Endstop *minEndstop;
    Endstop *maxEndstop;
} Stepper;

#endif // STEPPER_H