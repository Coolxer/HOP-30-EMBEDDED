#ifdef STSTM32

#include "uart_min.h"

void uart_setup_gpio()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef gpio;

	gpio.Pin = USART2_TX | USART2_RX;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	gpio.Alternate = GPIO_AF7_USART2;

	HAL_GPIO_Init(GPIOA, &gpio);
}

void uart_setup_interface()
{
    __HAL_RCC_USART2_CLK_ENABLE();

	uart.Instance = USART2;
	uart.Init.BaudRate = 115200;
	uart.Init.WordLength = USART_WORDLENGTH_8B;
	uart.Init.Parity = USART_PARITY_NONE;
	uart.Init.StopBits = UART_STOPBITS_1;
	uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart.Init.OverSampling = UART_OVERSAMPLING_16;
	uart.Init.Mode = UART_MODE_TX_RX;

	HAL_UART_Init(&uart);
}

void uart_enable()
{
    uart_setup_gpio();
    uart_setup_interface();
}

void uart_send(char c)
{
    HAL_UART_Transmit(&uart, (uint8_t*)(&c), 1, 1000);
}

void uart_flush()
{
    
}

void uart_disable()
{
    __HAL_RCC_GPIOA_CLK_DISABLE();
    __HAL_RCC_USART2_CLK_DISABLE();
}

#endif // STSTM32