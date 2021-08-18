#include "command/response/response_builder.h"

#include <stdio.h>

#include "null.h"
#include "communication/config/communication.h"

uint8_t response[MAX_RESPONSE_SIZE];

uint8_t *response_builder_buildPas(uint8_t *index)
{
    snprintf((void *)response, sizeof(response), "%c%s%c%s%c%s%c%s%c%c%c", COMMAND_BEGIN_TERMINATOR, KEY.INDEX, COMMAND_PAIR_CONNECTOR, index, COMMAND_PARAM_SEPARATOR, KEY.RESPONSE, COMMAND_PAIR_CONNECTOR, RES.PASSED, COMMAND_PARAM_SEPARATOR, SENTENCE_END_TERMINATOR, COMMAND_END_TERMINATOR);

    return response;
}

uint8_t *response_builder_buildErr(uint8_t *index, uint8_t code)
{
    snprintf((void *)response, sizeof(response), "%c%s%c%s%c%s%c%s%c%s%c%u%c%c%c", COMMAND_BEGIN_TERMINATOR, KEY.INDEX, COMMAND_PAIR_CONNECTOR, index, COMMAND_PARAM_SEPARATOR, KEY.RESPONSE, COMMAND_PAIR_CONNECTOR, RES.ERROR, COMMAND_PARAM_SEPARATOR, KEY.CODE, COMMAND_PAIR_CONNECTOR, code, COMMAND_PARAM_SEPARATOR, SENTENCE_END_TERMINATOR, COMMAND_END_TERMINATOR);

    return response;
}

uint8_t *response_builder_buildFin(uint8_t *index)
{
    snprintf((void *)response, sizeof(response), "%c%s%c%s%c%s%c%s%c%c%c", COMMAND_BEGIN_TERMINATOR, KEY.INDEX, COMMAND_PAIR_CONNECTOR, index, COMMAND_PARAM_SEPARATOR, KEY.RESPONSE, COMMAND_PAIR_CONNECTOR, RES.FINISHED, COMMAND_PARAM_SEPARATOR, SENTENCE_END_TERMINATOR, COMMAND_END_TERMINATOR);

    return response;
}

uint8_t *response_builder_buildVal(uint8_t *index, uint8_t *states)
{
    snprintf((void *)response, sizeof(response), "%c%s%c%s%c%s%c%s%c%s%c%u%u%u%u%u%u%u%u%u%u%u%u%c%c%c", COMMAND_BEGIN_TERMINATOR, KEY.INDEX, COMMAND_PAIR_CONNECTOR, index, COMMAND_PARAM_SEPARATOR, KEY.RESPONSE, COMMAND_PAIR_CONNECTOR, RES.VALUE, COMMAND_PARAM_SEPARATOR, KEY.STATE, COMMAND_PAIR_CONNECTOR, states[0], states[1], states[2], states[3], states[4], states[5], states[6], states[7], states[8], states[9], states[10], states[11], COMMAND_PARAM_SEPARATOR, SENTENCE_END_TERMINATOR, COMMAND_END_TERMINATOR);

    return response;
}
