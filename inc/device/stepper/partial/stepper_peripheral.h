#ifndef STEPPER_PERIPHERAL_H
#define STEPPER_PERIPHERAL_H

#include "device/stepper/stepper.h"

enum
{
    NOT_RELOADED = 0,
    RELOADED = 1
};

/* PRIVATE */                                  //void stepper_setupGpio(Stepper *stepper);        /* setups all pins that are in common with stepper */
/* PRIVATE */                                  //void stepper_setupMasterTimer(Stepper *stepper); /* setups master timer (with PWM) */
/* PRIVATE */                                  //void stepper_setupSlaveTimer(Stepper *stepper);  /* setups slave timer (that controls number of steps taken) */
void stepper_setPeripherals(Stepper *stepper); /* calls all setups */

void stepper_stopTimers(Stepper *stepper);          // stop timers
void stepper_resetTimers(Stepper *stepper);         // reset timersEndstop *min, Endstop *max); // setups endstops to the axis
uint8_t stepper_manageSlaveTimer(Stepper *stepper); // reloads arr register value of slave timer if needed (overflow), info if RELOADED or NOT_RELOADED

#endif // STEPPER_PERIPHERAL_H