#ifndef DMA_VALIDATOR_H
#define DMA_VALIDATOR_H

#include "stm32f4xx_hal.h"

uint8_t checkMessageTerminators(); // check if message is fully received, not consists of parts,
                                   // and not overflow at all

uint8_t checkFirstMessageCharacters(); // check if message starts with idx characters
                                       // it is useful with fast receiving data, to not stacked

uint8_t validateTransmission(); // validate if transmission is fine

#endif // DMA_VALIDATOR_H