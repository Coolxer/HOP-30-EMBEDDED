#include "data_assistant.h"

#include <string.h>

uint8_t data_length(uint8_t *dt)
{
	uint8_t i = 0; // number of letters

	while(dt[i] != '\0')
		i++;

	return i;
}
                  
uint8_t data_size(uint8_t *dt)
{
	return sizeof(dt) * 8; 
}

void data_build(uint8_t *dt)
{
	uint8_t i, size;
	size = data_size(dt);

	for(i = 0; i < size; i++)
	{
		if(dt[i] == '\0' || dt[i] == ' ')
			dt[i] = SPACE_FILLER;
	}

	dt[size] = '\0';
}

void data_cut(uint8_t *dt)
{
	uint8_t i, size;
	size = data_size(dt);

	for(i = 0; i < size; i++)
		if(dt[i] == SPACE_FILLER)
			dt[i] = 0;

	dt[size] = '\0';
}

void data_clear(uint8_t *dt)
{
	uint8_t i, size;
	size = data_size(dt);

	for(i = 0; i < size ; i++)
		dt[i] = 0;
}

uint8_t data_equal(uint8_t *s1, uint8_t *s2)
{
	return strcmp(s1, s2);
}