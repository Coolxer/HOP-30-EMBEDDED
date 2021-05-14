#ifndef TH_PHASE_MOTOR_H
#define TH_PHASE_MOTOR_H

#include "stm32f4xx_hal.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
} Th_phase_motor;

#endif // TH_PHASE_MOTOR_H
