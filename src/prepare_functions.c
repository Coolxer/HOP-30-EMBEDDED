//#ifdef STSTM32

#include "prepare_functions.h"

#include <stdlib.h>
#include <string.h>

#include "device_manager.h"
#include "data_assistant.h"

uint8_t *prepare_switch(uint8_t ***args, uint8_t size)
{
	uint8_t steppers = 0, states = 0;
	feedback = "";

	for(i = 0; i < size ; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!device_manager_set_current(args[i][1])) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback = str_append(feedback, "_ERROR_invalid_stepper_name");
				break;
			}
			steppers++;
		}
		else if(strcmp((void *)args[i][0], "stt") == 0)
		{
			if(device_manager_get_current())
			{
				if(!stepper_switch(args[i][1]))
					feedback = str_append(feedback, "_ERROR_invalid_state_given");
			}
			else
			{
				feedback = str_append(feedback, "_ERROR_no_spp_key");
				break;
			}
			states++;
		}
		else
		{
			feedback = str_append(feedback, "_ERROR_unknown key");
			break;
		}
	}

	if((strcmp(feedback, "") == 0) && (steppers == states)) // checks if there are not errors = operation success
		feedback = str_append(feedback, "_SUCCESS");
	else
	{
		if(steppers < states)
			feedback = str_append(feedback, "_ERROR_no_spp_key");
		else if(steppers > states)
			feedback = str_append(feedback, "_ERROR_no_stt_key");
	}
	
	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_set(uint8_t ***args, uint8_t size)
{
	uint8_t steppers = 0, settings = 0;
	feedback = "";

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0)
		{
			if(!device_manager_set_current(args[i][1])) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback = str_append(feedback, "_ERROR_invalid_stepper_name");
				break;
			}
			steppers++;
		}
		else if (strcmp((void *)args[i][0], "msp") == 0)
		{
			if(device_manager_get_current())
			{
				if(!stepper_set_microstepping(args[i][1]))
					feedback = str_append(feedback, "_ERROR_invalid_combination");	
			}
			else
			{
				feedback = str_append(feedback, "_ERROR_no_spp_key");
				break;
			}
			settings++;
		}
		else if (strcmp((void *)args[i][0], "spd") == 0)
		{
			if(device_manager_get_current())
				stepper_set_speed(args[i][1]);
			else
			{
				feedback = str_append(feedback, "_ERROR_no_spp_key");
				break;
			}
			settings++;
		}
		else
		{
			feedback = str_append(feedback, "_ERROR_unknown key");
			break;
		}
	}

	if((strcmp(feedback, "") == 0) && (settings >= steppers)) // checks if there are not errors = operation success
		feedback = str_append(feedback, "_SUCCESS");
	else if (settings < steppers)
		feedback = str_append(feedback, "_ERROR_no_setting_given");

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_home(uint8_t ***args, uint8_t size)
{
	feedback = "";

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!device_manager_set_current(args[i][1])) // checks if set current device goes successfull, if no returns ERROR
				feedback = str_append(feedback, "_ERROR_invalid_stepper_name");
			else
				stepper_home(); // homes selected stepper motor
		}
		else
		{
			feedback = str_append(feedback, "_ERROR_unknown key");
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
	uint8_t steppers = 0, steps = 0;
	feedback = "";

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0)
		{
			if(!device_manager_set_current(args[i][1])) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback = str_append(feedback, "_ERROR_invalid_stepper_name");
				break;
			}
			steppers++;
		}
		else if (strcmp((void *)args[i][0], "stp") == 0)
		{
			if(device_manager_get_current())
				stepper_move(args[i][1]);
			else
			{
				feedback = str_append(feedback, "_ERROR_no_spp_key");
				break;
			}	
			steps++;
		}
		else
		{
			feedback = str_append(feedback, "_ERROR_unknown key");
			break;
		}
	}

	if((strcmp(feedback, "") == 0) && (steppers == steps)) // check if there are not errors = operation success
		feedback = str_append(feedback, "_SUCCESS");
	else
	{
		if(steppers < steps)
			feedback = str_append(feedback, "_ERROR_no_spp_key");
		else if(steppers > steps)
			feedback = str_append(feedback, "_ERROR_no_stp_key");
		
	}
	
	free(args); // free memory allocated to args

	return feedback;
}


//#endif // STSTM32