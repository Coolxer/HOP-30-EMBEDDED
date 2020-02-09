#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "Stepper.h"
#include "Endstop.h"

uint8_t PROCESS_FORWARD;

void device_manager_init();                                                     // sets devices
void device_manager_deinit();                                                   // resets devices
Stepper *device_manager_getStepper(uint8_t *name);                             // returns pointer to device by name, if device name is not recognized, returns NULL

/* PRIVATE */   //void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);               /* endstop interrupt procedure */
/* PRIVATE */   //void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);  /* SLAVE timer interrupt procedure */

#endif // DEVICE_MANAGER_H
