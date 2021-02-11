//#ifdef STSTM32

#include "stepper.h"

#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "counter.h"

void stepper_setupGpio(Stepper *stepper)
{
	GPIO_InitTypeDef gpio;

	/* setups gpio for all stepper pins except step_pin */

	gpio.Pin = stepper->dir | stepper->enable;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init((GPIO_TypeDef *)stepper->port, &gpio);
	HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->port, stepper->enable, GPIO_PIN_SET);

	/* setups gpio for step_pin */
	gpio.Pin = stepper->step;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_PULLUP;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio.Alternate = stepper->alternateFunction;

	HAL_GPIO_Init((GPIO_TypeDef *)stepper->port, &gpio);
}

void stepper_setupMasterTimer(Stepper *stepper)
{
	TIM_MasterConfigTypeDef masterConfig = {0};
	TIM_OC_InitTypeDef configOC = {0};

	stepper->masterTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
	stepper->masterTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	stepper->masterTimer.Init.Prescaler = 104;
	stepper->masterTimer.Init.Period = 0;
	stepper->masterTimer.Instance->CNT = 0;
	HAL_TIM_Base_Init(&stepper->masterTimer);

	//clockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	//HAL_TIM_ConfigClockSource(&stepper->master_timer, &clockSourceConfig);

	masterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&stepper->masterTimer, &masterConfig);

	configOC.OCMode = TIM_OCMODE_PWM1;
	configOC.Pulse = 10; // minimum pulse width should be given by driver, and will be like 1,5us or 2,0us
	configOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	configOC.OCFastMode = TIM_OCFAST_ENABLE; // TIM_OCFAST_DISABLE
	HAL_TIM_PWM_ConfigChannel(&stepper->masterTimer, &configOC, stepper->channel);
}

void stepper_setupSlaveTimer(Stepper *stepper)
{
	TIM_SlaveConfigTypeDef slaveConfig = {0};
	TIM_MasterConfigTypeDef masterConfig = {0};

	stepper->slaveTimer.Init.Prescaler = 0;
	stepper->slaveTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
	stepper->slaveTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	stepper->slaveTimer.Instance->CNT = 0;
	HAL_TIM_Base_Init(&stepper->slaveTimer);

	__HAL_TIM_CLEAR_FLAG(&stepper->slaveTimer, TIM_SR_UIF);	 // clear interrupt flag
	__HAL_TIM_CLEAR_IT(&stepper->slaveTimer, TIM_IT_UPDATE); // clear update flag

	slaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
	slaveConfig.InputTrigger = stepper->itr;
	HAL_TIM_SlaveConfigSynchronization(&stepper->slaveTimer, &slaveConfig);

	masterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&stepper->slaveTimer, &masterConfig);

	HAL_NVIC_SetPriority(stepper->irq, 0, 0); // set priority of stepper slaveTimer interrupt
	HAL_NVIC_EnableIRQ(stepper->irq);		  // enable stepper slaveTimer interrupt
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3)
	{
		//TIM3->ARR = v;
		//TIM3->CCR1 = v / 2;
	}
}

void stepper_setupTimers(Stepper *stepper)
{
	stepper_setupMasterTimer(stepper);
	stepper_setupSlaveTimer(stepper);
}

void stepper_init(Stepper *stepper, uint8_t *name, uint32_t port, TIM_TypeDef *masterTimer, TIM_TypeDef *slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq, uint16_t step, uint16_t dir, uint16_t enable, uint16_t minSpeed, uint16_t maxSpeed)
{
	strcpy((void *)stepper->name, (void *)name);

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

	stepper->lastState = stepper->state = OFF; // reset stepper state
	stepper->homeStep = FAST;
	stepper->lastHomeStep = PRECISE; // init value antything, just different than homeStep

	stepper->minSpeed = minSpeed;
	stepper->maxSpeed = maxSpeed;

	stepper->minEndstop = stepper->maxEndstop = NULL;

	stepper_setupGpio(stepper);
	stepper_setupTimers(stepper);

	stepper->state = OFF;
}

void stepper_assignEndstops(Stepper *stepper, Endstop *min, Endstop *max)
{
	stepper->minEndstop = min;
	stepper->maxEndstop = max;
}

void stepper_deinit(Stepper *stepper)
{
	HAL_TIM_PWM_Stop(&stepper->masterTimer, stepper->channel);
	HAL_TIM_Base_Stop_IT(&stepper->slaveTimer);
	HAL_NVIC_DisableIRQ(stepper->irq);
}

