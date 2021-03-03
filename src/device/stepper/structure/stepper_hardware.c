#include "device/stepper/structure/stepper_hardware.h"

Hardware stepper_hardware_init(GPIO_TypeDef *port, TIM_TypeDef *masterTimer, TIM_TypeDef *slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq, uint16_t step, uint16_t dir, uint16_t enable)
{
    Hardware hardware = {0};

    hardware.port = port;

    hardware.masterTimer.Instance = masterTimer;
    hardware.slaveTimer.Instance = slaveTimer;

    hardware.alternateFunction = alternateFunction;
    hardware.channel = channel;
    hardware.itr = itr;
    hardware.irq = irq;

    hardware.step = step;
    hardware.dir = dir;
    hardware.enable = enable;

    return hardware;
}