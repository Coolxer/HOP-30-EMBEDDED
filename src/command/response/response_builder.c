#include "command/response/response_builder.h"

#include <stdio.h>

#include "communication/config/communication.h"

uint8_t response[RESPONSE_SIZE];

void response_builder_formatResponse()
{
    uint8_t n = 0;

    while (response[n] != '\n')
        n++;

    uint8_t i = (uint8_t)(n + 1);

    for (; i < RESPONSE_SIZE; i++)
        response[i] = '|';

    response[RESPONSE_SIZE - 1] = '\0';
}

uint8_t *response_builder_buildPas(uint8_t *id)
{
    snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%s", KEY.INDEX, '=', id, '|', KEY.RESPONSE, '=', RES.PASSED, "|\n");

    response_builder_formatResponse();

    return response;
}

uint8_t *response_builder_buildErr(uint8_t *id, uint8_t code)
{
    snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%c%s%c%u%s", KEY.INDEX, '=', id, '|', KEY.RESPONSE, '=', RES.ERROR, '|', KEY.CODE, '=', code, "|\n");

    response_builder_formatResponse();

    return response;
}

uint8_t *response_builder_buildFin(uint8_t *id)
{
    snprintf((void *)response, sizeof(response), "%s%c%s%c%s%c%s%s", KEY.INDEX, '=', id, '|', KEY.RESPONSE, '=', RES.FINISHED, "|\n");

    response_builder_formatResponse();

    return response;
}