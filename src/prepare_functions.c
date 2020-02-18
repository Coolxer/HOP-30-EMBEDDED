//#ifdef STSTM32

#include "prepare_functions.h"

#include <stdlib.h>
#include <string.h>

#include "data_assistant.h"

uint8_t *prepare_settings(uint8_t ***args, uint8_t size, uint8_t *key, uint8_t (*fun)(Stepper*, uint8_t*))
{
	Stepper *stepper = NULL;
	uint8_t* feedback = (uint8_t*)"";

	if(strcmp((void*)args[0][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
	{
		if(!(stepper = device_manager_getStepper(args[0][1]))) // checks if set current device goes successfull, if no returns ERROR
			feedback = (uint8_t*)"_ERROR_invalid_spp_value";
		else
		{
			if(strcmp((void*)args[1][0], (void*)key) == 0)
			{
				if(!fun(stepper, args[1][1]))
				{
					feedback = str_append((uint8_t*)"_ERROR_invalid_", key);
					feedback = str_append(feedback, (uint8_t*)"_value");
				}
				else
					feedback = (uint8_t*)"_SUCCESS";
			}
			else
			{
				feedback = str_append((uint8_t*)"_ERROR_no_", key);
				feedback = str_append(feedback, (uint8_t*)"_key");
			}				
		}
	}
	else 
		feedback = (uint8_t*)"_ERROR_no_spp_key";

	free(args); // frees memory allocated to args
	
	return feedback;
}

uint8_t *prepare_getEndstopState(uint8_t ***args, uint8_t size)
{
	Endstop *endstop = NULL;
	uint8_t* feedback = (uint8_t*)"";

	if(strcmp((void *)args[0][0], "end") == 0)
	{
		if(!(endstop = device_manager_getEndstop(args[0][1]))) // checks if set current device goes successfull, if no returns ERROR
			feedback = (uint8_t*)"_ERROR_invalid_end_value";
		else
		{
			feedback = (uint8_t*)"_SUCCESS_";
			feedback = str_append(feedback, args[0][1]);
			feedback = str_append(feedback, (uint8_t*)"_STATE_");
			feedback = char_append(feedback, (uint8_t*)endstop_isClicked(endstop));
		}
	}
	else
		feedback = (uint8_t*)"_ERROR_no_end_key";
	
	free(args); // free memory allocated to args

	return feedback;
}

uint8_t *prepare_switch(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	uint8_t* feedback = (uint8_t*)"";

	if(strcmp((void *)args[0][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
	{
		if(strcmp((void *)args[0][1], "all") == 0)
		{
			if(strcmp((void *)args[1][0], "stt") == 0)
			{
				uint8_t *stt = args[1][1];

				if(strcmp((void*)stt, "0") == 0)
				{
					stepper_emergency_shutdown(device_manager_getStepper((uint8_t*)"x"));
					stepper_emergency_shutdown(device_manager_getStepper((uint8_t*)"y"));
					stepper_emergency_shutdown(device_manager_getStepper((uint8_t*)"z"));
					stepper_emergency_shutdown(device_manager_getStepper((uint8_t*)"w"));

					feedback = (uint8_t*)"_SUCCESS";
				}
				else if(strcmp((void*)stt, "1") == 0)
				{
					stepper_switch(device_manager_getStepper((uint8_t*)"x"), 1);
					stepper_switch(device_manager_getStepper((uint8_t*)"y"), 1);
					stepper_switch(device_manager_getStepper((uint8_t*)"z"), 1);
					stepper_switch(device_manager_getStepper((uint8_t*)"w"), 1);

					feedback = (uint8_t*)"_SUCCESS";
				}
				else
					feedback = (uint8_t*)"_ERROR_invalid_stt_value";	
			}
			else
				feedback = (uint8_t*)"_ERROR_no_stt_key";	
		}
		else
		{
			if(!(stepper = device_manager_getStepper(args[0][1]))) // checks if set current device goes successfull, if no returns ERROR
				feedback = (uint8_t*)"_ERROR_invalid_spp_value";
			else
			{
				if(strcmp((void *)args[1][0], "stt") == 0)
				{
					if(strcmp((void *)args[1][1], "0") != 0 && strcmp((void *)args[1][1], "1") != 0)
						feedback = (uint8_t*)"_ERROR_invalid_stt_value";
					else
					{
						uint8_t state = 0;

						sscanf((void *)args[1][1], "%d", &state);

						if(!stepper_switch(stepper, state))
							feedback = (uint8_t*)"_ERROR_operation_not_allowed";
						else
							feedback = (uint8_t*)"_SUCCESS";
					}	
				}
				else
					feedback = (uint8_t*)"_ERROR_no_stt_key";			
			}
		}
	}
	else 
		feedback = (uint8_t*)"_ERROR_no_spp_key";

	free(args); // frees memory allocated to args
	
	return feedback;
}

uint8_t *prepare_home(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	uint8_t* feedback = (uint8_t*)"";

	if(strcmp((void *)args[0][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
	{
		if(strcmp((void *)args[0][1], "all") == 0)
		{
			stepper_home(device_manager_getStepper((uint8_t*)"x"));
			stepper_home(device_manager_getStepper((uint8_t*)"y"));
			stepper_home(device_manager_getStepper((uint8_t*)"z"));
			
			feedback = (uint8_t*)"_VALID_COMMAND";
		}
		else
		{
			if(!(stepper = device_manager_getStepper(args[0][1]))) // checks if set current device goes successfull, if no returns ERROR
				feedback = (uint8_t*)"_ERROR_invalid_spp_value";
			else
			{
				if(!stepper_home(stepper))
					feedback = (uint8_t*)"_ERROR_operation_not_allowed";
				else
					feedback = (uint8_t*)"_VALID_COMMAND"; 
			}
		}	
	}
	else
		feedback = (uint8_t*)"_ERROR_no_spp_key";

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_move(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	uint8_t* feedback = (uint8_t*)"";

	if(strcmp((void *)args[0][0], "spp") == 0)
	{
		if(!(stepper = device_manager_getStepper(args[0][1]))) // checks if set current device goes successfull, if no returns ERROR
			feedback = (uint8_t*)"_ERROR_invalid_spp_value";
		else
		{
			if(strcmp((void *)args[1][0], "stp") == 0)
			{
				uint8_t result = stepper_move(stepper, args[1][1]);
				if(!result)
					feedback = (uint8_t*)"_ERROR_move_by_0_steps";
				else
				{
					if(result == 1)
						feedback = (uint8_t*)"_VALID_COMMAND";
					else if(result == 9)
						feedback = (uint8_t*)"_ERROR_operation_not_allowed";
				}
					
			}
			else
				feedback = (uint8_t*)"_ERROR_no_stp_key";
		}
	}
	else
		feedback = (uint8_t*)"_ERROR_no_spp_key";
	
	free(args); // free memory allocated to args

	return feedback;
}

uint8_t *prepare_process(uint8_t ***args, uint8_t size) // opt=pro|spp=x|spd=40|spp=w|dir=1|spd=70
{
	uint8_t* feedback = (uint8_t*)"";

	if(strcmp((void *)args[0][0], "dir") == 0)
	{
		Stepper *x = NULL, *w = NULL;

		x = device_manager_getStepper((uint8_t*)"x");
		w = device_manager_getStepper((uint8_t*)"w");

		if(strcmp((void *)args[0][1], "0") != 0 && strcmp((void *)args[0][1], "1") != 0)
			feedback = (uint8_t*)"_ERROR_invalid_dir_value";
		else
		{	
			uint8_t dir;
			
			sscanf((void *)args[0][1], "%d", &dir);

			stepper_setDirection(w, dir);

			stepper_run(x);
			stepper_run(w);

			PROCESS_FORWARD = 1;

			feedback = (uint8_t*)"_VALID_COMMAND";
		}
	}
	else
		feedback = (uint8_t*)"_ERROR_no_dir_key";

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_intervention(uint8_t ***args, uint8_t size, uint8_t (*fun)(Stepper*))
{
	Stepper *stepper = NULL;
	uint8_t* feedback = (uint8_t*)"";

	if(strcmp((void *)args[0][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
	{
		if(strcmp((void *)args[0][1], "pro") == 0)
		{
			fun(device_manager_getStepper((uint8_t*)"x"));
			fun(device_manager_getStepper((uint8_t*)"w"));

			feedback = (uint8_t*)"_SUCCESS";
		}
		else if(strcmp((void *)args[0][1], "all") == 0)
		{
			fun(device_manager_getStepper((uint8_t*)"x"));
			fun(device_manager_getStepper((uint8_t*)"y"));
			fun(device_manager_getStepper((uint8_t*)"z"));
			fun(device_manager_getStepper((uint8_t*)"w"));

			feedback = (uint8_t*)"_SUCCESS";
		}
		else
		{
			if(!(stepper = device_manager_getStepper(args[0][1]))) // checks if set current device goes successfull, if no returns ERROR
				feedback = (uint8_t*)"_ERROR_invalid_spp_value";
			else
			{
				if(!fun(stepper))
					feedback = (uint8_t*)"_ERROR_operation_not_allowed";
				else
					feedback = (uint8_t*)"_SUCCESS";			
			}
		}
	}
	else 
		feedback = (uint8_t*)"_ERROR_no_spp_key";
	
	free(args); // frees memory allocated to args

	return feedback;
}

//#endif // STSTM32