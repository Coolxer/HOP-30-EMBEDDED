#include "device/high_voltage/pomp/partial/pomp_setup.h"

void pomp_init(HVDevice *pomp, GPIO_TypeDef *port, uint16_t pin)
{
    high_voltage_device_init(pomp, port, pin);
}