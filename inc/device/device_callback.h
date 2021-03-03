#ifndef DEVICE_CALLBACK_H
#define DEVICE_CALLBACK_H

#include "device/device_manager.h"

void endstopClickedCallback();  // endstop clicked callback
void stepperFinishedCallback(); // stepper finished move callback;

/* PRIVATE */ //void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);               /* endstop interrupt procedure */
/* PRIVATE */ //void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);  /* SLAVE timer interrupt procedure */

#endif // DEVICE_CALLBACK_H
