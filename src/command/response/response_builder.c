#include "command/response/response_builder.h"

#include <stdio.h>
#include "null.h"

#include "communication/config/communication.h"

uint8_t response[RESPONSE_SIZE];

void response_builder_formatResponse()
{
    uint8_t n = 0;

    while (n < RESPONSE_SIZE)
    {
        if (response[n] == COMMAND_END_TERMINATOR)
            break;

        n++;
    }

    uint8_t i = (uint8_t)(n + 1);

    for (; i < RESPONSE_SIZE; i++)
        response[i] = COMMAND_PARAM_SEPARATOR;

    response[RESPONSE_SIZE - 1] = EMPTY_CHARACTER;
}

uint8_t *response_builder_buildPas(uint8_t *index)
{
    snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%c%c", KEY.INDEX, COMMAND_PAIR_CONNECTOR, index, COMMAND_PARAM_SEPARATOR, KEY.RESPONSE, COMMAND_PAIR_CONNECTOR, RES.PASSED, COMMAND_PARAM_SEPARATOR, COMMAND_END_TERMINATOR);

    response_builder_formatResponse();

    return response;
}

uint8_t *response_builder_buildErr(uint8_t *index, uint8_t code)
{
    snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%c%s%c%u%c%c", KEY.INDEX, COMMAND_PAIR_CONNECTOR, index, COMMAND_PARAM_SEPARATOR, KEY.RESPONSE, COMMAND_PAIR_CONNECTOR, RES.ERROR, COMMAND_PARAM_SEPARATOR, KEY.CODE, COMMAND_PAIR_CONNECTOR, code, COMMAND_PARAM_SEPARATOR, COMMAND_END_TERMINATOR);

    response_builder_formatResponse();

    return response;
}

uint8_t *response_builder_buildFin(uint8_t *index)
{
    snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%c%c", KEY.INDEX, COMMAND_PAIR_CONNECTOR, index, COMMAND_PARAM_SEPARATOR, KEY.RESPONSE, COMMAND_PAIR_CONNECTOR, RES.FINISHED, COMMAND_PARAM_SEPARATOR, COMMAND_END_TERMINATOR);

    response_builder_formatResponse();

    return response;
}

uint8_t *response_builder_buildVal(uint8_t *index, uint8_t *states)
{
    snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%c%s%c%u%u%u%u%u%u%u%u%u%u%u%u%c%c", KEY.INDEX, COMMAND_PAIR_CONNECTOR, index, COMMAND_PARAM_SEPARATOR, KEY.RESPONSE, COMMAND_PAIR_CONNECTOR, RES.VALUE, COMMAND_PARAM_SEPARATOR, KEY.STATE, COMMAND_PAIR_CONNECTOR, states[0], states[1], states[2], states[3], states[4], states[5], states[6], states[7], states[8], states[9], states[10], states[11], COMMAND_PARAM_SEPARATOR, COMMAND_END_TERMINATOR);

    response_builder_formatResponse();

    return response;
}
