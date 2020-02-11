#include "data_assistant.h"

#include <string.h>
#include <stdlib.h>

uint8_t *char_append(uint8_t *src, uint8_t ch)
{
	uint8_t s = strlen((void *)src);
	
	uint8_t tmp[s + 1];
	tmp[0] = 0;

	strcpy((void *)tmp, (void *)src);
	tmp[s] = ch;
	tmp[s + 1] = '\0';

	return (uint8_t*)strdup((void*)tmp);
}

uint8_t *str_append(uint8_t *src, uint8_t *str)
{
	uint8_t s = strlen((void *)src) + strlen((void *)str) + 1;

	uint8_t tmp[s];
	tmp[0] = 0;

	strcat((void *)tmp, (void *)src);
	strcat((void *)tmp, (void *)str);
	tmp[s + 1] = '\0';

	return (uint8_t*)strdup((void *)tmp);
}
