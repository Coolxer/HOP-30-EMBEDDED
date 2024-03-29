#include "device/low_voltage/stepper/structure/stepper_info.h"

#include "device/low_voltage/stepper/enum/state.h"

Info stepper_info_init(uint8_t name)
{
    Info info = {0};

    info.index = (uint8_t *)"0";
    info.name = name;

    info.state = LOW;
    return info;
}