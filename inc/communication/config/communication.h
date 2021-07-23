#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#define UART_PORT "COM4"      // signature of serial port
#define UART_BAUDRATE 2000000 // default baudrate of UART communication

#define UART_NAME USART2
#define USART2_TX GPIO_PIN_2 // define uart tx pin (send)
#define USART2_RX GPIO_PIN_3 // define uart rx pins (receive)

#define REQUEST_SIZE 48
#define RESPONSE_SIZE 32

#define MIN_TRUNC_REQUEST_SIZE 21 // minimum command length to be sure it is correct

#endif // COMMUNICATION_H