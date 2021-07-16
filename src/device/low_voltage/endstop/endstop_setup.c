#include "device/low_voltage/endstop/partial/endstop_setup.h"

#include <string.h>

void endstop_init(Endstop *endstop, uint8_t *name, GPIO_TypeDef *port, uint16_t pin, uint8_t irq)
{
    strcpy((void *)endstop->name, (void *)name);

    endstop->hardware = endstop_hardware_init(port, pin, irq);
    endstop->debounce = endstop_debounce_init();
}

void endstop_deinit(Endstop *endstop)
{
    HAL_GPIO_DeInit(endstop->hardware.port, endstop->hardware.pin);
    HAL_NVIC_DisableIRQ(endstop->hardware.irq);
}
