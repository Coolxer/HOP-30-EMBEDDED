//#ifdef STSTM32

#include "uart.h"

#include <string.h>
#include <stdlib.h>

#include "uart_min.h"
#include "dma.h"
#include "data_assistant.h"

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
			//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
			command = dma_getCommand();

			if(strcmp(command, "ON") == 0)
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
			}
			else if(strcmp(command, "OFF") == 0)
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
			}

			free(command);
		}

		/*
		if (__HAL_UART_GET_FLAG(&uart, UART_FLAG_RXNE) == SET) // checks if transmision Flag is set -> something arrived, ready for read
		{
			HAL_UART_Receive(&uart, data, DATA_SIZE, 100); // reads data from UART

			if(!uart_manage()) // checks if upcoming command is "FINISH"
				break;
		}
		*/
	}	
}

void uart_send(uint8_t *message)
{
	//HAL_UART_Transmit(&uart, (uint8_t*)message, DATA_SIZE, 1000); // sends message through UART with 1000 timeout
	HAL_UART_Transmit(&uart, '1', 1, 1000); // sends message through UART with 1000 timeout
}

uint8_t uart_manage()
{
	uint8_t* feedback;

	/*
	if(strcmp(data, "FINISH") == 0) // checks if receive command is "FINISH"
	{
		strcpy(data, "FINISHED"); // prepares feedback command as "FINISHED"
		return false;
	}

	if(strlen(data) == 0) // checks if upcoming data is NULL
		strcpy(feedback, "NULL_DATA_EXCEPTION");
	else
		feedback = connector_manage_data(connector_parse(data), DATA_SIZE); // passes transmission data to connector manage function where it will be processed

	*/
	
	uart_send(feedback); // send feedback through UART port
	free(feedback); // free memory reserved for feedback message
	return 1;
}

//#endif // STSTM32