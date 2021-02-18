#ifndef STEPPER_CONNECTION_H
#define STEPPER_CONNECTION_H

#include "stm32f4xx_hal.h"

/**************** X STEPPER  ******************/

#define X_NAME (uint8_t *)"x"
#define X_PORT GPIOC

#define X_MASTER_TIMER TIM3
#define X_SLAVE_TIMER TIM2

#define X_ALTERNATE_FUNCTION GPIO_AF2_TIM3
#define X_CHANNEL TIM_CHANNEL_1
#define X_ITR TIM_TS_ITR2
#define X_IRQ TIM2_IRQn

#define X_STEP GPIO_PIN_6
#define X_DIR GPIO_PIN_7
#define X_ENABLE GPIO_PIN_8
#define X_SLEEP GPIO_PIN_9

/************* END OF X STEPPER  **************/

/**************** Y STEPPER  ******************/

#define Y_NAME (uint8_t *)"y"
#define Y_PORT GPIOA

#define Y_MASTER_TIMER TIM13
#define Y_SLAVE_TIMER TIM12

#define Y_ALTERNATE_FUNCTION GPIO_AF9_TIM13
#define Y_CHANNEL TIM_CHANNEL_1
#define Y_ITR TIM_TS_ITR2
#define Y_IRQ TIM8_BRK_TIM12_IRQn

#define Y_STEP GPIO_PIN_6
#define Y_DIR GPIO_PIN_7
#define Y_ENABLE GPIO_PIN_8
#define Y_SLEEP GPIO_PIN_1

/************* END OF Y STEPPER  **************/

/**************** Z STEPPER  ******************/

#define Z_NAME (uint8_t *)"z"
#define Z_PORT GPIOB

#define Z_MASTER_TIMER TIM10
#define Z_SLAVE_TIMER TIM9

#define Z_ALTERNATE_FUNCTION GPIO_AF3_TIM10
#define Z_CHANNEL TIM_CHANNEL_1
#define Z_ITR TIM_TS_ITR2
#define Z_IRQ TIM1_BRK_TIM9_IRQn

#define Z_STEP GPIO_PIN_8
#define Z_DIR GPIO_PIN_14
#define Z_ENABLE GPIO_PIN_15
#define Z_SLEEP GPIO_PIN_9

/************* END OF Z STEPPER  **************/

/**************** W STEPPER  ******************/

#define W_NAME (uint8_t *)"w"
#define W_PORT GPIOB

#define W_MASTER_TIMER TIM4
#define W_SLAVE_TIMER TIM5

#define W_ALTERNATE_FUNCTION GPIO_AF2_TIM4
#define W_CHANNEL TIM_CHANNEL_1
#define W_ITR TIM_TS_ITR2
#define W_IRQ TIM5_IRQn

#define W_STEP GPIO_PIN_6
#define W_DIR GPIO_PIN_5
#define W_ENABLE GPIO_PIN_7
#define W_SLEEP GPIO_PIN_0

/************* END OF W STEPPER  **************/

/**************** K STEPPER  ******************/
/*
#define K_NAME (uint8_t*)"K"
#define K_PORT (GPIO_TypeDef *)GPIOA

#define K_MASTER_TIMER TIM1
#define K_SLAVE_TIMER TIM8

#define K_ALTERNATE_FUNCTION GPIO_AF1_TIM1
#define K_CHANNEL TIM_CHANNEL_2
#define K_ITR TIM_TS_ITR0

#define K_STEP GPIO_PIN_9
#define K_DIR GPIO_PIN_10
#define K_ENABLE GPIO_PIN_11

*/
/************* END OF K STEPPER  **************/

#endif // STEPPER_CONNECTION_H