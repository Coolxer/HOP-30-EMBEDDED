#ifndef CMD_HELPER
#define CMD_HELPER

#include "../device/device_manager.h"

enum LVD
{
    LVD_STEPPER = 0,
    LVD_ENDSTOP = 1
};

enum CMD_Type
{
    INSTANT = 0,
    LONG_TERM = 1
};

uint8_t
cmd_getSteppersAmount(uint8_t *value);
uint8_t cmd_getEndstopsAmount(uint8_t *value);

uint8_t cmd_getErrorByKey(uint8_t *key, enum ErrorType et);

#endif // CMD_HELPER