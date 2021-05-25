#ifndef CMD_BUILDER_H
#define CMD_BUILDER_H

#include "command/builder/partial/opt.h"
#include "command/builder/partial/key.h"
#include "command/builder/partial/res.h"
#include "command/builder/partial/err.h"
#include "command/builder/partial/val.h"

#include "command/builder/partial/data_assistant.h"

extern uint8_t *ZER0_INDEX;
extern uint8_t *SHUTDOWN_REQUEST;
extern uint8_t *SHUTDOWN_RESPONSE;

void cmd_builder_init();

uint8_t *cmd_builder_buildPas(uint8_t *id);
uint8_t *cmd_builder_buildErr(uint8_t *id, uint8_t code);
uint8_t *cmd_builder_buildFin(uint8_t *id);
uint8_t *cmd_builder_builRes(uint8_t *id, uint8_t *states);

#endif // CMD_BUILDER_H