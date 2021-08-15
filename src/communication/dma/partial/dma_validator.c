#include "communication/dma/partial/dma_validator.h"

#include "communication/dma/dma.h"
#include "communication/config/communication.h"

uint8_t checkMessageTerminators()
{
    uint8_t i = 0;

    for (; i < (REQUEST_SIZE - 1); i++)
    {
        if (dma.requestBuffer[i] == COMMAND_END_TERMINATOR)
            return 0;
    }

    if (dma.requestBuffer[REQUEST_SIZE - 1] != COMMAND_END_TERMINATOR)
        return 0;

    return 1;
}

uint8_t checkFirstMessageCharacters()
{
    if (dma.requestBuffer[0] != 'i')
        return 0;

    if (dma.requestBuffer[1] != 'd')
        return 0;

    if (dma.requestBuffer[2] != 'x')
        return 0;

    return 1;
}

uint8_t validateTransmission()
{
    if (checkMessageTerminators() && checkFirstMessageCharacters())
        return 1;

    return 0;
}