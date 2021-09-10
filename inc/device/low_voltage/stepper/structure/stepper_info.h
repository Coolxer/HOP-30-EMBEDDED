#ifndef STEPPER_INFO_H
#define STEPPER_INFO_H

#include <stdint.h>
#include "device/low_voltage/stepper/enum/state.h"

typedef struct
{
    uint8_t name;   // name
    uint8_t *index; // command index

    enum State state;          // state of stepper
    uint8_t invertedDirection; // is direction inverted?
} Info;

Info stepper_info_init(uint8_t name, uint8_t invertedDirection);

#endif // STEPPER_INFO_H