uint8_t stepper_setSpeed(Stepper *stepper, uint8_t *speed)
{
	uint32_t nSpeed = 0; // speed percentage
	uint32_t rSpeed = 0; // real speed

	// in 16-bit timer max Period value can reach 65535 if there is need to be LONGER period between steps
	// you need to use Prescaler

	// normally greater speed means faster, but there is otherwise, beacuse "speed" meaning period of time
	// so we need to cast this, but not this moment, because it's need to set up clocks frequency
	// and see in real time, what speed we need

	uint8_t len = strlen((void *)speed);

	if (len == 0 || len > 3) // check if string is empty or too long
		return 0;
	else
	{
		if (speed[0] == '0') // check if string starts with 0
			return 0;
	}

	uint8_t i;

	for (i = 0; i < len; i++)
	{
		if (speed[i] < 48 || speed[i] > 57) // check if string contains only numbers
			return 0;
	}

	sscanf((void *)speed, "%d", &nSpeed);

	if (nSpeed < 1 || nSpeed > 100) // checks if speed is in range
		return 0;

	// this is kind of reverse
	// if you wanna the highest speed the rSpeed must be the lowest
	nSpeed = 101 - nSpeed;																		 // reverse value
	rSpeed = ceil((nSpeed * (stepper->maxSpeed - stepper->minSpeed) / 100) + stepper->minSpeed); // calculte real speed

	__HAL_TIM_SET_AUTORELOAD(&stepper->masterTimer, rSpeed);						  // set speed
	__HAL_TIM_SET_COMPARE(&stepper->masterTimer, stepper->channel, ceil(rSpeed / 2)); // set pulse width

	return 1;
}

uint8_t stepper_switch(Stepper *stepper, uint8_t state)
{
	if (stepper->state == HOMING || stepper->state == MOVING) // cannot switch motor if stepper is homing or moving
		return 0;

	if (stepper->state != state) // check if state is not currently exists
	{
		HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->port, stepper->enable, state == 0 ? 1 : 0); // switches the stepper (OFF or ON)
		stepper->state = state;																   // update stepper state
	}

	return 1;
}

uint8_t stepper_emergency_shutdown(Stepper *stepper)
{
	HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->port, stepper->enable, GPIO_PIN_RESET); // switches the stepper OFF

	stepper->state = OFF; // update stepper state

	return 1;
}

uint8_t stepper_home(Stepper *stepper, uint8_t direction)
{
	if (((stepper->state == HOMING || stepper->state == MOVING) && stepper->homeStep == stepper->lastHomeStep) || stepper->state == PAUSED) // cannot home if motor is homing or moving right now or also paused
		return 0;

	if (stepper->homeStep == FAST)
	{
		if (!endstop_isClicked(stepper->minEndstop))
		{
			stepper_setSpeed(stepper, (uint8_t *)"30"); // home with 30% speed
			stepper_setDirection(stepper, direction);	// set left direction
			stepper_run(stepper);						// start motor moving

			stepper->state = HOMING; // update stepper state
			stepper->lastHomeStep = FAST;
		}
	}
	else if (stepper->homeStep == BACKWARD)
	{
		counter_count(65000);
		stepper->state = ON;
		stepper_move(stepper, (uint8_t *)"400");

		stepper->lastHomeStep = BACKWARD;
	}
	else
	{
		//HAL_Delay(150);
		stepper_setSpeed(stepper, (uint8_t *)"1");
		stepper_changeDirection(stepper);
		stepper_run(stepper);

		stepper->state = HOMING;
		stepper->lastHomeStep = PRECISE;
	}

	return 1;
}

uint8_t stepper_move(Stepper *stepper, uint8_t *steps)
{
	int32_t nSteps = 0;
	uint8_t len = strlen((void *)steps);

	if (stepper->state == HOMING || stepper->state == MOVING || stepper->state == PAUSED) // cannot move if motor is homing or moving or is paused right now
		return 9;

	if (len == 0) // check if length of string is 0
		return 0;
	else if (len > 1 && steps[0] == '0') // check if length is more than 1 (OK), but not ok if it's starting with 0
		return 0;

	if ((steps[0] < 48 || steps[0] > 58) && steps[0] != '-') // check if it's not number and not "-" (minus) sign
		return 0;

	uint8_t i;

	for (i = 1; i < len; i++)
	{
		if (steps[i] < 48 || steps[i] > 57) // check if string contains only numbers
			return 0;
	}

	sscanf((void *)steps, "%" SCNd32, &nSteps); // translate string to number

	if (nSteps == 0) // if steps is equals to 0, error
		return 0;
	else if (nSteps < 0) // check if steos are negative, set LEFT direction
		stepper_setDirection(stepper, 0);
	else // set RIGHT direction
		stepper_setDirection(stepper, 1);

	nSteps = abs(nSteps); // calc absolute value

	if (nSteps == 1) // this is weird situation if we want to move by 1 step, i need to set counter to 1
		__HAL_TIM_SET_COUNTER(&stepper->slaveTimer, 1);
	else
	{
		if (stepper->slaveTimer.Instance == TIM2 || stepper->slaveTimer.Instance == TIM5) // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease steps for them
			nSteps -= 1;
	}

	__HAL_TIM_SET_AUTORELOAD(&stepper->slaveTimer, nSteps); // set target value

	stepper_switch(stepper, 1);									// turn ON stepper motor
	HAL_TIM_Base_Start_IT(&stepper->slaveTimer);				// starts counting of PWM cycles
	HAL_TIM_PWM_Start(&stepper->masterTimer, stepper->channel); // starts moving

	stepper->state = MOVING; // update stepper state

	return 1;
}

