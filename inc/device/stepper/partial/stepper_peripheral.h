#ifndef STEPPER_PERIPHERAL_H
#define STEPPER_PERIPHERAL_H

#include "device/stepper/stepper.h"

/* PRIVATE */                                  //void stepper_setupGpio(Stepper *stepper);        /* setups all pins that are in common with stepper */
/* PRIVATE */                                  //void stepper_setupMasterTimer(Stepper *stepper); /* setups master timer (with PWM) */
/* PRIVATE */                                  //void stepper_setupSlaveTimer(Stepper *stepper);  /* setups slave timer (that controls number of steps taken) */
void stepper_setPeripherals(Stepper *stepper); /* calls all setups */

void stepper_stopTimers(Stepper *stepper); // stop timers
uint8_t stepper_reload(Stepper *stepper);  // try reloads arr register value of slave timer if needed (overflow), info if RELOADED or NOT_RELOADED

void stepper_setSpeedRegisters(Stepper *stepper, uint16_t psc, uint16_t arr, uint16_t pul);

#endif // STEPPER_PERIPHERAL_H