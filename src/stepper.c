//#ifdef STSTM32

#include "stepper.h"

#include <string.h>
#include <stdlib.h>

Stepper* stepper_init(Stepper *stepper, uint8_t *name, uint32_t port, TIM_TypeDef *masterTimer, TIM_TypeDef *slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq, uint16_t step, uint16_t dir, uint16_t enable, uint16_t m1, uint16_t m2, uint16_t m3)
{
	strcpy(stepper->name, name);

	stepper->port = port;

	stepper->masterTimer.Instance = masterTimer;
	stepper->slaveTimer.Instance = slaveTimer;

	stepper->alternateFunction = alternateFunction;
	stepper->channel = channel;
	stepper->itr = itr;
	stepper->irq = irq;

	stepper->step = step;
	stepper->dir = dir;
	stepper->enable = enable;
	
	stepper->m[0] = m1;
	stepper->m[1] = m2;
	stepper->m[2] = m3;

	stepper_setupGpio(stepper); 
	stepper_setupTimers(stepper);

	return &stepper;
}

void stepper_deinit(Stepper *stepper)
{
	HAL_TIM_PWM_Stop(&stepper->masterTimer, stepper->channel);
	HAL_TIM_Base_Stop_IT(&stepper->slaveTimer);
	HAL_NVIC_DisableIRQ(stepper->irq);
}

void stepper_setupGpio(Stepper *stepper)
{
	GPIO_InitTypeDef gpio;

	/* setups gpio for all stepper pins except step_pin */

	gpio.Pin = stepper->dir | stepper->enable | stepper->m[0] | stepper->m[1] | stepper->m[2];
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(stepper->port, &gpio);

	/* setups gpio for step_pin */
	gpio.Pin = stepper->step;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_NOPULL;
  	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio.Alternate = stepper->alternateFunction;

	HAL_GPIO_Init(stepper->port, &gpio);

	//HAL_GPIO_WritePin(stepper->port, stepper->enable, GPIO_PIN_RESET); // turns OFF stepper motor at start

	stepper_switch(stepper, "0");
}

void stepper_setupMasterTimer(Stepper *stepper)
{
	TIM_ClockConfigTypeDef clockSourceConfig = {0};
  	TIM_MasterConfigTypeDef masterConfig = {0};
  	TIM_OC_InitTypeDef configOC = {0};
	
	stepper->masterTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
	stepper->masterTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	stepper->masterTimer.Init.Prescaler = 4000 - 1;
	stepper->masterTimer.Init.Period = 5000 - 1;
	HAL_TIM_Base_Init(&stepper->masterTimer);

	//clockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	//HAL_TIM_ConfigClockSource(&stepper->master_timer, &clockSourceConfig);

	masterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&stepper->masterTimer, &masterConfig);

	configOC.OCMode = TIM_OCMODE_PWM1;
	configOC.Pulse = 1000;
	configOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  	configOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&stepper->masterTimer, &configOC, stepper->channel);
}

void stepper_setupSlaveTimer(Stepper *stepper)
{
	TIM_SlaveConfigTypeDef slaveConfig = {0};
  	TIM_MasterConfigTypeDef masterConfig = {0};

  	stepper->slaveTimer.Init.Prescaler = 0;
  	stepper->slaveTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
  	stepper->slaveTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  	HAL_TIM_Base_Init(&stepper->slaveTimer);

	__HAL_TIM_CLEAR_FLAG(&stepper->slaveTimer, TIM_SR_UIF); // clear interrupt flag

	slaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
  	slaveConfig.InputTrigger = stepper->itr;
  	HAL_TIM_SlaveConfigSynchronization(&stepper->slaveTimer, &slaveConfig);

  	masterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  	masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  	HAL_TIMEx_MasterConfigSynchronization(&stepper->slaveTimer, &masterConfig);

	HAL_NVIC_SetPriority(stepper->irq, 0, 0);
	HAL_NVIC_EnableIRQ(stepper->irq);
}

void stepper_setupTimers(Stepper *stepper)
{
	stepper_setupMasterTimer(stepper);
	stepper_setupSlaveTimer(stepper);
}

uint8_t stepper_setSpeed(Stepper *stepper, uint8_t *speed)
{
	uint32_t nSpeed;
	uint32_t rSpeed;
	// in 16-bit timer max Period value can reach 65535 if there is need to be LONGER period between steps
	// you need to use Prescaler

	// normally greater speed means faster, but there is otherwise, beacuse "speed" meaning is period of time
	// so we need to cast this, but not this moment, because it's need to set up clocks frequency
	// and see in real time, what speed we need

	sscanf(speed, "%d", &nSpeed);

	// min - max
	// <1000, 11000>

	// 1% = 100
	
	if(nSpeed < 1 || nSpeed > 100) // checks if speed is in range
		return 0;

	nSpeed = 101 - nSpeed; // reverse value

	rSpeed = (nSpeed * (11000 - 1000) / 100) + 1000;

	__HAL_TIM_SET_AUTORELOAD(&stepper->masterTimer, rSpeed);

	return 1;
}

