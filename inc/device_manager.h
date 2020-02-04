#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "Stepper.h"

#define STEPPERS_COUNT 1 //3                     // number of serviced devices
#define ENDSTOPS_COUNT 0

Stepper *steppers[STEPPERS_COUNT];                 // array of steppers

void device_manager_init();                     // sets devices parameters and reset current device
uint8_t device_manager_set_current(uint8_t *name); // sets current device by name, if device name is not recognized, returns FALSE

uint8_t device_manager_get_current();
void device_manager_release_device();

/* PRIVATE */   //void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif // DEVICE_MANAGER_H
