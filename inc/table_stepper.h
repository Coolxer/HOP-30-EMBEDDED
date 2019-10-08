#ifndef TABLE_STEPPER_H
#define TABLE_STEPPER_H

#include "stepper.h"

/* table motor  */

#define TABLE_TIMER TIM4
#define TABLE_PORT GPIOC

#define TABLE_DIR GPIO_PIN_7
#define TABLE_STEP GPIO_PIN_8
#define TABLE_ENABLE GPIO_PIN_9

#define TABLE_M1 GPIO_PIN_10
#define TABLE_M2 GPIO_PIN_11 
#define TABLE_M3 GPIO_PIN_12

#define TABLE_MIN_ENDSTOP GPIO_PIN_13
#define TABLE_MAX_ENDSTOP GPIO_PIN_14

/* end of table motor declaration  */

struct Stepper table_stepper;

struct Stepper *create_table_stepper();

void release_table_stepper();

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif // TABLE_STEPPER_H
