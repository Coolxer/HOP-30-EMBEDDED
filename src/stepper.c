//#ifdef STSTM32

#include <string.h>

#include "stepper.h"

Stepper *stepper_init(uint8_t *_name, TIM_TypeDef *_timer, uint8_t _alternate, uint32_t _channel, uint32_t _port, uint16_t _dir_pin, uint16_t _step_pin, uint16_t _enable_pin, uint16_t _m1, uint16_t _m2, uint16_t _m3)
{
	stepper = (Stepper *)malloc(sizeof(Stepper));

	enum types type = STEPPER;
	stepper->device.type = type;
	strcpy(stepper->device.name, _name);
	
	stepper->timer.Instance = _timer; 
	stepper->alternate = _alternate;
	stepper->channel = _channel;
	stepper->port = _port;

	stepper->dir_pin = _dir_pin;
	stepper->step_pin = _step_pin;
	stepper->enable_pin = _enable_pin;

	stepper->m_pins[0] = _m1;
	stepper->m_pins[1] = _m2;
	stepper->m_pins[2] = _m3;

	stepper->state = 0;

	stepper_setup_gpio();
	stepper_setup_timer();

	return stepper;
}

void stepper_deinit()
{
	if (strcmp((void *)stepper->device.name, "s1") == 0)
		__HAL_RCC_TIM3_CLK_DISABLE();
	else if (strcmp((void *)stepper->device.name, "s2") == 0)
		__HAL_RCC_TIM4_CLK_DISABLE();

	free(stepper);
}

void stepper_setup_gpio()
{
	GPIO_InitTypeDef gpio;

	gpio.Pin = stepper->enable_pin | stepper->dir_pin | stepper->m_pins[0] | stepper->m_pins[1] | stepper->m_pins[2];
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(stepper->port, &gpio);

	gpio.Pin = stepper->step_pin;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_NOPULL;
  	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio.Alternate = stepper->alternate;

	HAL_GPIO_Init(stepper->port, &gpio);

	HAL_GPIO_WritePin(stepper->port, stepper->enable_pin, GPIO_PIN_RESET); // turn OFF stepper motor at start
}

void stepper_setup_timer()
{
	if (strcmp((void *)stepper->device.name, "s1") == 0)
		__HAL_RCC_TIM3_CLK_ENABLE();

	else if (strcmp((void *)stepper->device.name, "s2") == 0)
		__HAL_RCC_TIM4_CLK_ENABLE();

	stepper->timer.Init.CounterMode = TIM_COUNTERMODE_UP;
	stepper->timer.Init.RepetitionCounter = 0;
	stepper->timer.Init.ClockDivision = 0;

	TIM_OC_InitTypeDef oc;
	oc.OCMode = TIM_OCMODE_PWM1;
	oc.Pulse = 100;
	oc.OCPolarity = TIM_OCPOLARITY_HIGH;
	oc.OCNPolarity = TIM_OCNPOLARITY_LOW;
	oc.OCFastMode = TIM_OCFAST_ENABLE;
	oc.OCIdleState = TIM_OCIDLESTATE_SET;
	oc.OCNIdleState = TIM_OCNIDLESTATE_RESET;

	HAL_TIM_PWM_ConfigChannel(&stepper->timer, &oc, stepper->channel);	
}

void stepper_set_speed(uint8_t speed)
{
	// in 16-bit timer max Period value can reach 65535 if there is need to be LONGER period between steps
	// you need to use Prescaler
	stepper->timer.Init.Period = 1000 - 1;
	stepper->timer.Init.Prescaler = 8000 - 1;
	HAL_TIM_PWM_Init(&stepper->timer);
}

bool stepper_toggle()
{
	GPIO_PinState state = HAL_GPIO_ReadPin(stepper->port, stepper->enable_pin);
	
	HAL_GPIO_TogglePin(stepper->port, stepper->enable_pin);

	if(state != HAL_GPIO_ReadPin(stepper->port, stepper->enable_pin))
		return true;
	
	return false; // something goes wrong and the pin state does not changed
}

bool stepper_set_microstepping(uint8_t *states)
{
	uint8_t i;
	GPIO_PinState state;

	for(i = 0; i < 3; i++)
	{
		state = (strcmp(states[i], '0') == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET;

		if(state == HAL_GPIO_ReadPin(stepper->port, stepper->m_pins[i])) // check if the msp pin actually have required state -> next
			continue; 

		HAL_GPIO_WritePin(stepper->port, stepper->m_pins[i], state);

		if(state != HAL_GPIO_ReadPin(stepper->port, stepper->m_pins[i]))
			return false; // something goes wrong
	}

	return true;
}

bool stepper_move(uint8_t steps)
{	
	HAL_TIM_PWM_Start(&stepper->timer, stepper->channel);
	return true;
}

bool stepper_home()
{
	HAL_TIM_PWM_Start(&stepper->timer, stepper->channel);
	return true;
}


//#endif // STSTM32