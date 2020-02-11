//#ifdef STSTM32

#include "prepare_functions.h"

#include <stdlib.h>
#include <string.h>

#include "data_assistant.h"

uint8_t *prepare_settings(uint8_t ***args, uint8_t size, uint8_t *key, uint8_t (*fun)(Stepper*, uint8_t*))
{
	Stepper *stepper = NULL;
	feedback = "";

	for(i = 0; i < size ; i += 2)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!(stepper = device_manager_getStepper(args[i][1]))) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback = "_ERROR_invalid_stepper_name";
				break;
			}
			else
			{
				if(strcmp((void *)args[i + 1][0], key) == 0)
				{
					if(!fun(stepper, args[i + 1][1]))
					{
						feedback = "_ERROR_invalid_";
						feedback = str_append(feedback, key);
						feedback = str_append(feedback, "_value");
						break;
					}
				}
				else
				{
					feedback ="_ERROR_unknown_key";
					break;
				}
			}
		}
		else 
		{
			feedback = "_ERROR_no_spp_key";
			break;
		}
	}

	if(strcmp(feedback, "") == 0)
		feedback = "_SUCCESS";
	
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
				feedback = "_ERROR_invalid_stepper_name";
				break;
			}
			else
				stepper_home(stepper); // homes selected stepper motor
		}
		else
		{
			feedback = "_ERROR_no_spp_key";
			break;
		}
	}

	if(strcmp(feedback, "") == 0) // checks if there are not errors = operation success
		feedback = "_VALID_COMMAND";

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
				feedback = "_ERROR_invalid_stepper_name";
				break;
			}
			else
			{
				if(strcmp((void *)args[i + 1][0], "stp") == 0)
				{
					if(!stepper_move(stepper, args[i + 1]))
					{
						feedback = feedback, "_ERROR_move_by_0_steps";
						break;
					}
				}
				else
				{
					feedback = "_ERROR_unknown_key";
					break;
				}
			}
		}
		else
		{
			feedback = feedback, "_ERROR_no_spp_key";
			break;
		}
	}

	if(strcmp(feedback, "") == 0)
		feedback = feedback, "_VALID_COMMAND";
	
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


		if(!stepper_setDirection(w, args[0][1])
		{
			feedback = "_ERROR_invalid_dir_value";
		}
		else
		{
			stepper_run(x);
			stepper_run(w);

			PROCESS_FORWARD = 1;
		}
	}
	else
		feedback = "_ERROR_no_dir_key";

	if(strcmp(feedback, "") == 0)
		feedback = "_VALID_COMMAND";	

	free(args); // frees memory allocated to args

	return feedback;
}

/*
uint8_t *prepare_intervention(uint8_t ***args, uint8_t size, void (*fun)(Stepper*, uint8_t*))
{
	Stepper *stepper = NULL;
	feedback = "";

	for(i = 0; i < size ; i += 2)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!(stepper = device_manager_getStepper(args[i][1]))) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback = "_ERROR_invalid_stepper_name";
				break;
			}
			else
			{
				if(strcmp((void *)args[i + 1][0], "mode") == 0)
					//stepper_stop(stepper, args[i + 1][1]);
					fun(stepper, args[i + 1][1]);
				else
				{
					feedback = "_ERROR_unknown_key";
					break;
				}
			}
		}
		else 
		{
			feedback = "_ERROR_no_spp_key";
			break;
		}
	}

	if(strcmp(feedback, "") == 0)
		feedback = "_SUCCESS";
	
	free(args); // frees memory allocated to args

	return feedback;
}
*/

uint8_t *prepare_intervention(uint8_t ***args, uint8_t size, void (*fun)(Stepper*, uint8_t*))
{
	Stepper *stepper = NULL;

	for(i = 0; i < size ; i += 2)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!(stepper = device_manager_getStepper(args[i][1]))) // checks if set current device goes successfull, if no returns ERROR
				return "_ERROR_invalid_stepper_name";
			else
			{
				if(strcmp((void *)args[i + 1][0], "mode") == 0)
					//stepper_stop(stepper, args[i + 1][1]);
					fun(stepper, args[i + 1][1]);
				else
					return "_ERROR_unknown_key";
			}
		}
		else 
			return "_ERROR_no_spp_key";
	}
	
	free(args); // frees memory allocated to args

	return "_SUCCESS";
}

//#endif // STSTM32