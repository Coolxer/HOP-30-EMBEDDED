#ifndef DMA_VALIDATOR_H
#define DMA_VALIDATOR_H

#include "stm32f4xx_hal.h"

uint8_t checkCommandLengthLimits();

uint8_t checkCommandBeginTerminator();
uint8_t checkCommandEndTerminator(); // check if message is fully received and not overflow at all

uint8_t validateTransmission(); // validate if transmission is fine

#endif // DMA_VALIDATOR_H