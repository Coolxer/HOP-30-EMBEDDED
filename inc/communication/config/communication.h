#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#define UART_PORT "COM3"      //"COM4"      // signature of serial port [COM3 on the other board]
#define UART_BAUDRATE 2000000 // baudrate of UART communication [default: 115200]

#define UART_NAME USART2
#define USART2_TX GPIO_PIN_2 // define uart tx pin (send)
#define USART2_RX GPIO_PIN_3 // define uart rx pins (receive)

#define COMMAND_PAIR_CONNECTOR '='
#define COMMAND_PARAM_SEPARATOR '|'
#define SENTENCE_END_TERMINATOR '@'
#define COMMAND_END_TERMINATOR '#'

#define REQUEST_SIZE 255
#define SINGLE_REQUEST_SIZE 50
#define MAX_BUFFER_REQUESTS 10

#define RESPONSE_SIZE 32
#define MAX_BUFFER_RESPONSES (MAX_BUFFER_REQUESTS + 10) // responses amount same as the requests, \
                                                        // but there are additional 10 for devices callbacks (4 steppers and 6 endstops)

#endif // COMMUNICATION_H