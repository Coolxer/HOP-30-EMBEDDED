#ifndef STEPPER_INFO_H
#define STEPPER_INFO_H

#include <stdint.h>
#include "device/low_voltage/stepper/enum/axis_type.h"

#define STEPPER_NAME_LENGTH 2

typedef struct
{
    enum AxisType axisType;            // axis type [LINEAR or CIRCULAR]
    uint8_t name[STEPPER_NAME_LENGTH]; // name
    uint8_t *index;                    // command index
} Info;

Info stepper_info_init(enum AxisType axisType, uint8_t *name);

#endif // STEPPER_INFO_H