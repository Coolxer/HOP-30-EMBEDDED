#ifndef DEVICE_H
#define DEVICE_H

#include "stm32f4xx_hal.h"

enum types {STEPPER = 0, ENDSTOP = 1}; // enum with types of devices serviced in application

typedef struct
{
    int type;                          // enum type define
    uint8_t name[2];                   // 2-character device name (id)

}Device;

#endif // DEVICE_H
