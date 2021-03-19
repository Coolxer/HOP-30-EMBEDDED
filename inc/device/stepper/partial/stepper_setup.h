#ifndef STEPPER_SETUP_H
#define STEPPER_SETUP_H

#include "device/stepper/stepper.h"

void stepper_init(Stepper *stepper, enum AxisType axisType, uint8_t *name, Hardware hardware, Speed speed, Acceleration acceleration);
void stepper_assignEndstops(Stepper *stepper, Endstop *min, Endstop *max); // setups endstops to the axis
void stepper_deinit(Stepper *stepper);                                     // stops PWM & disable IRQs

#endif // STEPPER_SETUP_H