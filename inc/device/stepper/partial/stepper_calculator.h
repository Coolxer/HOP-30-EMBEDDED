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

Speed_params convertSpeedToRegisters(enum AxisType axisType, float speed); // converts speed value to registers values
uint32_t convertWayToSteps(enum AxisType axisType, float way);             // converts way to steps number

float calculateSpeed(Stepper *stepper);                      // calculates new speed by (acceleration value and delta time)
uint32_t calculateStepsNeededToAccelerate(Stepper *stepper); // calculates steps needed to accelerate
uint8_t calculateRemainingTarget(Stepper *stepper);          // calculates remaining target

#endif // STEPPER_CALCULATOR_H