#ifndef RESPONSE_BUILDER_H
#define RESPONSE_BUILDER_H

#include "command/partial/opt.h"
#include "command/partial/key.h"
#include "command/partial/err.h"
#include "command/partial/res.h"
#include "command/partial/val.h"

void response_builder_formatResponse();

uint8_t *response_builder_buildPas(uint8_t *index);
uint8_t *response_builder_buildErr(uint8_t *index, uint8_t code);
uint8_t *response_builder_buildFin(uint8_t *index);

#endif // RESPONSE_BUILDER_H