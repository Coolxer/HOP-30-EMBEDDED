#include "dma.h"

#include <string.h>
#include <stdlib.h>

#include "data_assistant.h"

/* *********************** SETUP FUNCTIONS ***************************** */

void dma_setup(UART_HandleTypeDef* uart)
{
	dma.uart = uart;

	__HAL_UART_ENABLE_IT(dma.uart, UART_IT_IDLE); // enable UART IDLE interrupt
	__HAL_DMA_ENABLE_IT(dma.uart->hdmarx, DMA_IT_TC); // enable DMA TC (transfer complete) interrupt

	HAL_UART_Receive_DMA(dma.uart, dma.dma_buffer, DMA_BUFFER_SIZE); // start listening by DMA and to DMA buffer

 	dma.uart->hdmarx->Instance->CR &= ~DMA_SxCR_HTIE; // for sure, disable HC (half-transfer complete) interrupt

 	dma.head = dma.tail = 0;
 	dma.commands_count = 0;
}

void dma_setup_interface()
{
	__HAL_RCC_DMA1_CLK_ENABLE();

    hdma_usart2_rx.Instance = DMA1_Stream5;
    hdma_usart2_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

	HAL_DMA_Init(&hdma_usart2_rx);
}

void dma_setup_interrupts()
{
    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);

    /* DMA1_Stream5_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
}

void dma_init()
{
    dma_setup_interface();
    dma_setup_interrupts();
}

void dma_deinit()
{
	__HAL_RCC_DMA1_CLK_DISABLE();
}

/* *********************** OPERATIONAL FUNCTIONS ***************************** */

uint8_t dma_isReady()
{
    if(dma.commands_count) // check if commands_count > 0
		return 1;

	return 0;
}

uint8_t dma_getChar()
{
    if(dma.head == dma.tail)
		return -1;

	dma.tail = (dma.tail + 1) % UART_BUFFER_SIZE; // get tail index
	return dma.uart_buffer[dma.tail];
}

uint8_t* dma_getCommand()
{
    uint8_t ch;
	uint8_t* cmd = "";

	while((ch = dma_getChar()))
	{
		if(ch == '\n') // check if there is end of line (LF), which means command end?
			break;

		cmd = char_append(cmd, ch); // append char to command
	}

	dma.commands_count--; // decrease number of commands, which exists in buffer

	return cmd;
}


/* ***************************** HANDLERS ********************************** */

void dma_uart_handler()
{
    if(dma.uart->Instance->SR & UART_FLAG_IDLE) // check if idle flag is set
	{
		volatile uint32_t tmp;
		tmp = dma.uart->Instance->SR;  // Read status register
		tmp = dma.uart->Instance->DR;  // Read data register
		dma.uart->hdmarx->Instance->CR &= ~DMA_SxCR_EN; // Disable DMA -> force Transfer Complete interrupt
	}
}

void dma_dma_handler()
{
    uint8_t i, response_length = 0;
	uint16_t temp;
	DMA_HandleTypeDef *hdma = dma.uart->hdmarx;

	typedef struct
	{
		__IO uint32_t ISR;   // DMA interrupt status register
		__IO uint32_t Reserved0;
		__IO uint32_t IFCR;  // DMA interrupt flag clear register
	}Dma_registers;

	Dma_registers *regs = (Dma_registers *)hdma->StreamBaseAddress; // get base address of registers

	if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_TC) != RESET)
	{
		// there was a difference DMA_FLAG_TCIF1_5
		regs->IFCR = DMA_FLAG_TCIF0_4 << hdma->StreamIndex; // Clear Transfer Complete flag

		response_length = DMA_BUFFER_SIZE - hdma->Instance->NDTR;

		for(i = 0; i < response_length; i++)
		{
			temp = (dma.head + 1) % UART_BUFFER_SIZE;

			if(temp == dma.tail)
				dma.head = dma.tail;
			else
			{
				dma.uart_buffer[temp] = dma.dma_buffer[i];

				if(dma.uart_buffer[temp] == '\n') // if there is end of line sign, that means this is end of command
					dma.commands_count++; // so increase number of commands

				dma.head = temp;
			}
		}

		regs->IFCR = 0x3FU << hdma->StreamIndex; // clear all interrupts that are in common with transport
		hdma->Instance->M0AR = (uint32_t)dma.dma_buffer; // set address for dma buffer again
		hdma->Instance->NDTR = DMA_BUFFER_SIZE; // set length of response
		hdma->Instance->CR |= DMA_SxCR_EN; // start DMA transfer
	}
}

void USART2_IRQHandler(void)
{
	dma_uart_handler();
}

void DMA1_Stream5_IRQHandler(void)
{
    dma_dma_handler();
}