#include "device/stepper/structure/stepper_info.h"

#include <string.h>

Info stepper_info_init(enum AxisType axisType, uint8_t *name, float minSpeed, float maxSpeed)
{
    Info info = {0};

    info.axisType = axisType;
    info.index = (uint8_t *)"0";
    strcpy((void *)info.name, (void *)name);

    info.minSpeed = minSpeed;
    info.maxSpeed = maxSpeed;

    return info;
}