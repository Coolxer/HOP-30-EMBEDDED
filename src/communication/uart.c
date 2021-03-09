#include "communication/uart.h"

#include "null.h"

#include "command/cmd_builder.h"

#include "communication/uart_min.h"
#include "communication/dma/partial/dma_setup.h"
#include "communication/dma/partial/dma_handler.h"
#include "communication/dma/partial/dma_interrupt.h"
#include "communication/dma/partial/dma_operation.h"

void uart_init()
{
	uart_min_init();
	dma_init();

	__HAL_LINKDMA(&uart, hdmarx, hdma_usart2_rx);
	__HAL_LINKDMA(&uart, hdmatx, hdma_usart2_tx);

	dma_setup(&uart);
}

uint8_t *uart_listen()
{
	if (BUFFER_IS_NOT_EMPTY())
	{
		if (dma_isReady()) // if there are command with min 21 length characters
			return dma_getCommand();
		else // if string is too short
			uart_send(cmd_builder_buildErr(ZER0_INDEX, ERR.INVALID_COMMAND_LENGTH));
	}

	return EMPTY;
}

void uart_send(uint8_t *message)
{
	if (TRANSFER_IS_COMPLETE())
		HAL_UART_Transmit_DMA(&uart, (uint8_t *)message, (uint16_t)stringLength(message));
}