void stepper_setDirection(Stepper *stepper, uint8_t dir)
{
	HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->port, stepper->dir, dir);
	counter_count(5);
}

void stepper_changeDirection(Stepper *stepper)
{
	HAL_GPIO_TogglePin((GPIO_TypeDef *)stepper->port, stepper->dir);
	counter_count(5);
}

void stepper_run(Stepper *stepper)
{
	stepper_switch(stepper, 1);									// turn ON stepper
	HAL_TIM_PWM_Start(&stepper->masterTimer, stepper->channel); // starts moving
}

uint8_t stepper_pause(Stepper *stepper)
{
	if ((stepper->state != HOMING && stepper->state != MOVING) || stepper->state == PAUSED) // cannot pause if stepper is not homing, not moving or if it is already paused
		return 0;

	if (stepper->state == MOVING) // if stepper is in MOVING state i need to remember register values TARGET and COUNTER
	{
		stepper->target = stepper->slaveTimer.Instance->ARR;
		stepper->cnt = stepper->slaveTimer.Instance->CNT;

		if (stepper->slaveTimer.Instance == TIM2 || stepper->slaveTimer.Instance == TIM5) // if TIM2 and TIM5 i need to decrease target
			stepper->target--;
	}

	stepper_stopTimers(stepper); // stop timers

	stepper->lastState = stepper->state; // remember last state
	stepper->state = PAUSED;			 // update state

	return 1;
}

uint8_t stepper_resume(Stepper *stepper)
{
	if (stepper->state != PAUSED) // cannot resume stepper if it's not paused
		return 0;

	if (stepper->lastState == MOVING) // if stepper was in MOVING state before pause, we need to set target and counter to previous values
	{
		__HAL_TIM_SET_AUTORELOAD(&stepper->slaveTimer, stepper->target);
		__HAL_TIM_SET_COUNTER(&stepper->slaveTimer, stepper->cnt);

		HAL_TIM_Base_Start_IT(&stepper->slaveTimer); // enable slaveTimer
	}

	HAL_TIM_PWM_Start(&stepper->masterTimer, stepper->channel); // enable masterTimer

	stepper->state = stepper->lastState; // recover state

	return 1;
}

uint8_t stepper_stop(Stepper *stepper)
{
	if (stepper->state != HOMING && stepper->state != MOVING && stepper->state != PAUSED) // cannot stop motor if its not homing, moving or not paused
		return 0;

	stepper_stopTimers(stepper); // stop timers

	stepper->lastState = stepper->state = ON; // reset stepper state

	return 1;
}

void stepper_stopTimers(Stepper *stepper)
{
	HAL_TIM_PWM_Stop(&stepper->masterTimer, stepper->channel); // stop masterTimer

	if (stepper->state == MOVING)					// check if stepper is in MOVING state i need to stop slaveTimer too
		HAL_TIM_Base_Stop_IT(&stepper->slaveTimer); // stop slaveTimer

	stepper_reset(stepper); // reset stepper
}

void stepper_reset(Stepper *stepper)
{
	stepper->state = ON; // reset state of motor

	__HAL_TIM_SET_COUNTER(&stepper->slaveTimer, 0);	 // reset slaveTimer counter
	__HAL_TIM_SET_COUNTER(&stepper->masterTimer, 0); // reset masterTimer counter

	__HAL_TIM_CLEAR_FLAG(&stepper->slaveTimer, TIM_SR_UIF);	 // clear interrupt flag
	__HAL_TIM_CLEAR_IT(&stepper->slaveTimer, TIM_IT_UPDATE); // clear update_flag
}

//#endif // STSTM32