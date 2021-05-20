#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "device/low_voltage/stepper/stepper.h"
#include "device/low_voltage/endstop/endstop.h"

#include "device/high_voltage/high_voltage_device.h"

enum InformationType
{
    POINTER = 0,
    INDEX = 1
};

enum
{
    STEPPERS_COUNT = 4,
    ENDSTOPS_COUNT = 6
};

// main devices arrays
extern Stepper steppers[STEPPERS_COUNT];
extern Endstop endstops[ENDSTOPS_COUNT];

// additional pointers to easy grab (useful)
extern Stepper *W_STEPPER;
extern Stepper *X_STEPPER;
extern Stepper *Y_STEPPER;
extern Stepper *Z_STEPPER;

extern HVDevice POMP;
extern HVDevice TH_PHASE_MOTOR;

void device_manager_init();   // sets devices
void device_manager_deinit(); // resets devices

Stepper *device_manager_getStepperOrIndex(uint8_t *name, enum InformationType it); // returns pointer or index for stepper
Stepper *device_manager_findParentStepper(Endstop *endstop);                       // returns parent stepper of given endstop

Endstop *device_manager_getEndstopOrIndex(uint8_t *name, enum InformationType it); // returns pointer or index for endstop

void manageDevices(); // manages devices events

/* PRIVATE */ //void manageEndstops(); // manages endstops services (events)
/* PRIVATE */ //void manageSteppers(); // manages steppers services (events)

#endif // DEVICE_MANAGER_H
