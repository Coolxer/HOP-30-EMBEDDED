#ifndef DMA_INTERRUPT_H
#define DMA_INTERRUPT_H

#include "stm32f4xx_hal.h"

uint8_t TRANSFER_IS_COMPLETE(); // returns TRUE if transfer is complete (depend on FLAG)

/* PRIVATE */ //void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart); // updates transfer complete flag
/* PRIVATE */ //static HAL_StatusTypeDef UART_Transmit_IT(UART_HandleTypeDef *huart);    // transmit event callback
/* PRIVATE */ //static HAL_StatusTypeDef UART_EndTransmit_IT(UART_HandleTypeDef *huart); // finished transmit callback

void dma_transmit_interrupt(UART_HandleTypeDef *huart);     // transmit event callback handler
void dma_end_transmit_interrupt(UART_HandleTypeDef *huart); //transmit event callback handler

#endif // DMA_INTERRUPT_H