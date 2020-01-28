//#ifdef STSTM32

#include <string.h>

#include "stepper.h"

Stepper *stepper_init(uint8_t *_name, TIM_TypeDef *_timer, uint8_t _alternate, uint32_t _channel, uint32_t _port, uint16_t _dir_pin, uint16_t _step_pin, uint16_t _enable_pin, uint16_t _m1, uint16_t _m2, uint16_t _m3)
{
	// TODO (set stepper to NULL at start)
	//if(stepper == NULL)
		stepper = (Stepper *)malloc(sizeof(Stepper)); // reserves memory for operting stepper

	enum types type = STEPPER; // creates ENDSTOP type
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

	stepper->state = GPIO_PIN_RESET;

	stepper_setup_gpio(); // setups stepper gpio
	stepper_setup_timer(); // setups stepper timer
	
	stepper_set_speed(200); // setups stepper speed

	return stepper;
}

void stepper_deinit()
{
	/* turns off property TIMER depend on current device name */

	if (stepper->timer.Instance == TIM3) 
		__HAL_RCC_TIM3_CLK_DISABLE();
	else if (stepper->timer.Instance == TIM4)
		__HAL_RCC_TIM4_CLK_DISABLE();

	free(stepper); 
}

void stepper_setup_gpio()
{
	GPIO_InitTypeDef gpio;

	/* setups gpio for all stepper pins except step_pin */

	gpio.Pin = stepper->enable_pin | stepper->dir_pin | stepper->m_pins[0] | stepper->m_pins[1] | stepper->m_pins[2];
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(stepper->port, &gpio);

	/* setups gpio for step_pin */

	gpio.Pin = stepper->step_pin;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_NOPULL;
  	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio.Alternate = stepper->alternate;

	HAL_GPIO_Init(stepper->port, &gpio);

	HAL_GPIO_WritePin(stepper->port, stepper->enable_pin, GPIO_PIN_RESET); // turns OFF stepper motor at start
}

void stepper_setup_timer()
{
	/* turns on property TIMER depend on current device name */

	if (stepper->timer.Instance == TIM3)
		__HAL_RCC_TIM3_CLK_ENABLE();

	else if (stepper->timer.Instance == TIM4)
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

	// TODO -> speed should be only positive value

	/*
	if(speed == 0) // checks if speed is 0 -> EROR
		return;
	else if(speed < 0) // checks if speed is less than 0 or its more than 0 and set correctly dir_pin to it
		HAL_GPIO_WritePin(stepper->port, stepper->dir_pin, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(stepper->port, stepper->dir_pin, GPIO_PIN_SET);
	*/

	/* speed set */

	stepper->timer.Init.Period = 1000 - 1;
	stepper->timer.Init.Prescaler = 8000 - 1;
	
	HAL_TIM_PWM_Init(&stepper->timer);
}

bool stepper_switch(uint8_t *state)
{
	if(strcmp(state, "off") == 0)
		stepper->state = GPIO_PIN_RESET;
	else if (strcmp(state, "on") == 0)
		stepper->state = GPIO_PIN_SET;
	else
		return false;
	
	HAL_GPIO_WritePin(stepper->port, stepper->enable_pin, stepper->state); // switches the stepper (OFF or ON)

	return true;
}

bool stepper_set_microstepping(uint8_t *states)
{
	uint8_t i;
	GPIO_PinState state;

	for(i = 0; i < 3; i++)
	{
		if((strcmp(states[i], '0') != 0) && (strcmp(states[i], '1') != '1'))
			return false;

		state = (strcmp(states[i], '0') == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET;

		HAL_GPIO_WritePin(stepper->port, stepper->m_pins[i], state); // sets required state of concret microstep pin 
	}

	return true;
}

void stepper_move(uint8_t steps)
{	
	HAL_TIM_PWM_Start(&stepper->timer, stepper->channel); // starts moving
	return true;
}

void stepper_home()
{
	stepper_switch("on");

	HAL_GPIO_WritePin(stepper->port, stepper->dir_pin, GPIO_PIN_SET); //set left direction;
	HAL_TIM_PWM_Start(&stepper->timer, stepper->channel); // starts moving
}


//#endif // STSTM32