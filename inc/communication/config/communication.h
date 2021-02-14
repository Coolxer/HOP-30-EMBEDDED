#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#define UART_PORT "COM3"     // signature of serial port
#define UART_BAUDRATE 115200 // default baudrate of UART communication

#define UART_NAME USART2
#define USART2_TX GPIO_PIN_2 // define uart tx pin (send)
#define USART2_RX GPIO_PIN_3 // define uart rx pins (receive)

#endif // COMMUNICATION_H