#include "device/high_voltage/pomp/partial/pomp_operation.h"

void pomp_switch(HVDevice *pomp, uint8_t *state, uint8_t *EMPTY1)
{
    high_voltage_device_switch(pomp, state);
}