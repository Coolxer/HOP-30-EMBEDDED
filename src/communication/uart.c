#include "communication/uart.h"

#include "enum/type.h"
#include "flag.h"

#include "command/cmd_builder.h"

#include "communication/uart_min.h"
#include "communication/dma/partial/dma_setup.h"
#include "communication/dma/partial/dma_operation.h"

uint8_t *invalid_cmd_length_error = (uint8_t *)"\0";

void uart_init()
{
	uart_min_init();
	dma_init();

	__HAL_LINKDMA(&uart, hdmarx, hdma_usart2_rx);
	__HAL_LINKDMA(&uart, hdmatx, hdma_usart2_tx);

	dma_setup(&uart);

	invalid_cmd_length_error = cmd_builder_buildErr((uint8_t *)"0", ERR.INVALID_COMMAND_LENGTH);
}

uint8_t *uart_listen()
{
	if (!BUFFER_EMPTY) // info if something come on UART
	{
		BUFFER_EMPTY = 1; // reset data flag

		if (dma_isReady()) // if there are command with min 21 length characters
			return dma_getCommand();
		else // if string is too short
			uart_send(invalid_cmd_length_error);
	}

	return (uint8_t *)"\0";
}

void uart_send(uint8_t *message)
{
	if (TRANSFER_COMPLETE)
	{
		TRANSFER_COMPLETE = 0;
		HAL_UART_Transmit_DMA(&uart, (uint8_t *)message, (uint16_t)stringLength(message));
	}
}
