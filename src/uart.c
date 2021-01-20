//#ifdef STSTM32
#include "uart.h"

#include <stdlib.h>
#include <string.h>

#include "connector.h"
#include "uart_min.h"
#include "dma.h"

void uart_init()
{
	uart_min_init();
	dma_init();

	__HAL_LINKDMA(&uart, hdmarx, hdma_usart2_rx);
	__HAL_LINKDMA(&uart, hdmatx, hdma_usart2_tx);

	dma_setup(&uart);
}

uint8_t uart_listen()
{
	if (!dma_isEmpty()) // info if something come
	{
		if (dma_isReady())
		{
			command = dma_getCommand();
			feedback = (uint8_t *)"";
			return 1;
		}
		else
			uart_send((uint8_t *)"_ERROR_invalid_command_length");

		dma_clear();
	}

	return 0;
}

void uart_send(uint8_t *message)
{
	if (tcReady)
	{
		useTC();
		HAL_UART_Transmit_DMA(&uart, (uint8_t *)message, strlen((void *)message));
	}
}

uint8_t uart_manage()
{
	//free(feedback);
	return 1;
}

//#endif // STSTM32