#include "stepper.h"

#include "stm32f4xx_hal.h"

void stepper_init(struct Stepper *s, uint8_t *name, uint8_t enable_pin, uint8_t dir_pin, uint8_t step_pin, uint8_t m1, uint8_t m2, uint8_t m3, uint8_t endstop_pin)
{
	s->_name = name;
	s->_enable_pin = enable_pin;
	s->_dir_pin = dir_pin;
	s->_step_pin = step_pin;
	s->_m1 = m1;
	s->_m2 = m2;
	s->_m3 = m3;
	s->_endstop_pin = endstop_pin;

	stepper_setup_gpio(s);
}

void stepper_setup_gpio(struct Stepper *s)
{
	GPIO_InitTypeDef gpio;

	gpio.Pin = s->_enable_pin;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOA, &gpio);

	HAL_GPIO_WritePin(GPIOA, s->_enable_pin, GPIO_PIN_RESET); // turns OFF stepper motor
}

void stepper_enable(struct Stepper *s, bool state)
{
    if(state)
	    HAL_GPIO_WritePin(GPIOA, s->_enable_pin, GPIO_PIN_SET); // turns ON stepper motor
    else
        HAL_GPIO_WritePin(GPIOA, s->_enable_pin, GPIO_PIN_RESET); // turns OFF stepper motor
}