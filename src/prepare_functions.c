//#ifdef STSTM32

#include "prepare_functions.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "device_manager.h"

#include "data_assistant.h"

uint8_t *prepare_turn(uint8_t ***args, uint8_t size, uint8_t dt_size)
{
	uint8_t i, *feedback;

	feedback = (uint8_t *)malloc(dt_size * sizeof(uint8_t));

	data_clear(feedback, dt_size);

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // check if the selected string is "spp" (stepper)
		{
			if(!device_manager_set_current(args[i][1]))
				strcat(feedback, "_ERROR_invalid_stepper_name");
			else
			{
				if(!stepper_toggle())
					strcat(feedback, "_ERROR_toggle_not_worked");
			}	
		}
		else if (i == size - 1)
			strcat(feedback, "_ERROR_no_spp_key");
	}

	if(strcmp(feedback, "") == 0) // check if there are not errors = operation success
		strcpy(feedback, "_SUCCESS");

	free(args); // free memory allocated to args

	return feedback;
}

uint8_t *prepare_set(uint8_t ***args, uint8_t size, uint8_t dt_size)
{
	uint8_t i, *feedback, spp_cnt = 0, msp_cnt = 0;

	feedback = (uint8_t *)malloc(dt_size * sizeof(uint8_t));

	data_clear(feedback, dt_size);

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // check if the selected string is "spp" (stepper)
		{
			if(!device_manager_set_current(args[i][1]))
			{
				strcat(feedback, "_ERROR_invalid_stepper_name");
				continue;
			}

			spp_cnt++;
		}

		if(strcmp((void *)args[i][0], "msp") == 0)
		{
			if(!stepper_set_microstepping(args[i][1]))
				strcat(feedback, "_ERROR_set_microstepping_not_worked");

			msp_cnt++;
		}
	}

	if(spp_cnt == 0)
		strcat(feedback, "_ERROR_no_spp_param");
	
	if(msp_cnt == 0)
		strcat(feedback, "_ERROR_no_msp_param");

	if(spp_cnt > msp_cnt)
		strcat(feedback, "_ERROR_no_msp_key_for_spp");

	if(msp_cnt > spp_cnt)
		strcat(feedback, "_ERROR_no_spp_param_for_msp");

	if(strcmp(feedback, "") == 0) // check if there are not errors = operation success
		strcpy(feedback, "_SUCCESS");

	free(args); // free memory allocated to args

	return feedback;
}

uint8_t *prepare_home(uint8_t ***args, uint8_t size, uint8_t dt_size)
{
	uint8_t i, *feedback;
	float speed;

	feedback = (uint8_t *)malloc(dt_size * sizeof(uint8_t));

	data_clear(feedback, dt_size);

	if(strcmp((void *)args[0][0], "spd") != 0)
		return "_ERROR_no_home_speed_given";
	else
		speed = (float)atof(args[0][1]);

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // check if the selected string is "spp" (stepper)
		{
			if(!device_manager_set_current(args[i][1]))
				strcat(feedback, "_ERROR_invalid_stepper_name");
			else
			{
				stepper_set_speed(speed);
				if(!stepper_home())
					strcat(feedback, "_ERROR_home_not_worked");
			}	
		}
		else if (i == size - 1)
			strcat(feedback, "_ERROR_no_spp_key");
	}

	if(strcmp(feedback, "") == 0) // check if there are not errors = operation success
		strcpy(feedback, "_SUCCESS");

	free(args); // free memory allocated to args

	return feedback;
}

uint8_t *prepare_move(uint8_t ***args, uint8_t size, uint8_t dt_size)
{
	uint8_t i, *feedback;

	feedback = (uint8_t *)malloc(dt_size * sizeof(uint8_t));

	data_clear(feedback, dt_size);

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // check if the selected string is "spp" (stepper)
		{
			if(!device_manager_set_current(args[i][1]))
				strcat(feedback, "_ERROR_invalid_stepper_name");
			else
			{
				if(!stepper_toggle())
					strcat(feedback, "_ERROR_toggle_not_worked");
			}	
		}
		else if (i == size - 1)
			strcat(feedback, "_ERROR_no_spp_key");
	}

	if(strcmp(feedback, "") == 0) // check if there are not errors = operation success
		strcpy(feedback, "_SUCCESS");

	free(args); // free memory allocated to args

	return feedback;
}


//#endif // STSTM32