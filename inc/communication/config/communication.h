#ifndef COMMUNICATION_H
#define COMMUNICATION_H

// #define UART_PORT "COM3"     // signature of serial port
#define UART_PORT "COM4"     // signature of serial port
#define UART_BAUDRATE 115200 // default baudrate of UART communication
// #define UART_BAUDRATE 2000000 // default baudrate of UART communication

#define UART_NAME USART2
#define USART2_TX GPIO_PIN_2 // define uart tx pin (send)
#define USART2_RX GPIO_PIN_3 // define uart rx pins (receive)

#define REQUEST_SIZE 255
#define RESPONSE_SIZE 32

#define MAX_SINGLE_REQUEST_SIZE 36
#define MAX_BUFFER_REQUESTS 10

#endif // COMMUNICATION_H