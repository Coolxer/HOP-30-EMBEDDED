#ifdef STSTM32
#include "prepare_functions.h"

#include <string.h>
#include "device_manager.h"

uint8_t * prepare_turn(uint8_t ***args, uint8_t *size)
{
	uint8_t i, spp_cnt = 0, sth_cnt = 0, *fb;

	for(i = 0; i < *size; i++)
	{
		if(strcmp((void *)args[i][0], "spp") == 0)
		{
			device_manager_set_current(args[i][1]);
			spp_cnt++;
		}
			
	    if(strcmp((void *)args[i][0], "sth") == 0)
		{
			stepper_enable(current, (bool)args[i][1]);
			sth_cnt++;
		}
	}

	if(spp_cnt == 0)
		strcpy(fb, "ERROR_no_spp_parameter");
	
	if(sth_cnt == 0)
		strcat(fb, "ERROR_no_sth_parameter");

	if((spp_cnt > 1) && spp_cnt > sth_cnt)
		strcat(fb, "ERROR_no_sth_parameter_for_spp");
	
	if((sth_cnt > 1) && sth_cnt > spp_cnt)
		strcat(fb, "ERROR_no_s[[_parameter_for_sth");

	return fb;
}

#endif // STSTM32