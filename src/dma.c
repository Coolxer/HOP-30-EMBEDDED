#include "dma.h"

#include <string.h>
#include <stdlib.h>

#include "data_assistant.h"

DMA dma;
UART_HandleTypeDef *huart;

/* *********************** SETUP FUNCTIONS ***************************** */

void dma_setup(UART_HandleTypeDef *uart)
{
	dma.uart = uart;

	__HAL_UART_ENABLE_IT(dma.uart, UART_IT_IDLE);	  // enable UART IDLE interrupt
	__HAL_DMA_ENABLE_IT(dma.uart->hdmarx, DMA_IT_TC); // enable DMA TC (transfer complete) interrupt

	HAL_UART_Receive_DMA(dma.uart, dma.dma_buffer, DMA_BUFFER_SIZE); // start listening by DMA and to DMA buffer

	dma.uart->hdmarx->Instance->CR &= ~DMA_SxCR_HTIE; // for sure, disable HC (half-transfer complete) interrupt

	dma.head = dma.tail = 0; // reset head and tail (means the positions in buffer)
	dma.commands_count = 0;	 // reset number of commands ready to process

	dma.empty = 1; // set the state of dma (if data come this will be set to 0)

	huart = uart; // set pointer to uart (using by DMA1_Stream6 -> for TX transfer with DMA)
}

void dma_setupInterface()
{
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

	hdma_usart2_tx.Instance = DMA1_Stream6;
	hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
	hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_usart2_tx.Init.Mode = DMA_NORMAL;
	hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
	hdma_usart2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

	HAL_DMA_Init(&hdma_usart2_tx);
}

void dma_setupInterrupts()
{
	/* USART2 interrupt Init */
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);

	/* DMA1_Stream5_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

	HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}

void dma_init()
{
	dma_setupInterface();
	dma_setupInterrupts();
}

/* *********************** OPERATIONAL FUNCTIONS ***************************** */

uint8_t dma_isEmpty()
{
	return dma.empty;
}

void dma_clear()
{
	dma.empty = 1;
}

uint8_t dma_isReady()
{
	if (dma.commands_count) // check if commands_count is greater than 0
		return 1;

	return 0;
}

uint8_t dma_getChar()
{
	if (dma.head == dma.tail)
		return 0;

	dma.tail = (dma.tail + 1) % UART_BUFFER_SIZE; // set tail index
	return dma.uart_buffer[dma.tail];			  // return character from buffer
}

uint8_t *dma_getCommand()
{
	uint8_t ch;
	uint8_t *cmd = (uint8_t *)"";

	while ((ch = dma_getChar()))
	{
		if (ch == '\n') // check if there is end of line (LF), which means command end?
			break;

		cmd = char_append(cmd, ch); // append char to command
	}

	if (dma.commands_count)
		dma.commands_count--; // decrease number of commands, which exists in buffer

	return cmd;
}

uint8_t isTCReady()
{
	return tcReady;
}

void useTC()
{
	tcReady = 0;
}

/* ***************************** HANDLERS ********************************** */

void dma_uartHandler()
{
	if (dma.uart->Instance->SR & UART_FLAG_IDLE) // check if idle flag is set
	{
		volatile uint32_t tmp;
		tmp = dma.uart->Instance->SR;					// Read status register
		tmp = dma.uart->Instance->DR;					// Read data register
		dma.uart->hdmarx->Instance->CR &= ~DMA_SxCR_EN; // Disable DMA -> force Transfer Complete interrupt
	}
}

