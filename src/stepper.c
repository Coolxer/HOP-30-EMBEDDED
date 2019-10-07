//#ifdef STSTM32

#include "stepper.h"
#include <string.h>

void stepper_init(struct Stepper *s, uint8_t *_name, TIM_TypeDef *_instance, uint32_t _port, uint16_t _dir_pin, uint16_t _step_pin, uint16_t _enable_pin, uint16_t _m1, uint16_t _m2, uint16_t _m3, uint16_t _endstop_pin)
{
	strcpy(s->name, _name);
	s->timer.Instance = _instance; 
	s->port = _port;

	s->dir_pin = _dir_pin;
	s->step_pin = _step_pin;
	s->enable_pin = _enable_pin;

	s->m_pins[0] = _m1;
	s->m_pins[1] = _m2;
	s->m_pins[2] = _m3;

	if(_endstop_pin != 0) // if theres is 0 as endstop pin that means the stepper has no endstop connected to
		s->endstop_pin = _endstop_pin;

	stepper_setup_gpio(s);
}

void stepper_setup_gpio(struct Stepper *s)
{
	GPIO_InitTypeDef gpio;

	gpio.Pin = s->enable_pin | s->dir_pin | s->step_pin | s->m_pins[0] | s->m_pins[1] | s->m_pins[2] | s->endstop_pin;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(s->port, &gpio);

	HAL_GPIO_WritePin(s->port, s->enable_pin, GPIO_PIN_RESET); // turn OFF stepper motor at start

	HAL_GPIO_WritePin(s->port, s->m_pins[0], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(s->port, s->m_pins[1], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(s->port, s->m_pins[2], GPIO_PIN_RESET);
}

void stepper_setup_timer(struct Stepper *s)
{
	s->timer.Init.CounterMode = TIM_COUNTERMODE_UP;
	
	s->timer.Init.RepetitionCounter = 0;
	//s->timer.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	HAL_TIM_PWM_Init(&s->timer);
}

void stepper_set_speed(struct Stepper *s, uint8_t speed)
{
	s->timer.Init.Period = 1000 - 1;
	s->timer.Init.Prescaler = 8000 - 1;
	s->timer.Init.ClockDivision = 0;
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

bool stepper_move_by_steps(uint8_t steps)
{
	return true;
}

bool stepper_move_until()
{
	return true;
}
        

//#endif // STSTM32