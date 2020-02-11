//#ifdef STSTM32

#include "uart.h"

#include <string.h>
#include <stdlib.h>

#include "uart_min.h"
#include "dma.h"
#include "data_assistant.h"

uint8_t *command;
uint8_t *feedback;

void uart_init()
{
	uart_min_init();
    dma_init();
	
	__HAL_LINKDMA(&uart,hdmarx,hdma_usart2_rx);

	dma_setup(&uart);
}

void uart_listen()
{
	while(1)
	{
		if(!dma_isEmpty()) // info if something come
		{
			if(dma_isReady())
			{
				command = dma_getCommand();

				if(!uart_manage())
					break;
			}
			else
				uart_send((uint8_t*)"_ERROR_invalid_command_length");

			dma_clear();
		}	
	}

	free(command);
	free(feedback);
}

void uart_send(uint8_t *message)
{
	HAL_UART_Transmit(&uart, (uint8_t*)message, strlen((void*)message), 1000); // sends message through UART with 100 timeout
}

uint8_t uart_manage()
{
	feedback = (uint8_t*)"";

	if(strcmp((void*)command, "FINISH") == 0) // checks if receive command is "FINISH"
	{
		feedback = str_append(feedback, (uint8_t*)"FINISHED");
		return 0;
	}
	else
		feedback = connector_manage(connector_parse(command)); // passes transmission data to connector manage function where it will be processed
	
	uart_send(feedback); // send feedback through UART port
	//free(feedback);
	return 1;
}

//#endif // STSTM32