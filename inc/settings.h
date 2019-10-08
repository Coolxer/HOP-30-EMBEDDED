#ifndef SETTINGS_H
#define SETTINGS_H

#include "stm32f4xx_hal.h"

/* GENERAL SECTION */

#define CLOCK_SPEED 8000000 // main clock speed frequency

/* END OF GENERAL SECTION */

/*************************************************************************************************************/

/* COMMUNICATION SECTION */

#define UART_PORT "COM3" // signature of serial port
#define UART_BAUDRATE 115200 // default baudrate of UART communication

#define UART_NAME USART2;
#define USART2_TX GPIO_PIN_2 // define uart tx pin as 2 (send)
#define USART2_RX GPIO_PIN_3 // define uart rx pins as 3 (receive)

/* END OF COMMUNICATION SECTION */

/*************************************************************************************************************/

#endif // SETTINGS_H 