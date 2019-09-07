//#ifdef STSTM32

#include "stepper.h"
#include <string.h>
#include "stm32f4xx_hal.h"

void stepper_init(struct Stepper *s, uint8_t *_name, uint32_t _port, uint16_t _enable_pin, uint16_t _dir_pin, uint16_t _step_pin, uint16_t _m1, uint16_t _m2, uint16_t _m3, uint16_t _endstop_pin)
{
	strcpy(s->name, _name);
	s->port = _port;
	s->enable_pin = _enable_pin;
	s->dir_pin = _dir_pin;
	s->step_pin = _step_pin;
	s->m_pins[0] = _m1;
	s->m_pins[1] = _m2;
	s->m_pins[2] = _m3;
	s->endstop_pin = _endstop_pin;

	stepper_setup_gpio(s);
}

void stepper_setup_gpio(struct Stepper *s)
{
	__HAL_RCC_GPIOC_CLK_ENABLE(); // should be intialized in higher level (depend on using gpio pins)

	GPIO_InitTypeDef gpio;

	gpio.Pin = s->enable_pin | s->dir_pin | s->step_pin | s->m_pins[0] | s->m_pins[1] | s->m_pins[2] | s->endstop_pin;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(s->port, &gpio);

	HAL_GPIO_WritePin(s->port, s->enable_pin, GPIO_PIN_RESET); // turn OFF stepper motor at start

	HAL_GPIO_WritePin(s->port, s->m_pins[0], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(s->port, s->m_pins[1], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(s->port, s->m_pins[2], GPIO_PIN_RESET);
}

bool stepper_toggle(struct Stepper *s)
{
	GPIO_PinState state = HAL_GPIO_ReadPin(s->port, s->enable_pin);
	
	HAL_GPIO_TogglePin(s->port, s->enable_pin);

	if(state != HAL_GPIO_ReadPin(s->port, s->enable_pin))
		return true;
	
	return false; // something goes wrong and the pin state does not changed
}

bool stepper_set_microstepping(struct Stepper *s, uint8_t *states)
{
	uint8_t i;
	GPIO_PinState state;

	for(i = 0; i < 3; i++)
	{
		state = (strcmp(states[i], '0') == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET;

		if(state == HAL_GPIO_ReadPin(s->port, s->m_pins[i])) // check if the msp pin actually have required state -> next
			continue; 

		HAL_GPIO_WritePin(s->port, s->m_pins[i], state);

		if(state != HAL_GPIO_ReadPin(s->port, s->m_pins[i]))
			return false; // something goes wrong
	}

	return true;
}
        

//#endif // STSTM32