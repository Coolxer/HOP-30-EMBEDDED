//#ifdef STSTM32

#include "uart_min.h"

#include "settings.h"

void uart_setup_gpio()
{
	GPIO_InitTypeDef gpio;

	__HAL_RCC_USART2_CLK_ENABLE();

	gpio.Pin = USART2_TX | USART2_RX; 
	gpio.Mode = GPIO_MODE_AF_PP;	  
	gpio.Pull = GPIO_PULLUP;
	gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio.Alternate = GPIO_AF7_USART2;

	HAL_GPIO_Init(GPIOA, &gpio);
}

void uart_setup_interface()
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
}

void uart_min_init()
{
    uart_setup_gpio();
    uart_setup_interface();
}

void uart_write(char c)
{
    HAL_UART_Transmit(&uart, (uint8_t*)(&c), 1, 1000); // sends 1 char with timeout 1000 through UART
}

void uart_flush()
{
    
}

void uart_min_deinit()
{  
    __HAL_RCC_USART2_CLK_DISABLE(); // disables USART2 clock
}

//#endif // STSTM32