#include "command/response/response_builder.h"

#include <stdio.h>

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
        response[i] = '|';

    response[RESPONSE_SIZE - 1] = '\0';
}

uint8_t *response_builder_buildPas(uint8_t *index)
{

    snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%c%c", KEY.INDEX, '=', index, '|', KEY.RESPONSE, '=', RES.PASSED, '|', COMMAND_END_TERMINATOR);

    response_builder_formatResponse();

    return response;
}

uint8_t *response_builder_buildErr(uint8_t *index, uint8_t code)
{
    snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%c%s%c%u%c%c", KEY.INDEX, '=', index, '|', KEY.RESPONSE, '=', RES.ERROR, '|', KEY.CODE, '=', code, '|', COMMAND_END_TERMINATOR);

    response_builder_formatResponse();

    return response;
}

uint8_t *response_builder_buildFin(uint8_t *index)
{
    snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%c%c", KEY.INDEX, '=', index, '|', KEY.RESPONSE, '=', RES.FINISHED, '|', COMMAND_END_TERMINATOR);

    response_builder_formatResponse();

    return response;
}

uint8_t *response_builder_buildVal(uint8_t *index, uint8_t *states)
{
    snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%c%s%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", KEY.INDEX, '=', index, '|', KEY.RESPONSE, '=', RES.VALUE, '|', KEY.STATE, '=', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '0', '0', '|', COMMAND_END_TERMINATOR);
    //snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%c%s%c%c%c%c%c%c%c%c%c%c%c%c%c%s", KEY.INDEX, '=', index, '|', KEY.RESPONSE, '=', RES.VALUE, '|', KEY.STATE, '=', states[0], states[1], states[2], states[3], states[4], states[5], states[6], states[7], states[8], states[9], states[10], states[11], "|\n");
    //snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%c%s%c%s%s", KEY.INDEX, '=', index, '|', KEY.RESPONSE, '=', RES.VALUE, '|', KEY.STATE, '=', states, "|\n");
    //snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%c%s%c%c%c%c%c%c%c%c%c%c%c%c%c%s", KEY.INDEX, '=', index, '|', KEY.RESPONSE, '=', RES.VALUE, '|', KEY.STATE, '=', data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], "|\n");

    //response_builder_formatResponse();

    return response;
}
