#ifndef STEPPER_SETUP_H
#define STEPPER_SETUP_H

#include "device/low_voltage/stepper/stepper.h"

void stepper_init(Stepper *stepper, enum AxisType axisType, uint8_t *name, TIM_TypeDef *masterTimer, TIM_TypeDef *slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq,
                  GPIO_TypeDef *enablePort, uint16_t enablePin, GPIO_TypeDef *stepPort, uint16_t stepPin, GPIO_TypeDef *dirPort, uint16_t dirPin);
void stepper_assignEndstops(Stepper *stepper, Endstop *min, Endstop *max); // setups endstops to the axis
void stepper_deinit(Stepper *stepper);                                     // stops PWM & disable IRQs

#endif // STEPPER_SETUP_H