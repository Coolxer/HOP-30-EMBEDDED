#ifndef STEPPER_CALCULATOR_H
#define STEPPER_CALCULATOR_H

#include "stm32f4xx_hal.h"

#include "device/stepper/enum/axis_type.h"

extern const uint16_t MAX_16BIT_VALUE;

// structure of speed setting registers
typedef struct
{
    uint16_t psc; // prescaler
    uint16_t arr; // autoreload
    uint16_t pul; // pulse

} Speed_params;

Speed_params calculate_speed(enum AxisType axisType, float speed);
uint32_t calculate_way(enum AxisType axisType, float way);

#endif // STEPPER_CALCULATOR_H