#include "data/assistant.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "null.h"

uint8_t stringLength(uint8_t *str)
{
	return (uint8_t)strlen((void *)str);
}

uint8_t stringEqual(uint8_t *str1, uint8_t *str2)
{
	if (strcmp((void *)str1, (void *)str2) == 0)
		return 1;

	return 0;
}

void clearString(uint8_t *src, uint8_t len)
{
	uint8_t i = 0;
	for (; i < len; i++)
		src[i] = EMPTY_CHARACTER;
}

uint8_t convertStrToBoolean(uint8_t *str)
{
	return stringEqual(str, (uint8_t *)"0") ? 0 : 1;
}

float convertStrToFloat(uint8_t *str)
{
	return strtof((void *)str, NULL);
}

uint8_t containsOnlyDigits(uint8_t *str)
{
	uint8_t i = 0;

	for (i = 0; i < stringLength(str); i++)
	{
		if (str[i] < 48 || str[i] > 57) // check if string contains only numbers
			return 0;
	}

	return 1;
}
