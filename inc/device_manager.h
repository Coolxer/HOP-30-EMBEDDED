#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "Stepper.h"
#include "Endstop.h"

#define STEPPERS_COUNT 4                                                        // number of steppers
#define ENDSTOPS_COUNT 1                                                        // number of endstops

void device_manager_init();                                                     // sets devices
void device_manager_deinit();                                                   // resets devices
Stepper* device_manager_get_stepper(uint8_t *name);                             // returns pointer to device by name, if device name is not recognized, returns NULL

/* PRIVATE */   //void EXTI4_IRQHandler(void)                                   /* endstop interrupt handler */
/* PRIVATE */   //void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);               /* endstop interrupt procedure */

/* PRIVATE */   //void TIM2_IRQHandler(void);                                   /* TIM2 interrupt handler */
/* PRIVATE */   //void TIM5_IRQHandler(void);                                   /* TIM5 interrupt handler */
/* PRIVATE */   //void TIM1_BRK_TIM9_IRQHandler(void);                          /* TIM9 interrupt handler */
/* PRIVATE */   //void TIM8_BRK_TIM12_IRQHandler(void);                         /* TIM12 interrupt handler */

/* PRIVATE */   //void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);  /* SLAVE timer interrupt procedure */


#endif // DEVICE_MANAGER_H
