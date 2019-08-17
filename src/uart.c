#ifdef STSTM32
#include "uart.h"

void uart_setup_gpio()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef gpio;

	gpio.Pin = uart2_tx | uart2_rx;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	gpio.Alternate = GPIO_AF7_USART2;

	HAL_GPIO_Init(GPIOA, &gpio);
}

void uart_setup_dma()
{
    __HAL_RCC_DMA1_CLK_ENABLE();

	/* uart2_rx interface init */
	hdma_uart_rx.Instance = DMA1_Stream5;
	hdma_uart_rx.Init.Channel = DMA_CHANNEL_4;
	hdma_uart_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_uart_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_uart_rx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_uart_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_uart_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_uart_rx.Init.Mode = DMA_NORMAL;
	hdma_uart_rx.Init.Priority = DMA_PRIORITY_LOW;
	hdma_uart_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(&hdma_uart_rx);

	__HAL_LINKDMA(&uart, hdmarx, hdma_uart_rx);

	/* uart2_tx interface init */
	hdma_uart_tx.Instance = DMA1_Stream6;
	hdma_uart_tx.Init.Channel = DMA_CHANNEL_4;
	hdma_uart_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_uart_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_uart_tx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_uart_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_uart_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_uart_tx.Init.Mode = DMA_NORMAL;
	hdma_uart_tx.Init.Priority = DMA_PRIORITY_LOW;
	hdma_uart_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(&hdma_uart_tx);

	__HAL_LINKDMA(&uart, hdmatx, hdma_uart_tx);
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

void uart_setup_nvic()
{
    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

	HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}

void uart_init()
{
    uart_setup_gpio();
	uart_setup_dma();
	uart_setup_interface();
    uart_setup_nvic();

    // start listening to COM port
	HAL_UART_Receive_DMA(&uart, received_data, DATA_SIZE);
}

void uart_send(uint8_t __ATOMIC_CONSUME)
{
    HAL_UART_Transmit(&uart, c, 1, 1000);
}

void uart_deinit()
{
    __HAL_RCC_GPIOA_CLK_DISABLE();
    __HAL_RCC_GPIOA_CLK_DISABLE();

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* usart)
{

}
#endif