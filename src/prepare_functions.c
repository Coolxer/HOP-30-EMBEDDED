#include "prepare_functions.h"

void prepare_turn(uint8_t ***args, uint8_t *size)
{
	uint8_t i;

	for(i = 0; i < *size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0)
			device_manager_set_current(args[i][1]);

	    if(strcmp((void *)args[i][0], "sth") == 0)
	    	stepper_enable(current, (bool)args[i][1]);
	}
}