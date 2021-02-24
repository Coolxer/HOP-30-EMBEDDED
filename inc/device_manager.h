#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "stepper/stepper.h"
#include "endstop/endstop.h"

void device_manager_init();   // sets devices
void device_manager_deinit(); // resets devices

Stepper *device_manager_getStepper(uint8_t *name); // returns pointer to stepper by name, if device name is not recognized, returns NULL
Endstop *device_manager_getEndstop(uint8_t *name); // returns pointer to endstopp by name

void device_manager_endstopClickedCallback();  // endstop clicked callback
void device_manager_stepperFinishedCallback(); // stepper finished move callback;

void device_manager_process(); // process

/* PRIVATE */ //Stepper *device_manager_findParentStepper(Endstop *endstop); // returns parent stepper of given endstop

/* PRIVATE */ //void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);               /* endstop interrupt procedure */
/* PRIVATE */ //void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);  /* SLAVE timer interrupt procedure */

#endif // DEVICE_MANAGER_H
