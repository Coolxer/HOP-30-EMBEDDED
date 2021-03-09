#include "communication/dma/partial/dma_interrupt.h"

#include "null.h"
#include "communication/dma/dma.h"

volatile uint8_t TRANSFER_COMPLETE = SET;

uint8_t TRANSFER_IS_COMPLETE()
{
    if (TRANSFER_COMPLETE)
    {
        TRANSFER_COMPLETE = RESET;
        return 1;
    }

    return 0;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    TRANSFER_COMPLETE = SET;
    UNUSED(huart);
}

static HAL_StatusTypeDef UART_Transmit_IT(UART_HandleTypeDef *huart)
{
    uint16_t *tmp = NULL;

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
            __HAL_UART_DISABLE_IT(huart, UART_IT_TXE);
            __HAL_UART_ENABLE_IT(huart, UART_IT_TC);
        }
        return HAL_OK;
    }
    else
        return HAL_BUSY;
}

void dma_transmit_interrupt(UART_HandleTypeDef *huart)
{
    UART_Transmit_IT(huart);
}

static HAL_StatusTypeDef UART_EndTransmit_IT(UART_HandleTypeDef *huart)
{
    __HAL_UART_DISABLE_IT(huart, UART_IT_TC);

    huart->gState = HAL_UART_STATE_READY;

    HAL_UART_TxCpltCallback(huart);

    return HAL_OK;
}

void dma_end_transmit_interrupt(UART_HandleTypeDef *huart)
{
    UART_EndTransmit_IT(huart);
}
