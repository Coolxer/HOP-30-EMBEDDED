#ifndef STEPPER_INFO_H
#define STEPPER_INFO_H

#include <stdint.h>
#include "device/stepper/enum/axis_type.h"

typedef struct
{
    enum AxisType axisType; // axis type [LINEAR or CIRCULAR]
    uint8_t name[2];        // 2-characters name
    uint8_t *index;         // command index

    float minSpeed; // minimum speed of stepper (individually for each axis)
    float maxSpeed; // maximimum speed of stepper (individually for each axis)
} Info;

Info stepper_info_init(enum AxisType axisType, uint8_t *name, float minSpeed, float maxSpeed);

#endif // STEPPER_INFO_H