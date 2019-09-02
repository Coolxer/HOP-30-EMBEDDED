//#ifdef STSTM32
#include "prepare_functions.h"

#include <stdlib.h>
#include <string.h>

#include "device_manager.h"

#include "data_assistant.h"

uint8_t *prepare_turn(uint8_t ***args, uint8_t size, uint8_t dt_size)
{
	uint8_t i, spp_cnt = 0, sth_cnt = 0, *feedback;

	feedback = (uint8_t *)malloc(dt_size * sizeof(uint8_t));

	data_clear(feedback, dt_size);

	for(i = 0; i < size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // check if the selected string is "spp" (stepper)
		{
			device_manager_set_current(args[i][1]);
			spp_cnt++;
		}
			
	    if(strcmp((void *)args[i][0], "stt") == 0) // check if the selected string is "sth" (switch)
		{
			stepper_enable(device_manager_current(), args[i][1]);
			sth_cnt++;
		}
	}

	if(spp_cnt == 0) // check if there is no stepper keys
		strcpy(feedback, "_ERROR_no_spp_param");
	
	if(sth_cnt == 0) // check if there is no sth keys
		strcat(feedback, "_ERROR_no_sth_parameter");

	if(spp_cnt > sth_cnt) // check if there is more spp than sth keys
		strcat(feedback, "_ERROR_no_sth_parameter_for_spp");
	
	if(sth_cnt > spp_cnt) // check if there is more sth than spp keys
		strcpy(feedback, "_ERROR_no_spp_parameter_for_sth");

	if(strcmp(feedback, "") == 0) // check if there are not errors = operation success
		strcpy(feedback, "_SUCCESS");

	//strcat(feedback, '\0');

	free(args); // free memory allocated to args

	return feedback;
}

//#endif // STSTM32