#include "data_assistant.h"

#include <string.h>
#include <stdlib.h>

uint8_t *char_append(uint8_t *src, uint8_t ch)
{
	int s = strlen(src);
	
	char tmp[s + 1];
	
	strcpy(tmp, src);
	tmp[s] = ch;
	tmp[s+1] = '\0';

	return strdup(tmp);
}

uint8_t *str_append(uint8_t *src, uint8_t *str)
{
	int s = strlen(src) + strlen(str);

	char tmp[s]; 
	strcpy(tmp, src);
	strcpy(tmp, str);
	tmp[s + 1] = '\0';

	return strdup(tmp);
}
