#ifndef DIVIDER_STEPPER_H
#define DIVIDER_STEPPER_H

#include "stepper.h"

/* divider motor  */

#define DIVIDER_TIMER TIM3
#define DIVIDER_PORT GPIOA

#define DIVIDER_DIR GPIO_PIN_1
#define DIVIDER_STEP GPIO_PIN_2
#define DIVIDER_ENABLE GPIO_PIN_3

#define DIVIDER_M1 GPIO_PIN_4
#define DIVIDER_M2 GPIO_PIN_5 
#define DIVIDER_M3 GPIO_PIN_6   

/* end of divider motor declaration  */

struct Stepper divider_stepper;

struct Stepper *create_divider_stepper();

void release_divider_stepper();

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif // DIVIDER_STEPPER_H
