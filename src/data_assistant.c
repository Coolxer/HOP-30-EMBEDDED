#include "data_assistant.h"

#include <string.h>
#include <stdlib.h>

uint8_t *char_append(uint8_t *src, uint8_t ch)
{
	uint8_t s = strlen(src);
	
	uint8_t tmp[s + 1];
	tmp[0] = 0;

	strcpy(tmp, src);
	tmp[s] = ch;
	tmp[s + 1] = '\0';

	return strdup(tmp);
}

uint8_t *str_append(uint8_t *src, uint8_t *str)
{
	uint8_t s = strlen(src) + strlen(str);

	uint8_t tmp[s];
	tmp[0] = 0;

	strcat(tmp, src);
	strcat(tmp, str);
	tmp[s + 1] = '\0';

	return strdup(tmp);
}
