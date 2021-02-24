#ifndef STEPPER_H
#define STEPPER_H

#include "stm32f4xx_hal.h"

#include "stepper/structure/stepper_hardware.h"
#include "stepper/structure/stepper_info.h"
#include "stepper/structure/stepper_instance.h"

#include "endstop/endstop.h"

typedef struct
{
    Hardware hardware;
    Info info;
    Instance instance;

    Endstop *minEndstop;
    Endstop *maxEndstop;
} Stepper;

#endif // STEPPER_H