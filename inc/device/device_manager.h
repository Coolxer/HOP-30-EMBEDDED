#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "device/low_voltage/stepper/stepper.h"
#include "device/low_voltage/endstop/endstop.h"

#include "device/low_voltage/stepper/partial/stepper_helper.h"

#include "device/high_voltage/hvd.h"

#define STEPPERS_AMOUNT 4
#define ENDSTOPS_AMOUNT 6

// low voltage devices arrays
extern Stepper steppers[STEPPERS_AMOUNT];
extern Endstop endstops[ENDSTOPS_AMOUNT];

// additional pointers to easy grab (useful)
extern Stepper *W_STEPPER;
extern Stepper *X_STEPPER;
extern Stepper *Y_STEPPER;
extern Stepper *Z_STEPPER;

// high voltage devices
extern HVD POMP;
extern HVD TH_PHASE_MOTOR;

// 12 devices at all : STEPPERS_AMOUNT (4) + ENDSTOPS_AMOUNT (6) + POMP (1) + TH_PHASE_MOTOR (1) = 12
extern uint8_t devicesStates[13]; // 13 here (12 + 1) for end of string terminator

void device_manager_init();   // sets devices
void device_manager_deinit(); // resets devices

Stepper *device_manager_getStepper(uint8_t *name);           // returns pointer to stepper
Stepper *device_manager_findParentStepper(Endstop *endstop); // returns parent stepper of given endstop

Endstop *device_manager_getEndstop(uint8_t *name); // returns pointer to endstop

void device_manager_process(); // manages devices events

void device_manager_getAllDevicesStates();

/* PRIVATE */ //void device_manager_manageEndstops(); // manages endstops services (events)
/* PRIVATE */ //void device_manager_manageSteppers(); // manages steppers services (events)

#endif // DEVICE_MANAGER_H
