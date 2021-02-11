//#ifdef STSTM32
#include "prepare_functions.h"

#include <stdlib.h>
#include <string.h>

#include "flags.h"
#include "cmd_builder.h"

uint8_t *prepare_settings(uint8_t *idx, uint8_t ***args)
{
	Stepper *stepper = NULL;
	uint8_t *feedback = (uint8_t *)"";

	if (strcmp((void *)args[0][0], (void *)KEYS.STEPPER) == 0) // checks if the selected string is "spp" (stepper)
	{
		if (!(stepper = device_manager_getStepper(args[0][1])))	  // checks if set current device goes successfull, if no returns ERROR
			feedback = cmd_builder_buildErr(idx, (uint8_t *)"9"); // "invalid stepper name"
		else													  // success getStepper
		{
			if (strcmp((void *)args[1][0], (void *)KEYS.SPEED) == 0) // check if there is SPEED key
			{
				if (!stepper_setSpeed(stepper, args[1][1]))				   // try to setup SPEED and if failed ...
					feedback = cmd_builder_buildErr(idx, (uint8_t *)"12"); // "invalid speed value"
				else
					feedback = cmd_builder_buildFin(idx, (uint8_t *)"2"); // success
			}
			else													   // key is not SPEED
				feedback = cmd_builder_buildErr(idx, (uint8_t *)"10"); // "no speed key"
		}
	}
	else													  // there is no STEPPER key
		feedback = cmd_builder_buildErr(idx, (uint8_t *)"8"); // "no stepper key"

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_getEndstopState(uint8_t *idx, uint8_t ***args)
{
	Endstop *endstop = NULL;
	uint8_t *feedback = (uint8_t *)"";

	if (strcmp((void *)args[0][0], (void *)KEYS.ENDSTOP) == 0) // check if there is ENDSTOP key
	{
		if (!(endstop = device_manager_getEndstop((uint8_t *)args[0][1])))	  // checks if set current device goes successfull, if no returns ERROR
			feedback = cmd_builder_buildErr(idx, (uint8_t *)"15");			  // "invalid endstop name",
		else																  // success
			feedback = cmd_builder_buildFin(idx, endstop_isClicked(endstop)); // success with value
	}
	else													   // there is no ENDSTOP KEY
		feedback = cmd_builder_buildErr(idx, (uint8_t *)"14"); // "no endstop key"

	free(args); // free memory allocated to args

	return feedback;
}

uint8_t *prepare_switch(uint8_t *idx, uint8_t ***args)
{
	Stepper *stepper = NULL;
	uint8_t *feedback = (uint8_t *)"";

	if (strcmp((void *)args[0][0], (void *)KEYS.STEPPER) == 0) // checks if the selected string is "spp" (stepper)
	{
		if (!(stepper = device_manager_getStepper(args[0][1])))	  // checks if set current device goes successfull, if no returns ERROR
			feedback = cmd_builder_buildErr(idx, (uint8_t *)"9"); // "invalid stepper name"
		else													  // success getStepper
		{
			if (strcmp((void *)args[1][0], (void *)KEYS.STEPPER_STATE) == 0) // check if there is STEPPER_STATE key
			{
				if (strcmp((void *)args[1][1], "0") != 0 && strcmp((void *)args[1][1], "1") != 0) // check if value is 0 or 1
					feedback = cmd_builder_buildErr(idx, (uint8_t *)"17");						  // "invalid stepper_state value
				else																			  // if the value is correct
				{
					uint8_t state = 0; // init any value

					sscanf((void *)args[1][1], "%d", &state); // str to int

					if (!stepper_switch(stepper, state))					   // try to switch stepper state
						feedback = cmd_builder_buildErr(idx, (uint8_t *)"18"); // "operation not allowed"
					else													   // success
						feedback = cmd_builder_buildFin(idx, (uint8_t *)"2");  // success
				}
			}
			else													   // no stepper state key
				feedback = cmd_builder_buildErr(idx, (uint8_t *)"16"); // "no stepper_state key"
		}
	}
	else													  // no stepper key
		feedback = cmd_builder_buildErr(idx, (uint8_t *)"8"); // "no stepper key

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_home(uint8_t *idx, uint8_t ***args)
{
	Stepper *stepper = NULL;
	uint8_t *feedback = (uint8_t *)"";

	if (strcmp((void *)args[0][0], (void *)KEYS.STEPPER) == 0) // checks if the selected string is "spp" (stepper)
	{
		if (!(stepper = device_manager_getStepper(args[0][1])))	  // checks if set current device goes successfull, if no returns ERROR
			feedback = cmd_builder_buildErr(idx, (uint8_t *)"9"); // "invalid stepper name"
		else													  // success getStepper
		{
			if (strcmp((void *)args[1][0], (void *)KEYS.DIRECTION) == 0) // check if there is direction key
			{
				if (strcmp((void *)args[1][1], "0") != 0 && strcmp((void *)args[1][1], "1") != 0) // check if value is 0 or 1
					feedback = cmd_builder_buildErr(idx, (uint8_t *)"22");						  // "invalid direction value
				else
				{
					uint8_t direction = 0; // init any value

					sscanf((void *)args[1][1], "%d", &direction); // str to int

					if (!stepper_home(stepper, direction))					   // try to home stepper
						feedback = cmd_builder_buildErr(idx, (uint8_t *)"18"); // "operation not allowed"
					else													   // success home
					{
						feedback = cmd_builder_buildPas(idx); // passed
						stepper->index = idx;
					}
				}
			}
			else													   // no direction key
				feedback = cmd_builder_buildErr(idx, (uint8_t *)"21"); // "no direction key"
		}
	}
	else													  // no stepper key
		feedback = cmd_builder_buildErr(idx, (uint8_t *)"8"); // "no stepper key"

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_move(uint8_t *idx, uint8_t ***args)
{
	Stepper *stepper = NULL;
	uint8_t *feedback = (uint8_t *)"";

	if (strcmp((void *)args[0][0], (void *)KEYS.STEPPER) == 0) // check if the selected string is "spp"
	{
		if (!(stepper = device_manager_getStepper(args[0][1])))	  // checks if set current device goes successfull, if no returns ERROR
			feedback = cmd_builder_buildErr(idx, (uint8_t *)"9"); // "invalid stepper name"
		else													  // success getStepper
		{
			if (strcmp((void *)args[1][0], (void *)KEYS.STEPS) == 0) // check if there is steps key
			{
				uint8_t result = stepper_move(stepper, args[1][1]);		   // move stepper & get feedback
				if (!result)											   // if result is <= 0
					feedback = cmd_builder_buildErr(idx, (uint8_t *)"20"); // "invalid steps value (0)"
				else													   // if result > 0
				{
					if (result == 1) // success
					{
						feedback = cmd_builder_buildPas(idx); // passed

						stepper->index = idx;
					}
					else if (result == 9)									   // not allowed
						feedback = cmd_builder_buildErr(idx, (uint8_t *)"18"); // "operation not allowed"
				}
			}
			else													   // not steps key
				feedback = cmd_builder_buildErr(idx, (uint8_t *)"19"); // "no steps key"
		}
	} // no stepper key
	else
		feedback = cmd_builder_buildErr(idx, (uint8_t *)"8"); // "no stepper key"

	free(args); // free memory allocated to args

	return feedback;
}

uint8_t *prepare_process(uint8_t *idx, uint8_t ***args) // opt=pro|spp=x|spd=40|spp=w|dir=1|spd=70
{
	uint8_t *feedback = (uint8_t *)"";

	if (strcmp((void *)args[0][0], (void *)KEYS.DIRECTION) == 0) // check if the key is direction
	{
		Stepper *x = NULL, *w = NULL;

		x = device_manager_getStepper((uint8_t *)"x"); // get main x stepper (table)
		w = device_manager_getStepper((uint8_t *)"w"); // get main w stepper (rotator)

		if (strcmp((void *)args[0][1], "0") != 0 && strcmp((void *)args[0][1], "1") != 0) // check if value of dir key is 0 or 1
			feedback = cmd_builder_buildErr(idx, (uint8_t *)"22");						  // "invalid direction value"
		else																			  // if the dir value is correct
		{
			uint8_t dir = 0; // init any value

			sscanf((void *)args[0][1], "%d", &dir); // str to int

			stepper_setDirection(w, dir); // set direction of rotator

			stepper_run(x); // run x stepper
			stepper_run(w); // run w stepper

			PROCESS_FORWARD = 1; // acutal process status is that it is moving forward

			x->index = idx; // save index to x stepper (it is enough -> why x no w ? beacuse the response will be generate on endstop hitted by x stepper)

			feedback = cmd_builder_buildPas(idx); // build command to info that everything is fine
		}
	}
	else													   // no dir key
		feedback = cmd_builder_buildErr(idx, (uint8_t *)"21"); // "no direction key"

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_intervention(uint8_t *idx, uint8_t ***args, uint8_t (*fun)(Stepper *))
{
	Stepper *stepper = NULL;
	uint8_t *feedback = (uint8_t *)"";

	if (strcmp((void *)args[0][0], (void *)KEYS.STEPPER) == 0) // checks if the selected string is "spp" (stepper)
	{
		if (strcmp((void *)args[0][1], "pro") == 0) // group of steppers that consists of process (x & w)
		{
			fun(device_manager_getStepper((uint8_t *)"x")); // pause / resume / stop
			fun(device_manager_getStepper((uint8_t *)"w")); // pause / resume / stop

			feedback = cmd_builder_buildFin(idx, (uint8_t *)"2"); // success
		}
		else if (strcmp((void *)args[0][1], "all") == 0) // all steppers (x, y, z, w, k)
		{
			fun(device_manager_getStepper((uint8_t *)"x")); // pause / resume / stop
			fun(device_manager_getStepper((uint8_t *)"y")); // pause / resume / stop
			fun(device_manager_getStepper((uint8_t *)"z")); // pause / resume / stop
			fun(device_manager_getStepper((uint8_t *)"w")); // pause / resume / stop

			feedback = cmd_builder_buildFin(idx, (uint8_t *)"2"); // success
		}
		else // if individual stepper
		{
			if (!(stepper = device_manager_getStepper(args[0][1])))	  // checks if set current device goes successfull, if no returns ERROR
				feedback = cmd_builder_buildErr(idx, (uint8_t *)"9"); // "invalid stepper name"
			else													  // success getStepper
			{
				if (!fun(stepper))										   // try to pause / resume / stop
					feedback = cmd_builder_buildErr(idx, (uint8_t *)"18"); // "operation not allowed"
				else													   // success
					feedback = cmd_builder_buildFin(idx, (uint8_t *)"2");  // success
			}
		}
	}
	else													  // no spp key
		feedback = cmd_builder_buildErr(idx, (uint8_t *)"8"); // "no stepper key"

	free(args); // frees memory allocated to args

	return feedback;
}

//#endif // STSTM32