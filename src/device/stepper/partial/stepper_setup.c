#include "device/stepper/partial/stepper_setup.h"

#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_configuration.h"

void stepper_init(Stepper *stepper, enum AxisType axisType, uint8_t *name, Hardware hardware, Speed speed, Acceleration acceleration)
{
    stepper->info = stepper_info_init(axisType, name);
    stepper->instance = stepper_instance_init();

    stepper->hardware = hardware;
    stepper->speed = speed;
    stepper->acceleration = acceleration;
    stepper->movement = stepper_movement_init();

    stepper_setPeripherals(stepper);
}

void stepper_assignEndstops(Stepper *stepper, Endstop *min, Endstop *max)
{
    stepper->minEndstop = min;
    stepper->maxEndstop = max;
}

void stepper_deinit(Stepper *stepper)
{
    HAL_TIM_PWM_Stop(&stepper->hardware.masterTimer, stepper->hardware.channel);
    HAL_TIM_Base_Stop_IT(&stepper->hardware.slaveTimer);
    HAL_NVIC_DisableIRQ(stepper->hardware.irq);
}