#ifndef SETTINGS_H
#define SETTINGS_H

#include "stm32f4xx_hal.h"

/* GENERAL SECTION */

#define CLOCK_SPEED 8000000 // main clock speed frequency

/* END OF GENERAL SECTION */

/*************************************************************************************************************/

/* COMMUNICATION SECTION */

#define UART_PORT COM3 // signature of serial port
#define UART_BAUDRATE 115200 // default baudrate of UART communication

#define UART_NAME USART2;
#define USART2_TX GPIO_PIN_2 // define uart tx pin as 2 (send)
#define USART2_RX GPIO_PIN_3 // define uart rx pins as 3 (receive)

/* END OF COMMUNICATION SECTION */

/*************************************************************************************************************/

/* DEVICES SECTION */

/* divider motor  */

#define DIVIDER_TIMER TIM3
#define DIVIDER_PORT GPIOA

#define DIVIDER_DIR GPIO_PIN_1
#define DIVIDER_STEP GPIO_PIN_2
#define DIVIDER_ENABLE GPIO_PIN_3

#define DIVIDER_M1 GPIO_PIN_4
#define DIVIDER_M2 GPIO_PIN_5 
#define DIVIDER_M3 GPIO_PIN_6

#define DIVIDER_TIMER_INIT() __HAL_RCC_TIM3_CLK_ENABLE();   // init TIM3, which service divider motor
#define DIVIDER_TIMER_DEINIT() __HAL_RCC_TIM3_CLK_DISABLE();   // deinit TIM3, which service divider motor

/* end of divider motor declaration  */

/* table motor  */

#define TABLE_TIMER TIM4
#define TABLE_PORT GPIOC

#define TABLE_DIR GPIO_PIN_7
#define TABLE_STEP GPIO_PIN_8
#define TABLE_ENABLE GPIO_PIN_9

#define TABLE_M1 GPIO_PIN_10
#define TABLE_M2 GPIO_PIN_11 
#define TABLE_M3 GPIO_PIN_12

#define TABLE_ENDSTOP GPIO_PIN_13

#define TABLE_TIMER_INIT() __HAL_RCC_TIM4_CLK_ENABLE();   // init TIM4, which service table motor
#define TABLE_TIMER_DEINIT() __HAL_RCC_TIM4_CLK_DISABLE();  // deinit TIM3, which service divider motor

/* end of table motor declaration  */

/*************************************************************************************************************/

#endif // SETTINGS_H 