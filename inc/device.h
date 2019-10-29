#ifndef DEVICE_H
#define DEVICE_H

#include "stm32f4xx_hal.h"

enum types {STEPPER = 0, ENDSTOP = 1};

typedef struct
{
    int type;
    uint8_t name[2];      // 2-character device name (id)

}Device;

#endif // DEVICE_H
