#ifndef STEPPER_INFO_H
#define STEPPER_INFO_H

#include <stdint.h>

#include "device/stepper/enum/axis_type.h"

typedef struct
{
    enum AxisType axisType; // axis type [LINEAR or CIRCULAR]
    uint8_t name[2];        // 2-characters name
    uint8_t *index;         // command index
} Info;

Info stepper_info_init(enum AxisType axisType, uint8_t *name);

#endif // STEPPER_INFO_H