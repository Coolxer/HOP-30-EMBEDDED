#ifndef SETTINGS_H
#define SETTINGS_H

#include "stm32f4xx_hal.h"

/************************************* GENERAL SECTION ****************************************/

#define CLOCK_SPEED 18000000 // main clock speed frequency

/********************************** END OF GENERAL SECTION ************************************/


/*********************************** COMMUNICATION SECTION ***********************************/

#define UART_PORT "COM3" // signature of serial port
#define UART_BAUDRATE 115200 // default baudrate of UART communication

#define UART_NAME USART2
#define USART2_TX GPIO_PIN_2 // define uart tx pin as 2 (send)
#define USART2_RX GPIO_PIN_3 // define uart rx pins as 3 (receive)

/******************************* END OF COMMUNICATION SECTION *********************************/

/************************************* DEVICES SECTION ****************************************/

/**************** X STEPPER  ******************/

#define X_NAME "x"
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

#define X_M1 GPIO_PIN_9
#define X_M2 GPIO_PIN_10
#define X_M3 GPIO_PIN_11

/************* END OF X STEPPER  **************/

/**************** Y STEPPER  ******************/

#define Y_NAME "y"
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

//#define W_M1 GPIO_PIN_13 // cannot be
#define Y_M1 GPIO_PIN_1
//#define W_M2 GPIO_PIN_14 // cannot be
#define Y_M2 GPIO_PIN_4
#define Y_M3 GPIO_PIN_12

/************* END OF Y STEPPER  **************/

/**************** Z STEPPER  ******************/

#define Z_NAME "z"
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

#define Z_M1 GPIO_PIN_9
#define Z_M2 GPIO_PIN_10
#define Z_M3 GPIO_PIN_12

/************* END OF Z STEPPER  **************/

/**************** W STEPPER  ******************/

#define W_NAME "w"
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

// not sure about this 3 pins
#define W_M1 GPIO_PIN_0
#define W_M2 GPIO_PIN_1
#define W_M3 GPIO_PIN_13

/************* END OF W STEPPER  **************/

/**************** K STEPPER  ******************/
/*
#define K_NAME "k"
#define K_PORT GPIOA

#define K_MASTER_TIMER TIM1
#define K_SLAVE_TIMER TIM8

#define K_ALTERNATE_FUNCTION GPIO_AF1_TIM1
#define K_CHANNEL TIM_CHANNEL_2
#define K_ITR TIM_TS_ITR0

#define K_STEP GPIO_PIN_9
#define K_DIR GPIO_PIN_10
#define K_ENABLE GPIO_PIN_11

#define K_M1 GPIO_PIN_1
#define K_M2 GPIO_PIN_4
#define K_M3 GPIO_PIN_12
*/
/************* END OF K STEPPER  **************/

/********************************* END OF DEVICES SECTION ************************************/

/************************************ ENDSTOPS SECTION ***************************************/

/*********** X STEPPER ENDSTOPS ***************/

/***** LEFT ENDSTOP *****/

#define XL_NAME "XL"
#define XL_PORT GPIOC
#define XL_PIN GPIO_PIN_0
#define XL_IRQ EXTI0_IRQn

/** END OF LEFT ENDSTOP */

/**** RIGHT ENDSTOP *****/

#define XR_NAME "XR"
#define XR_PORT GPIOC
#define XR_PIN GPIO_PIN_1
#define XR_IRQ EXTI1_IRQn

/* END OF RIGHT ENDSTOP */

/******** END OF X STEPPER ENDSTOPS ***********/

/*********** Y STEPPER ENDSTOPS ***************/

/***** LEFT ENDSTOP *****/

#define YL_NAME "YL"
#define YL_PORT GPIOC
#define YL_PIN GPIO_PIN_2
#define YL_IRQ EXTI2_IRQn

/** END OF LEFT ENDSTOP */

/**** RIGHT ENDSTOP *****/

#define YR_NAME "YR"
#define YR_PORT GPIOC
#define YR_PIN GPIO_PIN_3
#define YR_IRQ EXTI3_IRQn

/* END OF RIGHT ENDSTOP */

/******** END OF Y STEPPER ENDSTOPS ***********/

/*********** Z STEPPER ENDSTOPS ***************/

/***** LEFT ENDSTOP *****/

#define ZL_NAME "ZL"
#define ZL_PORT GPIOC
#define ZL_PIN GPIO_PIN_4
#define ZL_IRQ EXTI4_IRQn

/** END OF LEFT ENDSTOP */

/**** RIGHT ENDSTOP *****/

#define ZR_NAME "ZR"
#define ZR_PORT GPIOC
#define ZR_PIN GPIO_PIN_5
#define ZR_IRQ EXTI9_5_IRQn

/* END OF RIGHT ENDSTOP */

/******** END OF Z STEPPER ENDSTOPS ***********/


/********************************* END OF ENDSTOPS SECTION ***********************************/

#endif // SETTINGS_H 