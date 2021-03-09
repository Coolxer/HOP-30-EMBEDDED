#include "device/stepper/partial/stepper_setup.h"

#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_configuration.h"

void stepper_init(Stepper *stepper, enum AxisType axisType, uint8_t *name, GPIO_TypeDef *port, TIM_TypeDef *masterTimer, TIM_TypeDef *slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq, uint16_t step, uint16_t dir, uint16_t enable,
                  float minSpeed, float maxSpeed, float homeFastBackwardSpeed, float homeSlowForwardSpeed, float homePreciseBackwardSpeed)
{
    stepper->hardware = stepper_hardware_init(port, masterTimer, slaveTimer, alternateFunction, channel, itr, irq, step, dir, enable);
    stepper->info = stepper_info_init(axisType, name);
    stepper->instance = stepper_instance_init();
    stepper->speed = stepper_speed_init(minSpeed, maxSpeed, homeFastBackwardSpeed, homeSlowForwardSpeed, homePreciseBackwardSpeed);

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