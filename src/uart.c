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

void uart_deinit()
{
	uart_min_deinit();
	dma_deinit();
}

void uart_listen()
{
	while(1)
	{
		if(dma_isReady())
		{
			command = dma_getCommand();

		/*
			if(strcmp(command, "ON") == 0)
	      {
	        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
	        HAL_UART_Transmit(&uart, "wlaczone", 8, 100);
	      }
	      else if(strcmp(command, "OFF") == 0)
	      {
	        HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_RESET);
	        HAL_UART_Transmit(&uart, "wylaczone", 9, 100);
	      }
	      free(command);

		  */

			if(!uart_manage())
				break;

			free(command);

			//data_clear(command);
		}
	}

	//free(command);
}

void uart_send(uint8_t *message)
{
	HAL_UART_Transmit(&uart, (uint8_t*)message, strlen(message), 1000); // sends message through UART with 100 timeout
}

uint8_t uart_manage()
{
	if(strlen(command) == 0)
		feedback = str_append(feedback, "_ERROR_NULL_DATA_EXCEPTION");
	else if(strcmp(command, "FINISH") == 0) // checks if receive command is "FINISH"
	{
		feedback = str_append(feedback, "FINISHED");
		return 0;
	}
	else
		feedback = connector_manage_data(connector_parse(command)); // passes transmission data to connector manage function where it will be processed
	
	uart_send(feedback); // send feedback through UART port
	data_clear(feedback);
	return 1;
}

//#endif // STSTM32