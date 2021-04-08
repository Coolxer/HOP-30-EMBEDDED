#ifndef STEPPER_SETUP_H
#define STEPPER_SETUP_H

#include "device/stepper/stepper.h"

void stepper_init(Stepper *stepper, enum AxisType axisType, uint8_t *name, GPIO_TypeDef *port, TIM_TypeDef *masterTimer, TIM_TypeDef *slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq, uint16_t step, uint16_t dir, uint16_t enable);
void stepper_assignEndstops(Stepper *stepper, Endstop *min, Endstop *max); // setups endstops to the axis
void stepper_deinit(Stepper *stepper);                                     // stops PWM & disable IRQs

#endif // STEPPER_SETUP_H