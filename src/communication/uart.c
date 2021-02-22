//#ifdef STSTM32
#include "communication/uart.h"

#include <string.h>

#include "command/partial/data_assistant.h"
#include "communication/uart_min.h"
#include "communication/dma/partial/dma_setup.h"
#include "communication/dma/partial/dma_operation.h"
#include "connector.h"

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
			return TRUE;
		}
		else
			uart_send((uint8_t *)"_ERR_invalid_command_length");

		dma_clear();
	}

	return FALSE;
}

void uart_send(uint8_t *message)
{
	if (tcReady)
	{
		// useTC();
		tcReady = 0;
		HAL_UART_Transmit_DMA(&uart, (uint8_t *)message, strlen((void *)message));
	}
}

//#endif // STSTM32