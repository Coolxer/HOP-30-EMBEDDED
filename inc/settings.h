#ifndef SETTINGS_H
#define SETTINGS_H

#include "stm32f4xx_hal.h"

/* GENERAL SECTION */

#define CLOCK_SPEED 8000000

/* END OF GENERAL SECTION */

/*************************************************************************************************************/

/* COMMUNICATION SECTION */

#define UART_PORT COM3
#define UART_SPEED 115200

/* END OF COMMUNICATION SECTION */

/*************************************************************************************************************/

/* DEVICES SECTION */

/* divider motor  */

#define DIVIDER_TIMER TIM3
#define DIVIDER_PORT GPIOA
#define DIVIDER_DIR GPIO_PIN_1
#define DIVIDER_STEP GPIO_PIN_2

#define DIVIDER_M1 GPIO_PIN_3
#define DIVIDER_M2 GPIO_PIN_4 
#define DIVIDER_M3 GPIO_PIN_5

/* end of divider motor declaration  */

/* table motor  */

#define TABLE_TIMER TIM4
#define TABLE_PORT GPIOC
#define TABLE_DIR GPIO_PIN_7
#define TABLE_STEP GPIO_PIN_8

#define TABLE_M1 GPIO_PIN_9
#define TABLE_M2 GPIO_PIN_10 
#define TABLE_M3 GPIO_PIN_11

#define TABLE_ENDSTOP GPIO_PIN_12

/* end of table motor declaration  */

/*************************************************************************************************************/

#endif // SETTINGS_H 