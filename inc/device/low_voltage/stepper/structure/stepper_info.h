#ifndef STEPPER_INFO_H
#define STEPPER_INFO_H

#include <stdint.h>
#include "device/low_voltage/stepper/enum/state.h"
#include "device/low_voltage/stepper/enum/axis_type.h"

typedef struct
{
    enum AxisType axisType; // axis type [LINEAR or CIRCULAR]
    uint8_t name;           // name
    uint8_t *index;         // command index

    enum State state;          // state of stepper
    uint8_t invertedDirection; // is direction inverted?
} Info;

Info stepper_info_init(enum AxisType axisType, uint8_t name, uint8_t invertedDirection);

#endif // STEPPER_INFO_H