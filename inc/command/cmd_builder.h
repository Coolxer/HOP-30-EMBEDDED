#ifndef CMD_BUILDER_H
#define CMD_BUILDER_H

#include "command/partial/opt.h"
#include "command/partial/key.h"
#include "command/partial/res.h"
#include "command/partial/err.h"

#include "stepper/stepper.h"

void cmd_builder_init();

// id, type(pas)
// id, type(err), cod
// id, type(fin),

uint8_t *cmd_builder_buildPas(uint8_t *id);
uint8_t *cmd_builder_buildErr(uint8_t *id, uint8_t code);
uint8_t *cmd_builder_buildFin(uint8_t *id);

// use as a shortcut of build pas / fin command, if there is no knowledge about ERR
// if pas == 1 , that mean its pass cmd, otherwise it's fin
// stepper is using only in pas cmd feedback, so can be NULL in other cases
uint8_t *cmd_builder_buildPasFinErr(uint8_t *id, uint8_t pas, uint8_t code, Stepper *stepper);

#endif // CMD_BUILDER_H