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

/*************************************** DEVICE SECTION ***************************************/

/**************** X STEPPER  ******************/

#define X_NAME "x"
#define X_PORT GPIOA

#define X_MASTER_TIMER TIM3
#define X_SLAVE_TIMER TIM2

#define X_ALTERNATE_FUNCTION GPIO_AF2_TIM3
#define X_CHANNEL TIM_CHANNEL_1

#define X_STEP GPIO_PIN_6
#define X_DIR GPIO_PIN_7
#define X_ENABLE GPIO_PIN_8

#define X_M1 GPIO_PIN_9
#define X_M2 GPIO_PIN_10
#define X_M3 GPIO_PIN_11

/************* END OF X STEPPER  **************/

/**************** Y STEPPER  ******************/

#define Y_NAME "y"
#define Y_PORT GPIOB

#define Y_MASTER_TIMER TIM4
#define Y_SLAVE_TIMER TIM5

#define Y_ALTERNATE_FUNCTION GPIO_AF2_TIM4
#define Y_CHANNEL TIM_CHANNEL_1

#define Y_STEP GPIO_PIN_6
#define Y_DIR GPIO_PIN_5
#define Y_ENABLE GPIO_PIN_7

#define GPIO_PIN_9
#define GPIO_PIN_10
#define GPIO_PIN_12

/************* END OF Y STEPPER  **************/

/**************** Z STEPPER  ******************/

#define Z_NAME "z"
#define Z_PORT GPIOB

#define Z_MASTER_TIMER TIM10
#define Z_SLAVE_TIMER TIM9

#define Z_ALTERNATE_FUNCTION GPIO_AF3_TIM10
#define Z_CHANNEL TIM_CHANNEL_1

#define Z_STEP GPIO_PIN_8
#define Z_DIR GPIO_PIN_14
#define Z_ENABLE GPIO_PIN_15

#define Z_M1 GPIO_PIN_2
#define Z_M2 GPIO_PIN_3
#define Z_M3 GPIO_PIN_4

/************* END OF Z STEPPER  **************/

/**************** W STEPPER  ******************/

#define W_NAME "w"
#define W_PORT GPIOA

#define W_MASTER_TIMER TIM13
#define W_SLAVE_TIMER TIM12

#define W_ALTERNATE_FUNCTION GPIO_AF9_TIM13
#define W_CHANNEL TIM_CHANNEL_1

#define W_STEP GPIO_PIN_6
#define W_DIR GPIO_PIN_7
#define W_ENABLE GPIO_PIN_8

#define W_M1 GPIO_PIN_13
#define W_M2 GPIO_PIN_14
#define W_M3 GPIO_PIN_15

/************* END OF W STEPPER  **************/

/**************** K STEPPER  ******************/

#define K_NAME "k"
#define K_PORT GPIOA

#define K_MASTER_TIMER TIM1
#define K_SLAVE_TIMER TIM8

#define K_ALTERNATE_FUNCTION GPIO_AF1_TIM1
#define K_CHANNEL TIM_CHANNEL_2

#define K_STEP GPIO_PIN_9
#define K_DIR GPIO_PIN_10
#define K_ENABLE GPIO_PIN_11

#define K_M1 GPIO_PIN_1
#define K_M2 GPIO_PIN_4
#define K_M3 GPIO_PIN_12

/************* END OF K STEPPER  **************/

#endif // SETTINGS_H 