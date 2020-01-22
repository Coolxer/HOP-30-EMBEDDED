//#ifdef STSTM32

#include "prepare_functions.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "device_manager.h"

#include "data_assistant.h"

uint8_t *prepare_switch(uint8_t ***args, uint8_t size, uint8_t dt_size)
{
	uint8_t i, *feedback;

	feedback = (uint8_t *)malloc(dt_size * sizeof(uint8_t)); // reserves memory for feedback message

	data_clear(feedback, dt_size); // clears feedback message

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!device_manager_set_current(args[i][1])) // checks if set curent device goes successfull, if no returns ERROR
				strcat(feedback, "_ERROR_invalid_stepper_name");
			else // if successfully selected current device
			{
				if(strcmp((void *)args[i + 1][0], "stt") == 0)
				{
					if(!stepper_switch(args[i+1][1])) // toggles stepper motor, if failed returns ERROR
						strcat(feedback, "_ERROR_switch_not_worked");
				}
				else
					strcat(feedback, "_ERROR_no_stt_key");
			}	
		}
		else if (i == size - 1) // checks if we are on last iteration and the key is not equals to spp
			strcat(feedback, "_ERROR_no_spp_key");
	}

	if(strcmp(feedback, "") == 0) // checks if there are not errors = operation success
		strcpy(feedback, "_SUCCESS");

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_set(uint8_t ***args, uint8_t size, uint8_t dt_size)
{
	uint8_t i, *feedback, spp_cnt = 0, msp_cnt = 0;

	// spp_cnt is number of spp keys in command
	// msp_cnt is number of msp keys in command
	// spp_cnt should be equals to msp_cnt, because then the command is correct

	feedback = (uint8_t *)malloc(dt_size * sizeof(uint8_t)); // reserves memory for feedback message

	data_clear(feedback, dt_size); // clears feedback message

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!device_manager_set_current(args[i][1])) // checks if set curent device goes successfull, if no returns ERROR
			{
				strcat(feedback, "_ERROR_invalid_stepper_name");
				continue;
			}

			spp_cnt++;
		}

		if(strcmp((void *)args[i][0], "msp") == 0) // checks if the selected string is "msp" (microstepping)
		{
			if(!stepper_set_microstepping(args[i][1])) // sets stepper microstepping, if failed returns ERROR
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

	if(strcmp(feedback, "") == 0) // checks if there are not errors = operation success
		strcpy(feedback, "_SUCCESS");

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_home(uint8_t ***args, uint8_t size, uint8_t dt_size)
{
	uint8_t i, *feedback;
	float speed;

	feedback = (uint8_t *)malloc(dt_size * sizeof(uint8_t)); // reserves memory for feedback message

	data_clear(feedback, dt_size); // clears feedback message

	if(strcmp((void *)args[0][0], "spd") != 0) // check sif the first given key is spd, if no the command cannot be done (no speed given)
		return "_ERROR_no_home_speed_given";
	else
		speed = (float)atof(args[0][1]);

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // checks if the selected string is "spp" (stepper)
		{
			if(!device_manager_set_current(args[i][1])) // checks if set curent device goes successfull, if no returns ERROR
				strcat(feedback, "_ERROR_invalid_stepper_name");
			else
			{
				stepper_set_speed(speed); // sets stepper motor speed
				if(!stepper_home()) // homes selected stepper motor, if failed return ERROR
					strcat(feedback, "_ERROR_home_not_worked");
			}	
		}
		else if (i == size - 1) // checks if we are on last iteration and the key is not equals to spp
			strcat(feedback, "_ERROR_no_spp_key");
	}

	if(strcmp(feedback, "") == 0) // checks if there are not errors = operation success
		strcpy(feedback, "_SUCCESS");

	free(args); // frees memory allocated to args

	return feedback;
}

uint8_t *prepare_move(uint8_t ***args, uint8_t size, uint8_t dt_size)
{
	uint8_t i, *feedback;

	feedback = (uint8_t *)malloc(dt_size * sizeof(uint8_t)); // reserves memory for feedback message

	data_clear(feedback, dt_size); // clears feedback message

	for(i = 0; i < size; i++)
	{

	}

	if(strcmp(feedback, "") == 0) // check if there are not errors = operation success
		strcpy(feedback, "_SUCCESS");

	free(args); // free memory allocated to args

	return feedback;
}


//#endif // STSTM32