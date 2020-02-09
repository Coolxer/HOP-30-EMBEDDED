//#ifdef STSTM32

#include "prepare_functions.h"

#include <stdlib.h>
#include <string.h>

#include "device_manager.h"
#include "data_assistant.h"

uint8_t *prepare_switch(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	feedback = "";

	for(i = 0; i < size ; i += 2)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!(stepper = device_manager_getStepper(args[i][1]))) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback = str_append(feedback, "_ERROR_invalid_stepper_name");
				break;
			}
			else
			{
				if(strcmp((void *)args[i + 1][0], "stt") == 0)
				{
					if(!stepper_switch(stepper, args[i + 1][1]))
					{
						feedback = str_append(feedback, "_ERROR_invalid_state_given");
						break;
					}		
				}
				else
				{
					feedback = str_append(feedback, "_ERROR_unknown_key");
					break;
				}
			}
		}
		else 
		{
			feedback = str_append(feedback, "_ERROR_no_spp_key");
			break;
		}
	}

	if(strcmp(feedback, "") == 0)
		feedback = str_append(feedback, "_SUCCESS");
	
	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_setSpeed(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	feedback = "";

	for(i = 0; i < size ; i += 2)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!(stepper = device_manager_getStepper(args[i][1]))) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback = str_append(feedback, "_ERROR_invalid_stepper_name");
				break;
			}
			else
			{
				if(strcmp((void *)args[i + 1][0], "spd") == 0)
				{
					if(!stepper_setSpeed(stepper, args[i + 1][1]))
					{
						feedback = str_append(feedback, "_ERROR_invalid_speed_given");
						break;
					}		
				}
				else
				{
					feedback = str_append(feedback, "_ERROR_unknown_key");
					break;
				}
			}
		}
		else 
		{
			feedback = str_append(feedback, "_ERROR_no_spp_key");
			break;
		}
	}

	if(strcmp(feedback, "") == 0)
		feedback = str_append(feedback, "_SUCCESS");
	
	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_setMicrostepping(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	feedback = "";

	for(i = 0; i < size ; i += 2)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!(stepper = device_manager_getStepper(args[i][1]))) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback = str_append(feedback, "_ERROR_invalid_stepper_name");
				break;
			}
			else
			{
				if(strcmp((void *)args[i + 1][0], "spd") == 0)
				{
					if(!stepper_setMicrostepping(stepper, args[i + 1][1]))
					{
						feedback = str_append(feedback, "_ERROR_invalid_combination_given");
						break;
					}		
				}
				else
				{
					feedback = str_append(feedback, "_ERROR_unknown_key");
					break;
				}
			}
		}
		else 
		{
			feedback = str_append(feedback, "_ERROR_no_spp_key");
			break;
		}
	}

	if(strcmp(feedback, "") == 0)
		feedback = str_append(feedback, "_SUCCESS");
	
	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_home(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	feedback = "";

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!(stepper = device_manager_getStepper(args[i][1]))) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback = str_append(feedback, "_ERROR_invalid_stepper_name");
				break;
			}
			else
				stepper_home(stepper); // homes selected stepper motor
		}
		else
		{
			feedback = str_append(feedback, "_ERROR_no_spp_key");
			break;
		}
	}

	if(strcmp(feedback, "") == 0) // checks if there are not errors = operation success
		feedback = str_append(feedback, "_SUCCESS");

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_move(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	feedback = "";

	for(i = 0; i < size; i += 2)
	{
		if(strcmp((void *)args[i][0], "spp") == 0)
		{
			if(!(stepper = device_manager_getStepper(args[i][1]))) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback = str_append(feedback, "_ERROR_invalid_stepper_name");
				break;
			}
			else
			{
				if(strcmp((void *)args[i + 1][0], "stp") == 0)
				{
					if(!stepper_move(stepper, args[i + 1]))
					{
						feedback = str_append(feedback, "_ERROR_move_by_0_steps");
						break;
					}
				}
				else
				{
					feedback = str_append(feedback, "_ERROR_unknown_key");
					break;
				}
			}
		}
		else
		{
			feedback = str_append(feedback, "_ERROR_no_spp_key");
			break;
		}
	}

	if(strcmp(feedback, "") == 0)
		feedback = str_append(feedback, "_SUCCESS");
	
	free(args); // free memory allocated to args

	return feedback;
}

uint8_t *prepare_process(uint8_t ***args, uint8_t size) // opt=pro|spp=x|spd=40|spp=w|dir=1|spd=70
{
	feedback = "";

	if(strcmp((void *)args[0][0], "dir") == 0)
	{
		Stepper *x = NULL, *w = NULL;

		x = device_manager_getStepper("x");
		w = device_manager_getStepper("w");

		stepper_setDirection(w, args[0][1]);
		
		stepper_run(x);
		stepper_run(w);

		PROCESS_FORWARD = 1;

		feedback = str_append(feedback, "_SUCCESS");
	}
	else
		feedback = str_append(feedback, "_ERROR_no_dir_key");

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_pause(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	feedback = "";

	for(i = 0; i < size ; i += 2)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!(stepper = device_manager_getStepper(args[i][1]))) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback = str_append(feedback, "_ERROR_invalid_stepper_name");
				break;
			}
			else
			{
				if(strcmp((void *)args[i + 1][0], "mode") == 0)
					stepper_pause(stepper, args[i + 1][1]);
				else
				{
					feedback = str_append(feedback, "_ERROR_unknown_key");
					break;
				}
			}
		}
		else 
		{
			feedback = str_append(feedback, "_ERROR_no_spp_key");
			break;
		}
	}

	if(strcmp(feedback, "") == 0)
		feedback = str_append(feedback, "_SUCCESS");
	
	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_resume(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	feedback = "";

	for(i = 0; i < size ; i += 2)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!(stepper = device_manager_getStepper(args[i][1]))) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback = str_append(feedback, "_ERROR_invalid_stepper_name");
				break;
			}
			else
			{
				if(strcmp((void *)args[i + 1][0], "mode") == 0)
					stepper_resume(stepper, args[i + 1][1]);
				else
				{
					feedback = str_append(feedback, "_ERROR_unknown_key");
					break;
				}
			}
		}
		else 
		{
			feedback = str_append(feedback, "_ERROR_no_spp_key");
			break;
		}
	}

	if(strcmp(feedback, "") == 0)
		feedback = str_append(feedback, "_SUCCESS");
	
	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_stop(uint8_t ***args, uint8_t size)
{
	Stepper *stepper = NULL;
	feedback = "";

	for(i = 0; i < size ; i += 2)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!(stepper = device_manager_getStepper(args[i][1]))) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback = str_append(feedback, "_ERROR_invalid_stepper_name");
				break;
			}
			else
			{
				if(strcmp((void *)args[i + 1][0], "mode") == 0)
					stepper_stop(stepper, args[i + 1][1]);
				else
				{
					feedback = str_append(feedback, "_ERROR_unknown_key");
					break;
				}
			}
		}
		else 
		{
			feedback = str_append(feedback, "_ERROR_no_spp_key");
			break;
		}
	}

	if(strcmp(feedback, "") == 0)
		feedback = str_append(feedback, "_SUCCESS");
	
	free(args); // frees memory allocated to args

	return feedback;
}

//#endif // STSTM32