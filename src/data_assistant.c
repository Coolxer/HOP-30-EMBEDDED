#include "data_assistant.h"

#include <string.h>
#include <stdlib.h>

uint8_t* char_append(uint8_t *src, uint8_t ch)
{
	int s = strlen(src);
	uint8_t *tmp = (uint8_t*)malloc(s + 1); // not sure if there should be (s + 2) -> ?? SHOULD I reserve memory for '\0'
	strcpy(tmp, src);
	tmp[s] = ch;
	tmp[s+1] = '\0';

	return tmp;
}

uint8_t* str_append(uint8_t *src, uint8_t* str)
{
	int s = strlen(src) + strlen(str);
	uint8_t *tmp = (uint8_t*)malloc(s); // not sure if there should be (s + 2) -> ?? SHOULD I reserve memory for '\0'
	strcpy(tmp, src);
	strcpy(tmp, str);
	tmp[s + 1] = '\0';

	return tmp;
}

void data_clear(uint8_t dt[], uint8_t dt_size)
{
	uint8_t i;

	for(i = 0; i < dt_size ; i++)
		dt[i] = 0;
}
