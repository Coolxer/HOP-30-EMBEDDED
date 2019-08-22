#include "data_assistant.h"

uint8_t data_string_size(uint8_t *string)
{
	uint8_t i = 0; // number of letters

	while(string[i] != '\0')
		i++;

	return i;
}

void data_build()
{
	uint8_t i;

	for(i = 0; i < DATA_SIZE; i++)
	{
		if(data[i] == '\0' || data[i] == ' ')
			data[i] = SPACE_FILLER;
	}

	data[DATA_SIZE] = '\0';
}

void data_cut()
{
	uint8_t i;

	for(i = 0; i < DATA_SIZE; i++)
		if(data[i] == SPACE_FILLER)
			data[i] = "";

	data[DATA_SIZE] = '\0';
}

void data_clear()
{
	uint8_t i;

	for(i = 0; i < DATA_SIZE ; i++)
		data[i] = 0;
}

uint8_t data_string_equals(uint8_t string[])
{
	return strcmp(data, string);
}