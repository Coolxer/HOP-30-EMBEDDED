#ifdef STSTM32

#include "stepper.h"
#include <string.h>
#include "stm32f4xx_hal.h"

void stepper_init(struct Stepper *s, uint8_t *_name, uint16_t _enable_pin, uint16_t _dir_pin, uint16_t _step_pin, uint16_t _m1, uint16_t _m2, uint16_t _m3, uint16_t _endstop_pin)
{
	strcpy(s->name, _name);
	s->enable_pin = _enable_pin;
	s->dir_pin = _dir_pin;
	s->step_pin = _step_pin;
	s->m1 = _m1;
	s->m2 = _m2;
	s->m3 = _m3;
	s->endstop_pin = _endstop_pin;

	stepper_setup_gpio(s);
}

void stepper_setup_gpio(struct Stepper *s)
{
	GPIO_InitTypeDef gpio;

	gpio.Pin = s->enable_pin;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOA, &gpio);

	HAL_GPIO_WritePin(GPIOA, s->enable_pin, GPIO_PIN_RESET); // turn OFF stepper motor
}

void stepper_enable(struct Stepper *s, bool state)
{
    if(state)
	    HAL_GPIO_WritePin(GPIOA, s->enable_pin, GPIO_PIN_SET); // turn ON stepper motor
    else
        HAL_GPIO_WritePin(GPIOA, s->enable_pin, GPIO_PIN_RESET); // turn OFF stepper motor
}

#endif // STSTM32