void dma_dmaHandler()
{
	uint8_t i, response_length = 0;
	uint16_t temp;
	DMA_HandleTypeDef *hdma = dma.uart->hdmarx;

	typedef struct
	{
		__IO uint32_t ISR; // DMA interrupt status register
		__IO uint32_t Reserved0;
		__IO uint32_t IFCR; // DMA interrupt flag clear register
	} Dma_registers;

	Dma_registers *regs = (Dma_registers *)hdma->StreamBaseAddress; // get base address of registers

	if (__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_TC) != RESET)
	{
		// there was a difference DMA_FLAG_TCIF1_5
		regs->IFCR = DMA_FLAG_TCIF0_4 << hdma->StreamIndex; // Clear Transfer Complete flag

		response_length = DMA_BUFFER_SIZE - hdma->Instance->NDTR; // read incoming data length

		dma.empty = 0; // set empty flag to 0 means that dma is not empty

		if (response_length >= 21) // min length of command is 21 (calculated, first validation)
		{
			for (i = 0; i < response_length; i++)
			{
				temp = (dma.head + 1) % UART_BUFFER_SIZE;

				if (temp == dma.tail)
					dma.head = dma.tail;
				else
				{
					dma.uart_buffer[temp] = dma.dma_buffer[i];

					if (dma.uart_buffer[temp] == '\n') // if there is end of line sign, that means this is end of command
						dma.commands_count++;		   // so increase number of commands

					dma.head = temp;
				}
			}
		}

		regs->IFCR = 0x3FU << hdma->StreamIndex;		 // clear all interrupts that are in common with transport
		hdma->Instance->M0AR = (uint32_t)dma.dma_buffer; // set address for dma buffer again
		hdma->Instance->NDTR = DMA_BUFFER_SIZE;			 // set length of response
		hdma->Instance->CR |= DMA_SxCR_EN;				 // start DMA transfer
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	tcReady = 1;
}

static HAL_StatusTypeDef UART_Transmit_IT(UART_HandleTypeDef *huart)
{
	uint16_t *tmp;

	/* Check that a Tx process is ongoing */
	if (huart->gState == HAL_UART_STATE_BUSY_TX)
	{
		if (huart->Init.WordLength == UART_WORDLENGTH_9B)
		{
			tmp = (uint16_t *)huart->pTxBuffPtr;
			huart->Instance->DR = (uint16_t)(*tmp & (uint16_t)0x01FF);

			if (huart->Init.Parity == UART_PARITY_NONE)
				huart->pTxBuffPtr += 2U;
			else
				huart->pTxBuffPtr += 1U;
		}
		else
			huart->Instance->DR = (uint8_t)(*huart->pTxBuffPtr++ & (uint8_t)0x00FF);

		if (--huart->TxXferCount == 0U)
		{
			/* Disable the UART Transmit Complete Interrupt */
			__HAL_UART_DISABLE_IT(huart, UART_IT_TXE);

			/* Enable the UART Transmit Complete Interrupt */
			__HAL_UART_ENABLE_IT(huart, UART_IT_TC);
		}
		return HAL_OK;
	}
	else
		return HAL_BUSY;
}

static HAL_StatusTypeDef UART_EndTransmit_IT(UART_HandleTypeDef *huart)
{
	/* Disable the UART Transmit Complete Interrupt */
	__HAL_UART_DISABLE_IT(huart, UART_IT_TC);

	/* Tx process is ended, restore huart->gState to Ready */
	huart->gState = HAL_UART_STATE_READY;

	HAL_UART_TxCpltCallback(huart);

	return HAL_OK;
}

void USART2_IRQHandler(void)
{
	dma_uartHandler();

	uint32_t isrflags = READ_REG(dma.uart->Instance->SR);
	uint32_t cr1its = READ_REG(dma.uart->Instance->CR1);

	/* UART in mode Transmitter ------------------------------------------------*/
	if (((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
	{
		UART_Transmit_IT(&dma.uart);
		return;
	}

	/* UART in mode Transmitter end --------------------------------------------*/
	if (((isrflags & USART_SR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))
	{
		UART_EndTransmit_IT(&dma.uart);
		return;
	}
}

void DMA1_Stream5_IRQHandler(void)
{
	dma_dmaHandler();
}

void DMA1_Stream6_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_usart2_tx);
	/*
    huart->gState = HAL_UART_STATE_READY;
	hdma_usart2_tx.State = HAL_DMA_STATE_READY;
	__HAL_DMA_CLEAR_FLAG(&hdma_usart2_tx, DMA_FLAG_TCIF2_6);
	__HAL_DMA_CLEAR_FLAG(&hdma_usart2_tx, DMA_FLAG_HTIF2_6);
	__HAL_DMA_CLEAR_FLAG(&hdma_usart2_tx, DMA_FLAG_FEIF2_6);
	__HAL_UNLOCK(&hdma_usart2_tx);
	*/
}
