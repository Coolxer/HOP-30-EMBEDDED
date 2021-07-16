#include "communication/dma/partial/dma_callback.h"

#include "command/builder/partial/data_assistant.h"

#include "communication/uart.h"
#include "communication/dma/dma.h"

//#include "command/cmd_manager.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    HAL_UART_Transmit_DMA(&uart, dma.commandBuffer, COMMAND_SIZE);

    dma.commandBuffer[0] = "\0";

    HAL_UART_Receive_DMA(&uart, dma.commandBuffer, COMMAND_SIZE);

    return;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    return;
}