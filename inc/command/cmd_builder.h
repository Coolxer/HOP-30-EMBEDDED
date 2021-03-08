#ifndef CMD_BUILDER_H
#define CMD_BUILDER_H

#include "command/partial/opt.h"
#include "command/partial/key.h"
#include "command/partial/res.h"
#include "command/partial/err.h"
#include "command/partial/val.h"

#include "command/partial/data_assistant.h"

extern uint8_t *ZER0_INDEX;
extern uint8_t *SHUTDOWN_REQUEST;
extern uint8_t *SHUTDOWN_RESPONSE;

void cmd_builder_init();

uint8_t *cmd_builder_buildPas(uint8_t *id);
uint8_t *cmd_builder_buildErr(uint8_t *id, uint8_t code);
uint8_t *cmd_builder_buildFin(uint8_t *id);

#endif // CMD_BUILDER_H