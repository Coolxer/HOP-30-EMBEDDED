#ifndef DMA_VALIDATOR_H
#define DMA_VALIDATOR_H

#include "stm32f4xx_hal.h"

uint8_t checkCommandLengthLimits(uint16_t size);

uint8_t checkCommandBeginTerminator();
uint8_t checkCommandEndTerminator(uint16_t size); // check if message is fully received and not overflow at all

uint8_t validateTransmission(uint16_t size); // validate if transmission is fine

#endif // DMA_VALIDATOR_H