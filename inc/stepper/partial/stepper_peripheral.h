#ifndef STEPPER_PERIPHERAL_H
#define STEPPER_PERIPHERAL_H

#include "stepper/stepper.h"

/* PRIVATE */                                     //void stepper_setupGpio(Stepper *stepper);        /* setups all pins that are in common with stepper */
/* PRIVATE */                                     //void stepper_setupMasterTimer(Stepper *stepper); /* setups master timer (with PWM) */
/* PRIVATE */                                     //void stepper_setupSlaveTimer(Stepper *stepper);  /* setups slave timer (that controls number of steps taken) */
void stepper_setup_peripherals(Stepper *stepper); /* calls all setups */

#endif // STEPPER_PERIPHERAL_H