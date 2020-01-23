//#ifdef STSTM32

#include "prepare_functions.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "device_manager.h"

#include "data_assistant.h"

uint8_t *prepare_switch(uint8_t ***args, uint8_t size)
{
	free(feedback);

	for(i = 0; i < size ; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!device_manager_set_current(args[i][1])) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback_append("_ERROR_invalid_stepper_name");
				break;
			}
		}
		else if(strcmp((void *)args[i + 1][0], "stt") == 0)
		{
			if(device_manager_get_current())
			{
				if(!stepper_switch(args[i + 1][1]))
					feedback_append("_ERROR_invalid_state_given");

				device_manager_release_device():
			}
			else
			{
				feedback_append("_ERROR_no_spp_key");
				break;
			}	
		}
		else
		{
			feedback_append("_ERROR_unknown key");
			break;
		}

	if(strcmp(feedback, "") == 0) // checks if there are not errors = operation success
		feedback_append("_SUCCESS");

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_set(uint8_t ***args, uint8_t size)
{
	free(feedback);

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0)
		{
			if(!device_manager_set_current(args[i][1])) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback_append("_ERROR_invalid_stepper_name");
				break;
			}
		}
		else if (strcmp((void *)args[i][0], "msp") == 0)
		{
			if(device_manager_get_current())
			{
				if(!stepper_set_microstepping(args[i][1])
					feedback_append("_ERROR_invalid_combination");	
			}
			else
			{
				feedback_append("_ERROR_no_spp_key");
				break;
			}
			
		}
		else if (strcmp((void *)args[i][0], "spd") == )
		{
			if(device_manager_get_current())
				stepper_set_speed(args[i][1]);
			else
			{
				feedback_append("_ERROR_no_spp_key");
				break;
			}
		}
		else
		{
			feedback_append("_ERROR_unknown key");
			break;
		}
	}

	if(strcmp(feedback, "") == 0) // checks if there are not errors = operation success
		feedback_append("_SUCCESS");

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_home(uint8_t ***args, uint8_t size)
{
	free(feeback);

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!device_manager_set_current(args[i][1])) // checks if set current device goes successfull, if no returns ERROR
				feedback_append("_ERROR_invalid_stepper_name");
			else
				stepper_home() // homes selected stepper motor
		}
		else
		{
			feedback_append("_ERROR_unknown key");
			break;
		}
	}

	if(strcmp(feedback, "") == 0) // checks if there are not errors = operation success
		strcpy(feedback, "_SUCCESS");

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_move(uint8_t ***args, uint8_t size)
{
	free(feedback);

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0)
		{
			if(!device_manager_set_current(args[i][1])) // checks if set current device goes successfull, if no returns ERROR
			{
				feedback_append("_ERROR_invalid_stepper_name");
				break;
			}
		}
		else if (strcmp((void *)args[i][0], "stp") == 0)
		{
			if(device_manager_get_current())
				stepper_move(args[i][1])
			else
			{
				feedback_append("_ERROR_no_spp_key");
				break;
			}	
		}
		else
		{
			feedback_append("_ERROR_unknown key");
			break;
		}
	}

	if(strcmp(feedback, "") == 0) // check if there are not errors = operation success
		strcpy(feedback, "_SUCCESS");

	free(args); // free memory allocated to args

	return feedback;
}

void feedback_append(uint8_t* str)
{
	feedback = (uint8_t*)malloc(strlen(feedback) + strlen(str) + 1);
	strcat(feedback, str);
}


//#endif // STSTM32