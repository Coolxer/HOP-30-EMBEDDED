#include "communication/dma/partial/dma_validator.h"

#include "communication/dma/dma.h"
#include "communication/config/communication.h"

#include "command/partial/err.h"

uint8_t checkCommandLengthLimits()
{
    if (dma.receivedCommandSize < MIN_COMMAND_SIZE)
        return ERR.COMMAND_TOO_SHORT;
    else if (dma.receivedCommandSize > MAX_COMMAND_SIZE)
        return ERR.COMMAND_TOO_LONG;

    return CORRECT;
}

uint8_t checkCommandBeginTerminator()
{
    if (dma.commandBuffer[0] != COMMAND_BEGIN_TERMINATOR)
        return ERR.COMMAND_INCORRECT_BEGINING;

    return CORRECT;
}

uint8_t checkCommandEndTerminator()
{
    if (dma.commandBuffer[dma.receivedCommandSize - 1] != COMMAND_END_TERMINATOR)
        return ERR.COMMAND_INCORRECT_END;

    return CORRECT;
}

uint8_t validateTransmission()
{
    uint8_t code = checkCommandLengthLimits();

    if (code != CORRECT)
        return code;

    code = checkCommandBeginTerminator();

    if (code != CORRECT)
        return code;

    code = checkCommandEndTerminator();

    if (code != CORRECT)
        return code;

    return CORRECT;
}