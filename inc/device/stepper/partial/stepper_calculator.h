#ifndef STEPPER_CALCULATOR_H
#define STEPPER_CALCULATOR_H

#include "stm32f4xx_hal.h"

#include "enum/axis_type.h"

extern const uint16_t MAX_16BIT_VALUE;

// structure of speed setting registers
typedef struct
{
    uint16_t psc; // prescaler
    uint16_t arr; // autoreload
    uint16_t pul; // pulse

} Speed;

// structure of steps setting parameters
typedef struct
{
    uint16_t laps; // number of laps (if arr is full, there is no laps too, because laps mean additional MAX_16_BIT_VALUE in arr register)
    uint16_t arr;  // current target

} Way;

Speed calculate_speed(enum AxisType axisType, float speed);
Way calculate_way(enum AxisType axisType, float way);

#endif // STEPPER_CALCULATOR_H