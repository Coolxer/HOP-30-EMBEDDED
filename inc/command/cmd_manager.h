#ifndef CMD_MANAGER_H
#define CMD_MANAGER_H

#include "stm32f4xx.h"

#include "command/partial/opt.h"
#include "command/partial/key.h"
#include "command/partial/val.h"
#include "command/partial/err.h"
#include "command/partial/res.h"

#define MAX_SINGLE_REQUEST_SIZE 36
#define MAX_BUFFER_REQUESTS 10

extern uint8_t REQUESTS[MAX_BUFFER_REQUESTS + 1][MAX_SINGLE_REQUEST_SIZE];

extern uint8_t registeredRequestsAmount;
extern uint8_t currentProcessingRequestIndex;
extern uint8_t previousRegisteredRequestIndex;

void cmd_manager_init();

void cmd_manager_delive(uint8_t *cmd);
void cmd_manager_manage();

uint8_t cmd_manager_getErrorByKey(uint8_t *key, enum ErrorType errorType);

#endif //CMD_MANAGER_H