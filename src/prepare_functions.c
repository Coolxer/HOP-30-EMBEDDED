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
				if(!stepper_toggle(device_manager_current()))
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