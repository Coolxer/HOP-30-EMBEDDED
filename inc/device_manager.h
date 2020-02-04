#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "Stepper.h"
#include "Endstop.h"

#define STEPPERS_COUNT 1 //3                     // number of serviced devices
#define ENDSTOPS_COUNT 1

void device_manager_init();                     // sets devices parameters and reset current device
void device_manager_deinit();
Stepper* device_manager_get_stepper(uint8_t *name); // sets current device by name, if device name is not recognized, returns FALSE

/* PRIVATE */   //void EXTI4_IRQHandler(void)   /* endstop interrupt handler */
/* PRIVATE */   //void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);   /* endstop interrupt procecure */

/* PRIVATE */   //void TIM4_IRQHandler(void);
/* PRIVATE */   //void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);  /* SLAVE timer interrupt procedure */

#endif // DEVICE_MANAGER_H
