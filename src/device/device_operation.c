#include "device/device_operation.h"

void intervene_process(void (*intervention)(Stepper *))
{
    intervention(X_STEPPER);
    intervention(W_STEPPER);
}

void intervene_all(void (*intervention)(Stepper *))
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++)
        intervention(&steppers[i]);
}
