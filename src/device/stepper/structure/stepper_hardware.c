#include "device/stepper/structure/stepper_hardware.h"

Hardware stepper_hardware_init(TIM_TypeDef *masterTimer, TIM_TypeDef *slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq,
                               GPIO_TypeDef *enablePort, uint16_t enablePin, GPIO_TypeDef *stepPort, uint16_t stepPin, GPIO_TypeDef *dirPort, uint16_t dirPin)
{
    Hardware hardware = {0};

    hardware.masterTimer.Instance = masterTimer;
    hardware.slaveTimer.Instance = slaveTimer;

    hardware.alternateFunction = alternateFunction;
    hardware.channel = channel;
    hardware.itr = itr;
    hardware.irq = irq;

    hardware.enablePort = enablePort;
    hardware.enablePin = enablePin;

    hardware.stepPort = stepPort;
    hardware.stepPin = stepPin;

    hardware.dirPort = dirPort;
    hardware.dirPin = dirPin;

    return hardware;
}