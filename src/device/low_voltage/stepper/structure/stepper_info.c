#include "device/low_voltage/stepper/structure/stepper_info.h"

#include "device/low_voltage/stepper/enum/state.h"

Info stepper_info_init(enum AxisType axisType, uint8_t name, uint8_t invertedDirection)
{
    Info info = {0};

    info.axisType = axisType;
    info.index = (uint8_t *)"0";
    info.name = name;

    info.state = LOW;
    info.invertedDirection = invertedDirection;

    return info;
}