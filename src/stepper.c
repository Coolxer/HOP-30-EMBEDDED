//#ifdef STSTM32

#include <string.h>

#include "stepper.h"

Stepper *stepper_init(uint8_t* _name, TIM_TypeDef *_master_timer, uint32_t _channel, TIM_TypeDef *_slave_timer, uint32_t _itr, uint8_t _irq, uint8_t _alternate, uint32_t _port, uint16_t _dir_pin, uint16_t _step_pin, uint16_t _enable_pin, uint16_t _m1, uint16_t _m2, uint16_t _m3)
{
	Stepper stepper;

	strcpy(stepper.name, _name);

	stepper.master_timer.Instance = _master_timer;
	stepper.channel = _channel; // PWM channel of master timer

	stepper.slave_timer.Instance = _slave_timer; 
	stepper.itr = _itr;
	stepper.irq = _irq;

	stepper.alternate = _alternate;
	
	stepper.port = _port;

	stepper.dir_pin = _dir_pin;
	stepper.step_pin = _step_pin;
	stepper.enable_pin = _enable_pin;

	stepper.m_pins[0] = _m1;
	stepper.m_pins[1] = _m2;
	stepper.m_pins[2] = _m3;

	stepper.state = GPIO_PIN_RESET;

	stepper_setup_gpio(&stepper); // setups stepper gpio
	stepper_setup_timers(&stepper); // setups stepper timer
	
	stepper_set_speed(&stepper, 200); // setups stepper speed

	return &stepper;
}

void stepper_deinit(Stepper* stepper)
{
	HAL_TIM_PWM_Stop(&stepper->master_timer, stepper->channel);
	HAL_TIM_Base_Stop_IT(&stepper->slave_timer);
	HAL_NVIC_DisableIRQ(stepper->irq);
}

void stepper_setup_gpio(Stepper* stepper)
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

void stepper_setup_master_timer(Stepper* stepper)
{
	TIM_ClockConfigTypeDef clockSourceConfig = {0};
  	TIM_MasterConfigTypeDef masterConfig = {0};
  	TIM_OC_InitTypeDef configOC = {0};
	
	stepper->master_timer.Init.CounterMode = TIM_COUNTERMODE_UP;
	stepper->master_timer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	//stepper->master_timer.Init.AutoReloadPreload = 0x00000000U;
	HAL_TIM_Base_Init(&stepper->master_timer);

	//clockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	//HAL_TIM_ConfigClockSource(&stepper->master_timer, &clockSourceConfig);

	HAL_TIM_PWM_Init(&stepper->master_timer);

	masterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&stepper->master_timer, &masterConfig);

	configOC.OCMode = TIM_OCMODE_PWM1;
	configOC.Pulse = 1000;
	configOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  	configOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&stepper->master_timer, &configOC, TIM_CHANNEL_1);
}

void stepper_setup_slave_timer(Stepper* stepper)
{
	TIM_SlaveConfigTypeDef slaveConfig = {0};
  	TIM_MasterConfigTypeDef masterConfig = {0};

  	stepper->slave_timer.Init.Prescaler = 0;
  	stepper->slave_timer.Init.CounterMode = TIM_COUNTERMODE_UP;
  	stepper->slave_timer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  	//stepper->slave_timer.Init.AutoReloadPreload = 0x00000000U;

  	HAL_TIM_Base_Init(&stepper->slave_timer);

	__HAL_TIM_CLEAR_FLAG(&stepper->slave_timer, TIM_SR_UIF); // clear interrupt flag

	slaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
  	slaveConfig.InputTrigger = stepper->itr;
  	HAL_TIM_SlaveConfigSynchronization(&stepper->slave_timer, &slaveConfig);

  	masterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  	masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  	HAL_TIMEx_MasterConfigSynchronization(&stepper->slave_timer, &masterConfig);

	HAL_NVIC_SetPriority(stepper->irq, 0, 0);
	HAL_NVIC_EnableIRQ(stepper->irq);
}

void stepper_setup_timers(Stepper* stepper)
{
	stepper_setup_master_timer(stepper);
	stepper_setup_slave_timer(stepper);
}

void stepper_set_speed(Stepper* stepper, uint8_t speed)
{
	// in 16-bit timer max Period value can reach 65535 if there is need to be LONGER period between steps
	// you need to use Prescaler

	// normally greater speed means faster, but there is otherwise, beacuse "speed" meaning is period of time
	// so we need to cast this, but not this moment, because it's need to set up clocks frequency
	// and see in real time, what speed we need

	if(speed == 0) // checks if speed is 0 -> ERROR
		return;

	/* speed set */

	stepper->master_timer.Init.Period = speed - 1;
	//stepper->timer.Init.Prescaler = 8000 - 1;
	
	//HAL_TIM_PWM_Init(&stepper->master_timer); <- do i need to call it again to assign new speed ? ???????
}

uint8_t stepper_switch(Stepper* stepper, uint8_t *state)
{
	if(strcmp(state, "off") == 0)
		stepper->state = GPIO_PIN_RESET;
	else if (strcmp(state, "on") == 0)
		stepper->state = GPIO_PIN_SET;
	else
		return 0;
	
	HAL_GPIO_WritePin(stepper->port, stepper->enable_pin, stepper->state); // switches the stepper (OFF or ON)

	return 1;
}

uint8_t stepper_set_microstepping(Stepper* stepper, uint8_t *states)
{
	uint8_t i;
	GPIO_PinState state;

	for(i = 0; i < 3; i++)
	{
		if((strcmp(states[i], '0') != 0) && (strcmp(states[i], '1') != 0))
			return 0;

		state = (strcmp(states[i], '0') == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET;

		HAL_GPIO_WritePin(stepper->port, stepper->m_pins[i], state); // sets required state of concret microstep pin 
	}

	return 1;
}

void stepper_move(Stepper* stepper, uint8_t steps)
{	
	HAL_TIM_Base_Start_IT(&stepper->slave_timer);
	HAL_TIM_PWM_Start(&stepper->master_timer, stepper->channel); // starts moving
}

void stepper_home(Stepper* stepper)
{
	stepper_switch("on");

	HAL_GPIO_WritePin(stepper->port, stepper->dir_pin, GPIO_PIN_SET); //set left direction;
	
	HAL_TIM_PWM_Start(&stepper->master_timer, stepper->channel); // starts moving
}


//#endif // STSTM32