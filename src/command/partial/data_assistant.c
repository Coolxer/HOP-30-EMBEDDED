#include "command/partial/data_assistant.h"

#include <string.h>
#include <stdlib.h>

uint8_t *char_append(uint8_t *src, uint8_t ch)
{
	uint8_t s = strlen((void *)src); // read length of src string

	uint8_t tmp[s + 1]; // declare table with additional place for char
	tmp[0] = 0;			// clear table

	strcpy((void *)tmp, (void *)src); // copy src to new table
	tmp[s] = ch;					  // set char at the pre-last pos
	tmp[s + 1] = '\0';				  // set end of string

	return (uint8_t *)strdup((void *)tmp); // return new string
}

uint8_t *str_append(uint8_t *src, uint8_t *str)
{
	uint8_t s = strlen((void *)src) + strlen((void *)str) + 1; // read length of src and str

	uint8_t tmp[s]; // declare table for keep 2 strings
	tmp[0] = 0;		// clear table

	strcat((void *)tmp, (void *)src); // copy src to new table
	strcat((void *)tmp, (void *)str); // copy str to new table
	tmp[s + 1] = '\0';				  // set end of string

	return (uint8_t *)strdup((void *)tmp); // return new string
}