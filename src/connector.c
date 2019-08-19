#include "connector.h"

#include <stdlib.h> // needed to use malloc, calloc, realloc
#include <string.h> // includes defintion of strtok function
#include <stddef.h> // includes NULL value

//#include "prepare_functions.h"

uint8_t ***connector_parse(uint8_t* dialog)
{
    uint8_t ***args = NULL, *param, *key, *value, size = 0;

	for (param = strtok((uint8_t*) dialog, "|"); param != NULL; param = strtok(NULL, "|"))
	{
		key = strtok_r(param, "=", &value);
		args = (uint8_t ***) realloc(args, (++size) * sizeof(uint8_t *));

		args[size-1] = (uint8_t **) malloc(2 * sizeof(uint8_t *));
        args[size-1][0] = (uint8_t *)malloc(connector_string_size(key) * sizeof(uint8_t));
        args[size-1][1] = (uint8_t *)malloc(connector_string_size(value) * sizeof(uint8_t));

		strcpy(args[size - 1][0], key);
		strcpy(args[size - 1][1], value);
	}

	//free(param);
	//free(key);
	//free(value);

	return args;
}

void connector_manage_data(uint8_t ***args, uint8_t size)
{
	//uint8_t *opt = args[0][1], size = connector_data_size(args);

	//memmove(args, args + 1, (--size) * sizeof(uint8_t *));

	//if(strcmp((void *)opt, "sth") == 0)
	//	prepare_turn(args, size);
}

uint8_t connector_string_size(uint8_t *string)
{
	uint8_t i = 0;

	while(string[i] != '\0')
		i++;

	return i;
}


