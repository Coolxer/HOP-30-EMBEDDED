#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "device/stepper/stepper.h"
#include "device/endstop/endstop.h"

enum
{
    STEPPERS_COUNT = 4,
    ENDSTOPS_COUNT = 6
};

// main devices arrays
extern Stepper steppers[STEPPERS_COUNT];
extern Endstop endstops[ENDSTOPS_COUNT];

// additional pointers to easy grab
extern Stepper *W_STEPPER;
extern Stepper *X_STEPPER;
extern Stepper *Y_STEPPER;
extern Stepper *Z_STEPPER;

void device_manager_init();   // sets devices
void device_manager_deinit(); // resets devices

Stepper *device_manager_getStepper(uint8_t *name);           // returns pointer to stepper by name, if device name is not recognized, returns NULL
Stepper *device_manager_findParentStepper(Endstop *endstop); // returns parent stepper of given endstop

void manageDevices(); // manages devices events

/* PRIVATE */ //void manageEndstops(); // manages endstops services (events)
/* PRIVATE */ //void manageSteppers(); // manages steppers services (events)

#endif // DEVICE_MANAGER_H
