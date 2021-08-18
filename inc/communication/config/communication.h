#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#define UART_PORT "COM4"      //"COM3"      // signature of serial port [COM3 on the other board]
#define UART_BAUDRATE 2000000 // baudrate of UART communication [default: 115200]
#define UART_NAME USART2
#define UART2_TX GPIO_PIN_2 // define uart tx pin (send)
#define UART2_RX GPIO_PIN_3 // define uart rx pins (receive)

#define MIN_COMMAND_SIZE 16
#define MAX_COMMAND_SIZE 255

#define COMMAND_BEGIN_TERMINATOR '$'
#define COMMAND_END_TERMINATOR '#'

#define COMMAND_PAIR_CONNECTOR '='
#define COMMAND_PARAM_SEPARATOR '|'
#define SENTENCE_END_TERMINATOR '@'

#define MAX_REQUEST_SIZE 50
#define MAX_BUFFER_REQUESTS 10

#define MAX_RESPONSE_SIZE 32
#define MAX_BUFFER_RESPONSES (MAX_BUFFER_REQUESTS + 10) // responses amount same as the requests, but there are additional 10 for devices callbacks (4 steppers and 6 endstops)

#endif // COMMUNICATION_H