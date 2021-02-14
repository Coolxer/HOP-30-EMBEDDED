#ifndef CMD_BUILDER_H
#define CMD_BUILDER_H

#include "command/partial/opt.h"
#include "command/partial/key.h"
#include "command/partial/res.h"

void cmd_builder_init();

// id, type(pas)
// id, type(err), cod
// id, type(fin), (value <- only for get_endstop_state)

uint8_t *cmd_builder_buildPas(uint8_t *id);
uint8_t *cmd_builder_buildErr(uint8_t *id, uint8_t *code);
uint8_t *cmd_builder_buildFin(uint8_t *id, uint8_t *value);

#endif // CMD_BUILDER_H