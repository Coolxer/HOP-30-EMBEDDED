#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "stm32f4xx_hal.h"

#include "communication/uart.h"
#include "communication/dma/dma.h"

// Connector between STM-32 and RPI

void connector_init();
void connector_deinit();

void connector_sendMessage(uint8_t *message);

#endif // CONNECTOR_H