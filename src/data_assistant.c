#include "data_assistant.h"

#include <string.h>

void data_fullfill(uint8_t dt[], uint8_t dt_size)
{
	uint8_t i;

	for(i = 0; i < dt_size; i++)
	{
		if(dt[i] == '\0' || dt[i] == ' ')
			dt[i] = SPACE_FILLER;
	}

	dt[dt_size] = '\0';
}

void data_crop(uint8_t dt[], uint8_t dt_size)
{
	uint8_t i;

	for(i = 0; i < dt_size; i++)
		if(dt[i] == SPACE_FILLER)
			dt[i] = 0;

	dt[dt_size] = '\0';
}

void data_clear(uint8_t dt[], uint8_t dt_size)
{
	uint8_t i;

	for(i = 0; i < dt_size ; i++)
		dt[i] = 0;
}
