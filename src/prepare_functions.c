//#ifdef STSTM32

#include "prepare_functions.h"

#include "cmd_builder.h"

uint8_t *prepare_settings(uint8_t ***args, uint8_t size, uint8_t *key, uint8_t (*fun)(Stepper*, uint8_t*))
{
	Stepper *stepper = NULL;
	uint8_t* feedback = (uint8_t*)"";
	uint8_t* index = args[0][1];

	if(strcmp((void*)args[2][0], KEYS.STEPPER) == 0) // checks if the selected string is "spp" (stepper)
	{
		if(!(stepper = device_manager_getStepper(args[2][1]))) // checks if set current device goes successfull, if no returns ERROR
			feedback = cmd_builder_buildErr(index, 9); // "invalid stepper name"
		else
		{
			if(strcmp((void*)args[3][0], (void*)key) == 0)
			{
				if(!fun(stepper, args[3][1]))
				{
					if(strcmp((void *)key, KEYS.SPEED) == 0)
						feedback = cmd_builder_buildErr(index, 12); // "invalid speed value"
					else
						feedback = cmd_builder_buildErr(index, 13); // "invalid microstepping value"
				}
				else
					feedback = cmd_builder_buildFin(index, -1); // success
			}
			else
			{
				if(strcmp((void *)key, KEYS.SPEED) == 0)
					feedback = cmd_builder_buildErr(index, 10); // "no speed key"
				else
					feedback = cmd_builder_buildErr(index, 11); // "no microstepping key"
			}				
		}
	}
	else 
		feedback = cmd_builder_buildErr(index, 8); // "no stepper key"

	free(args); // frees memory allocated to args
	
	return feedback;
}

uint8_t *prepare_getEndstopState(uint8_t ***args, uint8_t size)
{
	Endstop *endstop = NULL;
	uint8_t* feedback = (uint8_t*)"";
	uint8_t* index = args[0][1];

	if(strcmp((void *)args[2][0], KEYS.ENDSTOP) == 0)
	{
		if(!(endstop = device_manager_getEndstop(args[2][1]))) // checks if set current device goes successfull, if no returns ERROR
			feedback = cmd_builder_buildErr(index, 15); // "invalid endstop name",
		else
			feedback = cmd_builder_buildFin(index, endstop_isClicked(endstop)); // success with value
	}
	else
		feedback = cmd_builder_buildErr(index, 14); // "no endstop key"
	
	free(args); // free memory allocated to args

	return feedback;
}

uint8_t *prepare_switch(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	uint8_t* feedback = (uint8_t*)"";
	uint8_t* index = args[0][1];

	if(strcmp((void *)args[2][0], KEYS.STEPPER) == 0) // checks if the selected string is "spp" (stepper)
	{
		if(!(stepper = device_manager_getStepper(args[2][1]))) // checks if set current device goes successfull, if no returns ERROR
			feedback = cmd_builder_buildErr(index, 9); // "invalid stepper name"
		else
		{
			if(strcmp((void *)args[3][0], KEYS.STEPPER_STATE) == 0)
			{
				if(strcmp((void *)args[3][1], "0") != 0 && strcmp((void *)args[3][1], "1") != 0)
					feedback = cmd_builder_buildErr(index, 17); // "invalid stepper_state value
				else
				{
					uint8_t state = 0;

					sscanf((void *)args[3][1], "%d", &state);

					if(!stepper_switch(stepper, state))
						feedback = cmd_builder_buildErr(index, 18); // "operation not allowed"
					else
						feedback = cmd_builder_buildFin(index, -1); // success
				}				
			}
			else
				feedback = cmd_builder_buildErr(index, 16); // "no stepper_state key"
		}
	}
	else 
		feedback = cmd_builder_buildErr(index, 8); // "no stepper key

	free(args); // frees memory allocated to args
	
	return feedback;
}

