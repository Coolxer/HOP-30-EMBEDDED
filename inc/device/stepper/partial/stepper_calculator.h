#ifndef STEPPER_CALCULATOR_H
#define STEPPER_CALCULATOR_H

#include "stm32f4xx_hal.h"

#include "device/stepper/enum/axis_type.h"
#include "device/stepper/stepper.h"

extern const uint16_t MAX_16BIT_VALUE;

// structure of speed setting registers
typedef struct
{
    uint16_t psc; // prescaler
    uint16_t arr; // autoreload
    uint16_t pul; // pulse

} Speed_params;

Speed_params convertSpeedToRegisters(enum AxisType axisType, float speed);
uint32_t calculateWay(enum AxisType axisType, float way);

float calculateSpeed(Stepper *stepper);
uint8_t calculateIfShouldStartDecelerate(Stepper *stepper);

uint32_t calculateStepsNeededToAccelerate(Stepper *stepper);

#endif // STEPPER_CALCULATOR_H