uint8_t stepper_switch(Stepper *stepper, uint8_t *state)
{
	if(strcmp(state, "0") != 0 && strcmp(state, "1") != 0)
		return 0;

	HAL_GPIO_WritePin(stepper->port, stepper->enable, (uint8_t)state); // switches the stepper (OFF or ON)

	return 1;
}

uint8_t stepper_setMicrostepping(Stepper *stepper, uint8_t *states)
{
	uint8_t i;
	GPIO_PinState state;

	if(strlen(states) != 3)
		return 0;

	for(i = 0; i < 3; i++)
	{
		if((strcmp(states[i], '0') != 0) && (strcmp(states[i], '1') != 0))
			return 0;

		state = (strcmp(states[i], '0') == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET;

		HAL_GPIO_WritePin(stepper->port, stepper->m[i], state); // sets required state of concret microstep pin 
	}

	return 1;
}

uint8_t stepper_move(Stepper *stepper, uint8_t *steps)
{	
	int32_t nSteps;
	sscanf(steps, "%d", &nSteps);

	if(nSteps == 0)
		return 0;
	else if(nSteps < 0)
		HAL_GPIO_WritePin(stepper->port, stepper->enable, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(stepper->port, stepper->enable, GPIO_PIN_SET);

	HAL_GPIO_WritePin(stepper->port, stepper->enable, GPIO_PIN_SET);

	nSteps = abs(nSteps);
	
	if(nSteps == 1)
		__HAL_TIM_SET_COUNTER(&stepper->slaveTimer, 1);
	else
	{
		// there i noticed something weird, because steppers
		if(stepper->slaveTimer.Instance == TIM2 || stepper->slaveTimer.Instance == TIM5)
			nSteps -= 1;
	}
	
	__HAL_TIM_SET_AUTORELOAD(&stepper->slaveTimer, nSteps);

	
	stepper_switch(stepper, "1");
	HAL_TIM_Base_Start_IT(&stepper->slaveTimer);
	HAL_TIM_PWM_Start(&stepper->masterTimer, stepper->channel); // starts moving

	return 1;
}

void stepper_home(Stepper *stepper)
{
	stepper_setDirection(stepper, 0);
	stepper_run(stepper);
}

uint8_t stepper_setDirection(Stepper *stepper, uint8_t dir)
{
	//if(dir != 0 && dir != 1)
	if(strcmp(dir, '0') != 0 && strcmp(dir, '1') != 0)
		return 0;

	HAL_GPIO_WritePin(stepper->port, stepper->dir, dir);
	
	return 1;
}

void stepper_changeDirection(Stepper *stepper)
{
	HAL_GPIO_TogglePin(stepper->port, stepper->dir);
}

void stepper_run(Stepper *stepper)
{
	stepper_switch(stepper, "1");
	HAL_TIM_PWM_Start(&stepper->masterTimer, stepper->channel); // starts moving
}

uint8_t stepper_pause(Stepper *stepper, uint8_t mode)
{
	if(mode != 0 && mode != 1)
		return 0;

	if(mode)
	{
		stepper->target = stepper->slaveTimer.Instance->ARR;
		stepper->cnt = stepper->slaveTimer.Instance->CNT;
	}
	
	stepper_stop(stepper, mode);
	return 1;
}

uint8_t stepper_resume(Stepper *stepper, uint8_t mode)
{
	if(mode != 0 && mode != 1)
		return 0;

	if(mode)
	{
		__HAL_TIM_SET_AUTORELOAD(&stepper->slaveTimer, stepper->target);
		__HAL_TIM_SET_COUNTER(&stepper->slaveTimer, stepper->cnt);

		HAL_TIM_Base_Start_IT(&stepper->slaveTimer);
	}

	HAL_TIM_PWM_Start(&stepper->masterTimer, stepper->channel);
	return 1;

}

uint8_t stepper_stop(Stepper *stepper, uint8_t mode)
{
	if(mode != 0 && mode != 1)
		return 0;

	HAL_TIM_PWM_Stop(&stepper->masterTimer, stepper->channel);

	if(mode)
		HAL_TIM_Base_Stop_IT(&stepper->slaveTimer);

	return 1;
}

//#endif // STSTM32