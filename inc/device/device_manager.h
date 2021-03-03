#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "device/stepper/stepper.h"
#include "device/endstop/endstop.h"

enum
{
    STEPPERS_COUNT = 4,
    ENDSTOPS_COUNT = 6
};

extern Stepper steppers[STEPPERS_COUNT];
extern Endstop endstops[ENDSTOPS_COUNT];

extern Stepper *X_STEPPER;
extern Stepper *Y_STEPPER;
extern Stepper *Z_STEPPER;
extern Stepper *W_STEPPER;

extern Stepper *int_stepper; // stepper received in interrupt // should be volatile ?

void device_manager_init();   // sets devices
void device_manager_deinit(); // resets devices

Stepper *device_manager_getStepper(uint8_t *name);           // returns pointer to stepper by name, if device name is not recognized, returns NULL
Endstop *device_manager_getEndstop(uint8_t *name);           // returns pointer to endstopp by name
Stepper *device_manager_findParentStepper(Endstop *endstop); // returns parent stepper of given endstop

void device_manager_process(); // process

#endif // DEVICE_MANAGER_H
