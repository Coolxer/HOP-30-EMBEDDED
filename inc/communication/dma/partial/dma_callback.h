#ifndef DMA_CALLBACK_H
#define DMA_CALLBACK_H

#include "communication/config/communication.h"

#include "stm32f4xx_hal.h"

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

#endif // DMA_CALLBACK_H