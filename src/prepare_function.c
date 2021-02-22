//#ifdef STSTM32
#include "prepare_function.h"

#include <stddef.h> // includes NULL value
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "flag.h"
#include "validator.h"
#include "command/partial/data_assistant.h"
#include "command/cmd_builder.h"

#include "stepper/partial/stepper_configuration.h"
#include "stepper/partial/stepper_operation.h"
#include "stepper/partial/stepper_intervention.h"

uint8_t *prepare_configuration(uint8_t *idx, uint8_t ***args)
{
	Stepper *stepper = NULL;
	uint8_t *feedback = (uint8_t *)"";

	if (strcmp((void *)args[0][0], (void *)KEY.STEPPER) == 0)
	{
		if (!(stepper = device_manager_getStepper(args[0][1])))
			feedback = cmd_builder_buildErr(idx, ERR.INVALID_STEPPER_VALUE);
		else
		{
			if (strcmp((void *)args[1][0], (void *)KEY.SPEED) == 0)
				feedback = cmd_builder_buildPasFinErr(idx, 0, (uint8_t)stepper_setSpeed(stepper, args[1][1]), NULL);
			else
				feedback = cmd_builder_buildErr(idx, ERR.NO_SPEED_KEY);
		}
	}
	else
		feedback = cmd_builder_buildErr(idx, ERR.NO_STEPPER_KEY);

	free(args);

	return feedback;
}

uint8_t *prepare_switch(uint8_t *idx, uint8_t ***args)
{
	Stepper *stepper = NULL;
	uint8_t *feedback = (uint8_t *)"";

	if (strcmp((void *)args[0][0], (void *)KEY.STEPPER) == 0)
	{
		if (!(stepper = device_manager_getStepper(args[0][1])))
			feedback = cmd_builder_buildErr(idx, ERR.INVALID_STEPPER_VALUE);
		else
		{
			if (strcmp((void *)args[1][0], (void *)KEY.STEPPER_STATE) == 0)
				feedback = cmd_builder_buildPasFinErr(idx, 0, (uint8_t)stepper_switch(stepper, args[1][1]), NULL);
			else
				feedback = cmd_builder_buildErr(idx, ERR.NO_STATE_KEY);
		}
	}
	else
		feedback = cmd_builder_buildErr(idx, ERR.NO_STEPPER_KEY);

	free(args);

	return feedback;
}

uint8_t *prepare_home(uint8_t *idx, uint8_t ***args)
{
	Stepper *stepper = NULL;
	uint8_t *feedback = (uint8_t *)"";

	if (strcmp((void *)args[0][0], (void *)KEY.STEPPER) == 0)
	{
		if (!(stepper = device_manager_getStepper(args[0][1])))
			feedback = cmd_builder_buildErr(idx, ERR.INVALID_STEPPER_VALUE);
		else
		{
			if (strcmp((void *)args[1][0], (void *)KEY.DIRECTION) == 0)
				feedback = cmd_builder_buildPasFinErr(idx, 1, (uint8_t)stepper_home(stepper, args[1][1]), stepper);
			else
				feedback = cmd_builder_buildErr(idx, ERR.NO_DIRECTION_KEY);
		}
	}
	else
		feedback = cmd_builder_buildErr(idx, ERR.NO_STEPPER_KEY);

	free(args);

	return feedback;
}

uint8_t *prepare_move(uint8_t *idx, uint8_t ***args)
{
	Stepper *stepper = NULL;
	uint8_t *feedback = (uint8_t *)"";

	if (strcmp((void *)args[0][0], (void *)KEY.STEPPER) == 0)
	{
		if (!(stepper = device_manager_getStepper(args[0][1])))
			feedback = cmd_builder_buildErr(idx, ERR.INVALID_STEPPER_VALUE);
		else
		{
			if (strcmp((void *)args[1][0], (void *)KEY.WAY) == 0)
			{
				if (strcmp((void *)args[2][0], (void *)KEY.DIRECTION) == 0)
					feedback = cmd_builder_buildPasFinErr(idx, 1, (uint8_t)stepper_move(stepper, args[1][1], args[2][1]), stepper);
				else
					feedback = cmd_builder_buildErr(idx, ERR.NO_DIRECTION_KEY);
			}
			else
				feedback = cmd_builder_buildErr(idx, ERR.NO_WAY_KEY);
		}
	}
	else
		feedback = cmd_builder_buildErr(idx, ERR.NO_STEPPER_KEY);

	free(args);

	return feedback;
}

uint8_t *prepare_process(uint8_t *idx, uint8_t ***args)
{
	uint8_t *feedback = (uint8_t *)"";

	if (strcmp((void *)args[0][0], (void *)KEY.DIRECTION) == 0)
	{
		Stepper *x = NULL, *w = NULL;

		x = device_manager_getStepper((uint8_t *)"x");
		w = device_manager_getStepper((uint8_t *)"w");

		if (validate_boolean(args[0][1]))
			feedback = cmd_builder_buildErr(idx, ERR.INVALID_DIRECTION_VALUE);
		else
		{
			stepper_setDirection(w, args[0][1]); // set direction of rotator

			stepper_run(x); // run x stepper
			stepper_run(w); // run w stepper

			PROCESS_FORWARD = 1; // actual process status means it is moving forward
			x->index = idx;		 // save index to x stepper (it is enough -> why x no w ? beacuse the response will be generate on endstop hitted by x stepper)

			feedback = cmd_builder_buildPas(idx); // SUCCESS
		}
	}
	else
		feedback = cmd_builder_buildErr(idx, ERR.NO_DIRECTION_KEY);

	free(args);

	return feedback;
}

uint8_t *prepare_intervention(uint8_t *idx, uint8_t ***args, uint8_t (*fun)(Stepper *))
{
	Stepper *stepper = NULL;
	uint8_t *feedback = (uint8_t *)"";

	if (strcmp((void *)args[0][0], (void *)KEY.STEPPER) == 0)
	{
		if (strcmp((void *)args[0][1], "pro") == 0) // group of steppers that consists of process (x & w)
		{
			fun(device_manager_getStepper((uint8_t *)"x")); // pause / resume / stop
			fun(device_manager_getStepper((uint8_t *)"w")); // pause / resume / stop

			feedback = cmd_builder_buildFin(idx);
		}
		else if (strcmp((void *)args[0][1], "all") == 0) // all steppers (x, y, z, w, k)
		{
			fun(device_manager_getStepper((uint8_t *)"x")); // pause / resume / stop
			fun(device_manager_getStepper((uint8_t *)"y")); // pause / resume / stop
			fun(device_manager_getStepper((uint8_t *)"z")); // pause / resume / stop
			fun(device_manager_getStepper((uint8_t *)"w")); // pause / resume / stop

			feedback = cmd_builder_buildFin(idx);
		}
		else // if individual stepper
		{
			if (!(stepper = device_manager_getStepper(args[0][1])))
				feedback = cmd_builder_buildErr(idx, ERR.INVALID_STEPPER_VALUE);
			else
				feedback = cmd_builder_buildPasFinErr(idx, 0, (uint8_t)fun(stepper), NULL);
		}
	}
	else
		feedback = cmd_builder_buildErr(idx, ERR.NO_STEPPER_KEY);

	free(args);

	return feedback;
}

//#endif // STSTM32