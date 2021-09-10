#include "device/low_voltage/stepper/partial/stepper_setup.h"
#include "device/low_voltage/stepper/partial/stepper_peripheral.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"

void stepper_init(Stepper *stepper, uint8_t name, float stepsPerUnit, uint8_t invertedDirection, TIM_TypeDef *masterTimer, TIM_TypeDef *slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq,
                  GPIO_TypeDef *enablePort, uint16_t enablePin, GPIO_TypeDef *stepPort, uint16_t stepPin, GPIO_TypeDef *dirPort, uint16_t dirPin)
{
    stepper->info = stepper_info_init(name, invertedDirection);

    stepper->hardware = stepper_hardware_init(masterTimer, slaveTimer, alternateFunction, channel, itr, irq, enablePort, enablePin, stepPort, stepPin, dirPort, dirPin);
    stepper->speed = stepper_speed_init();
    stepper->acceleration = stepper_acceleration_init();
    stepper->movement = stepper_movement_init(stepsPerUnit);

    stepper_setPeripherals(stepper);
}

void stepper_assignEndstops(Stepper *stepper, Endstop *min, Endstop *max)
{
    stepper->minEndstop = min;
    stepper->maxEndstop = max;
}

void stepper_deinit(Stepper *stepper)
{
    stepper_resetPeriherals(stepper);
}