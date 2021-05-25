
#ifndef CMD_EXECUTOR
#define CMD_EXECUTOR

#include "../device/device_manager.h"

uint8_t *cmd_stepperAction(uint8_t *idx, uint8_t ***args, uint8_t **requiredKeys, uint8_t requiredKeysAmount, uint8_t (*validate)(Stepper *, uint8_t *, uint8_t *), void (*operate)(Stepper *, uint8_t *, uint8_t *), enum CMD_Type cmdType);
uint8_t *cmd_hvdAction(uint8_t *idx, uint8_t ***args, HVD *hvd);

uint8_t *cmd_proccessAction(uint8_t *idx, uint8_t **args);

uint8_t *cmd_getLVDState(uint8_t *idx, uint8_t ***args, enum LVD lvd);
uint8_t *cmd_getHVDState(uint8_t *idx, uint8_t ***args, HVD *hvd);

#endif // CMD_EXECUTOR