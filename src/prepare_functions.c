//#ifdef STSTM32
#include "prepare_functions.h"

#include <string.h>
#include "device_manager.h"

uint8_t * prepare_turn(uint8_t ***args, uint8_t *size)
{
	uint8_t i, spp_cnt = 0, sth_cnt = 0, *fb;

	fb = (uint8_t*)malloc(64 * sizeof(uint8_t)); // reserve memory for feedback (same length as data) --- to change

	for(i = 0; i < *size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0) // check if the selected string is "spp" (stepper)
		{
			device_manager_set_current(args[i][1]);
			spp_cnt++;
		}
			
	    if(strcmp((void *)args[i][0], "sth") == 0) // check if the selected string is "sth" (switch)
		{
			stepper_enable(current, (bool)args[i][1]);
			sth_cnt++;
		}
	}

	free(args); // free memory allocated to args

	if(spp_cnt == 0) // check if there is no stepper keys
		strcpy(fb, "ERROR_no_spp_parameter");
	
	if(sth_cnt == 0) // check if there is no sth keys
		strcat(fb, "ERROR_no_sth_parameter");

	if(spp_cnt > sth_cnt) // check if there is more spp than sth keys
		strcat(fb, "ERROR_no_sth_parameter_for_spp");
	
	if(sth_cnt > spp_cnt) // check if there is more sth than spp keys
		strcat(fb, "ERROR_no_spp_parameter_for_sth");

	if(strcmp(fb, "") == 0) // check if there are not errors = operation success
		strcpy(fb, "SUCCESS");

	return fb; // return feedback
}

//#endif  // STSTM32