uint8_t *prepare_home(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	uint8_t* feedback = (uint8_t*)"";
	uint8_t* index = args[0][1];

	if(strcmp((void *)args[2][0], KEYS.STEPPER) == 0) // checks if the selected string is "spp" (stepper)
	{
		if(!(stepper = device_manager_getStepper(args[2][1]))) // checks if set current device goes successfull, if no returns ERROR
			feedback = cmd_builder_buildErr(index, 9); // "invalid stepper name"
		else
		{
			if(!stepper_home(stepper))
				feedback = cmd_builder_buildErr(index, 18); // "operation not allowed"
			else
			{
				feedback = cmd_builder_buildPas(index); // passed
				uint8_t id;
				sscanf((void *)index, "%d", &id);
				stepper->index = id;
			}
				
		}	
	}
	else
		feedback = cmd_builder_buildErr(index, 8); // "no stepper key"

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_move(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	uint8_t* feedback = (uint8_t*)"";
	uint8_t* index = args[0][1];

	if(strcmp((void *)args[2][0], KEYS.STEPPER) == 0)
	{
		if(!(stepper = device_manager_getStepper(args[2][1]))) // checks if set current device goes successfull, if no returns ERROR
			feedback = cmd_builder_buildErr(index, 9); // "invalid stepper name"
		else
		{
			if(strcmp((void *)args[3][0], KEYS.STEPS) == 0)
			{
				uint8_t result = stepper_move(stepper, args[3][1]);
				if(!result)
					feedback = cmd_builder_buildErr(index, 20); // "invalid steps value (0)"
				else
				{
					if(result == 1)
					{
						feedback = cmd_builder_buildPas(index); // passed
						uint8_t id;
						sscanf((void *)index, "%d", &id);
						stepper->index = id;
					}
					else if(result == 9)
						feedback = cmd_builder_buildErr(index, 18);  // "operation not allowed"
				}
					
			}
			else
				feedback = cmd_builder_buildErr(index, 19); // "no steps key"
		}
	}
	else
		feedback = cmd_builder_buildErr(index, 8); // "no stepper key"
	
	free(args); // free memory allocated to args

	return feedback;
}

uint8_t *prepare_process(uint8_t ***args, uint8_t size) // opt=pro|spp=x|spd=40|spp=w|dir=1|spd=70
{
	uint8_t* feedback = (uint8_t*)"";
	uint8_t* index = args[0][1];

	if(strcmp((void *)args[2][0], KEYS.DIRECTION) == 0)
	{
		Stepper *x = NULL, *w = NULL;

		x = device_manager_getStepper((uint8_t*)"x");
		w = device_manager_getStepper((uint8_t*)"w");

		if(strcmp((void *)args[2][1], "0") != 0 && strcmp((void *)args[2][1], "1") != 0)
			feedback = cmd_builder_buildErr(index, 22); // "invalid direction value"
		else
		{	
			uint8_t dir;
			
			sscanf((void *)args[2][1], "%d", &dir);

			stepper_setDirection(w, dir);

			stepper_run(x);
			stepper_run(w);

			PROCESS_FORWARD = 1;

			feedback = cmd_builder_buildPas(index);
		}
	}
	else
		feedback = cmd_builder_buildErr(index, 21); // "no direction key"

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_intervention(uint8_t ***args, uint8_t size, uint8_t (*fun)(Stepper*))
{
	Stepper *stepper = NULL;
	uint8_t* feedback = (uint8_t*)"";
	uint8_t* index = args[0][1];

	if(strcmp((void *)args[2][0], KEYS.STEPPER) == 0) // checks if the selected string is "spp" (stepper)
	{
		if(strcmp((void *)args[2][1], "pro") == 0)
		{
			fun(device_manager_getStepper((uint8_t*)"x"));
			fun(device_manager_getStepper((uint8_t*)"w"));

			feedback = cmd_builder_buildFin(index, -1); // success
		}
		else if(strcmp((void *)args[2][1], "all") == 0)
		{
			fun(device_manager_getStepper((uint8_t*)"x"));
			fun(device_manager_getStepper((uint8_t*)"y"));
			fun(device_manager_getStepper((uint8_t*)"z"));
			fun(device_manager_getStepper((uint8_t*)"w"));

			feedback = cmd_builder_buildFin(index, -1); // success
		}
		else
		{
			if(!(stepper = device_manager_getStepper(args[2][1]))) // checks if set current device goes successfull, if no returns ERROR
				feedback = cmd_builder_buildErr(index, 9); // "invalid stepper name"
			else
			{
				if(!fun(stepper))
					feedback = cmd_builder_buildErr(index, 18); // "operation not allowed"
				else
					feedback = cmd_builder_buildFin(index, -1); // success	
			}
		}
	}
	else 
		feedback = cmd_builder_buildErr(index, 8); // "no stepper key"
	
	free(args); // frees memory allocated to args

	return feedback;
}

//#endif // STSTM32