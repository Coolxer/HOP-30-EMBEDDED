#ifndef CMD_MANAGER_H
#define CMD_MANAGER_H

#include "stm32f4xx.h"

#include "command/partial/opt.h"
#include "command/partial/key.h"
#include "command/partial/val.h"
#include "command/partial/err.h"
#include "command/partial/res.h"

void cmd_manager_init();

uint8_t cmd_manager_getErrorByKey(uint8_t *key, enum ErrorType errorType);

#endif //CMD_MANAGER_H