#ifndef STEPPER_CONNECTION_H
#define STEPPER_CONNECTION_H

#include "stm32f4xx_hal.h"

// MASTER_TIMER is PWM timer
// SLAVE_TIMER is Step-Counter timer

/**************** W STEPPER  ******************/

#define W_MASTER_TIMER TIM10
#define W_SLAVE_TIMER TIM9

#define W_ALTERNATE_FUNCTION GPIO_AF3_TIM10
#define W_CHANNEL TIM_CHANNEL_1
#define W_ITR TIM_TS_ITR2
#define W_IRQ TIM1_BRK_TIM9_IRQn

#define W_ENABLE_PORT GPIOC
#define W_ENABLE_PIN GPIO_PIN_9

#define W_STEP_PORT GPIOB
#define W_STEP_PIN GPIO_PIN_8

#define W_DIR_PORT GPIOB
#define W_DIR_PIN GPIO_PIN_9

#define W_DIR_INV 1

/************* END OF W STEPPER  **************/

/**************** X STEPPER  ******************/
#define X_MASTER_TIMER TIM13
#define X_SLAVE_TIMER TIM12

#define X_ALTERNATE_FUNCTION GPIO_AF9_TIM13
#define X_CHANNEL TIM_CHANNEL_1
#define X_ITR TIM_TS_ITR2
#define X_IRQ TIM8_BRK_TIM12_IRQn

#define X_ENABLE_PORT GPIOB
#define X_ENABLE_PIN GPIO_PIN_12

#define X_STEP_PORT GPIOA
#define X_STEP_PIN GPIO_PIN_6

#define X_DIR_PORT GPIOA
#define X_DIR_PIN GPIO_PIN_7

#define X_DIR_INV 0

/************* END OF X STEPPER  **************/

/**************** Y STEPPER  ******************/

#define Y_MASTER_TIMER TIM4
#define Y_SLAVE_TIMER TIM3

#define Y_ALTERNATE_FUNCTION GPIO_AF2_TIM4
#define Y_CHANNEL TIM_CHANNEL_1
#define Y_ITR TIM_TS_ITR2
#define Y_IRQ TIM3_IRQn

#define Y_ENABLE_PORT GPIOC
#define Y_ENABLE_PIN GPIO_PIN_7

#define Y_STEP_PORT GPIOB
#define Y_STEP_PIN GPIO_PIN_6

#define Y_DIR_PORT GPIOA
#define Y_DIR_PIN GPIO_PIN_9

#define Y_DIR_INV 0

/************* END OF Y STEPPER  **************/

/**************** Z STEPPER  ******************/

#define Z_MASTER_TIMER TIM2
#define Z_SLAVE_TIMER TIM5

#define Z_ALTERNATE_FUNCTION GPIO_AF1_TIM2
#define Z_CHANNEL TIM_CHANNEL_3
#define Z_ITR TIM_TS_ITR0
#define Z_IRQ TIM5_IRQn

#define Z_ENABLE_PORT GPIOA
#define Z_ENABLE_PIN GPIO_PIN_8

#define Z_STEP_PORT GPIOB
#define Z_STEP_PIN GPIO_PIN_10

#define Z_DIR_PORT GPIOB
#define Z_DIR_PIN GPIO_PIN_4

#define Z_DIR_INV 1

/************* END OF Z STEPPER  **************/

#endif // STEPPER_CONNECTION_H