//#ifdef STSTM32

#include "uart.h"

#include <string.h>
#include <stdlib.h>

#include "uart_min.h"
#include "data_assistant.h"

void uart_init()
{
	uart_start();

	data_clear(data, DATA_SIZE);
}

void uart_deinit()
{
	uart_end();
}

void uart_write(uint8_t *message)
{
	HAL_UART_Transmit(&uart, (uint8_t*)message, DATA_SIZE, 1000);
}

void uart_read()
{
	while(1)
	{
		if (__HAL_UART_GET_FLAG(&uart, UART_FLAG_RXNE) == SET)
		{
			HAL_UART_Receive(&uart, data, DATA_SIZE, 100);

			if(!uart_manage())
				break;
		}
	}	
}

bool uart_manage()
{
	data_cut(data, DATA_SIZE);

	if(strcmp(data, "FINISH") == 0)
	{
		strcpy(data, "FINISHED");
		data_build(data, DATA_SIZE);
		return false;
	}
	else
	{
		uint8_t *feedback = connector_manage_data(connector_parse(data), DATA_SIZE);
		data_build(feedback, DATA_SIZE);
		uart_write(feedback);
		data_clear(data, DATA_SIZE);
		free(feedback);
		return true;
	}	
}

//#endif // STSTM32