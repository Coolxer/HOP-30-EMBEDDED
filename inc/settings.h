#ifndef SETTINGS_H
#define SETTINGS_H

#include "stm32f4xx_hal.h"

/* GENERAL SECTION */

#define CLOCK_SPEED 18000000 // main clock speed frequency

/* END OF GENERAL SECTION */

/*************************************************************************************************************/

/* COMMUNICATION SECTION */

#define UART_PORT "COM3" // signature of serial port
#define UART_BAUDRATE 115200 // default baudrate of UART communication

#define UART_NAME USART2
#define USART2_TX GPIO_PIN_2 // define uart tx pin as 2 (send)
#define USART2_RX GPIO_PIN_3 // define uart rx pins as 3 (receive)

/* END OF COMMUNICATION SECTION */

/* DEVICE SECTION */

/* divider motor  */
#define DIVIDER_NAME "x"
#define DIVIDER_TIMER TIM3

#define DIVIDER_ALTERNATE GPIO_AF2_TIM3
#define DIVIDER_CHANNEL TIM_CHANNEL_1

#define DIVIDER_PORT GPIOA

#define DIVIDER_DIR GPIO_PIN_15 
#define DIVIDER_STEP GPIO_PIN_6 // PWM 3/1 
#define DIVIDER_ENABLE GPIO_PIN_10 

#define DIVIDER_M1 GPIO_PIN_7 
#define DIVIDER_M2 GPIO_PIN_9 
#define DIVIDER_M3 GPIO_PIN_8

/* end of divider motor declaration  */

/* table motor  */
#define TABLE_NAME "w"
#define TABLE_TIMER TIM4

#define TABLE_ALTERNATE GPIO_AF2_TIM4
#define TABLE_CHANNEL TIM_CHANNEL_2

#define TABLE_PORT GPIOB

#define TABLE_DIR GPIO_PIN_9
#define TABLE_STEP GPIO_PIN_7 // PWM 4/2
#define TABLE_ENABLE GPIO_PIN_6

#define TABLE_M1 GPIO_PIN_5 
#define TABLE_M2 GPIO_PIN_8 
#define TABLE_M3 GPIO_PIN_13

//#define TABLE_MIN_ENDSTOP GPIO_PIN_13
//#define TABLE_MAX_ENDSTOP GPIO_PIN_14

/* end of table motor declaration  */

/* divider min endstop */
#define DIVIDER_MIN_ENDSTOP_NAME "e1"
#define DIVIDER_MIN_ENDSTOP_PORT GPIOA
#define DIVIDER_MIN_ENDSTOP_PIN GPIO_PIN_4
#define DIVIDER_MIN_ENDSTOP_EXT EXTI4_IRQn

/* end of divider min endstop declaration */

/* END OF DEVICE SECTION */

/*************************************************************************************************************/

#endif // SETTINGS_H 