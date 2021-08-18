#include "communication/dma/partial/dma_validator.h"

#include "communication/dma/dma.h"
#include "communication/config/communication.h"

#include "command/partial/err.h"

uint8_t checkCommandLengthLimits(uint16_t size)
{
    if (size < MIN_COMMAND_SIZE)
        return ERR.COMMAND_TOO_SHORT;
    else if (size > MAX_COMMAND_SIZE)
        return ERR.COMMAND_TOO_LONG;

    return CORRECT;
}

uint8_t checkCommandBeginTerminator()
{
    if (dma.requestBuffer[0] != COMMAND_BEGIN_TERMINATOR)
        return ERR.COMMAND_INCORRECT_BEGINING;

    return CORRECT;
}

uint8_t checkCommandEndTerminator(uint16_t size)
{
    if (dma.requestBuffer[size - 1] != COMMAND_END_TERMINATOR)
        return ERR.COMMAND_INCORRECT_END;

    return CORRECT;
}

uint8_t validateTransmission(uint16_t size)
{
    uint8_t code = checkCommandLengthLimits(size);

    if (code != CORRECT)
        return code;

    code = checkCommandBeginTerminator();

    if (code != CORRECT)
        return code;

    code = checkCommandEndTerminator(size);

    if (code != CORRECT)
        return code;

    return CORRECT;
}