#include "data_assistant.h"

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

uint8_t *charAppend(uint8_t *src, uint8_t ch)
{
	uint8_t s = stringLength(src); // read length of src string

	uint8_t tmp[s + 1]; // declare table with additional place for char
	tmp[0] = 0;			// clear table

	strcpy((void *)tmp, (void *)src); // copy src to new table
	tmp[s] = ch;					  // set char at the pre-last pos
	tmp[s + 1] = '\0';				  // set end of string

	return (uint8_t *)strdup((void *)tmp); // return new string
}

uint8_t *strAppend(uint8_t *src, uint8_t *str)
{
	uint8_t s = (uint8_t)(stringLength(src) + stringLength(str) + 1); // read length of src and str

	uint8_t tmp[s]; // declare table for keep 2 strings
	tmp[0] = 0;		// clear table

	strcat((void *)tmp, (void *)src); // copy src to new table
	strcat((void *)tmp, (void *)str); // copy str to new table
	tmp[s + 1] = '\0';				  // set end of string

	return (uint8_t *)strdup((void *)tmp); // return new string
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
