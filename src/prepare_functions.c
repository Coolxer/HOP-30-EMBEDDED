#include "prepare_functions.h"

void prepare_steppers()
{
    stepper_init(&s1, "s1", 5, 6, 7, 8, 9, 10, 11);
    stepper_init(&s2, "s2", 12, 13, 14, 15, 16, 17, 18);
}

void prepare_turn(uint8_t ***args, uint8_t *size)
{
	uint8_t i;

	for(i = 0; i < *size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0)
	    {
			if(strcmp((const char *) args[i][1], "s1") == 0)
				current = &s1;
	        else
	        	current = &s2;
	    }

	    if(strcmp((void *)args[i][0], "sth") == 0)
	    	stepper_enable(current, (bool)args[i][1]);
	}
}