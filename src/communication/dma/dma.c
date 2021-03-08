#include "communication/dma/dma.h"

DMA_HandleTypeDef hdma_usart2_rx = {0};
DMA_HandleTypeDef hdma_usart2_tx = {0};

DMA dma = {0};
UART_HandleTypeDef *huart = NULL;