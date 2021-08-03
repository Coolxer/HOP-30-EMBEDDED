#include "communication/uart.h"
#include "communication/config/communication.h"

UART_HandleTypeDef uart = {0};
GPIO_InitTypeDef uartGPIO = {0};

void uart_setupGpio()
{
#ifdef UNIT_TEST
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
#endif

	uartGPIO.Pin = USART2_TX | USART2_RX;
	uartGPIO.Mode = GPIO_MODE_AF_PP;
	uartGPIO.Pull = GPIO_PULLUP;
	uartGPIO.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	uartGPIO.Alternate = GPIO_AF7_USART2;

	HAL_GPIO_Init(GPIOA, &uartGPIO);
}

void uart_setupInterface()
{
	uart.Instance = UART_NAME;
	uart.Init.BaudRate = UART_BAUDRATE;
	uart.Init.WordLength = USART_WORDLENGTH_8B;
	uart.Init.Parity = USART_PARITY_NONE;
	uart.Init.StopBits = UART_STOPBITS_1;
	uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart.Init.OverSampling = UART_OVERSAMPLING_16;
	uart.Init.Mode = UART_MODE_TX_RX;

	HAL_UART_Init(&uart);
	//uart.Instance->BRR = 2;
}

void uart_init()
{
	uart_setupGpio();
	uart_setupInterface();
}

void uart_deinit()
{
#ifdef UNIT_TEST
	__HAL_RCC_USART2_CLK_DISABLE();
	__HAL_RCC_GPIOA_CLK_DISABLE();
#endif

	HAL_GPIO_DeInit(GPIOA, (GPIO_InitTypeDef *)&uartGPIO);
	HAL_UART_DeInit(&uart);
}

void uart_flush()
{
	return;
}

void uart_write(char c)
{
	HAL_UART_Transmit(&uart, (uint8_t *)(&c), 1, 1000); // sends 1 char with timeout 1000 through UART
}
