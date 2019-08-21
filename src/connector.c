#include "connector.h"

#include <stdlib.h> // needed to use malloc, calloc, realloc
#include <string.h> // includes defintion and use of strtok function
#include <stddef.h> // includes NULL value

//#include "prepare_functions.h"

uint8_t ***connector_parse(uint8_t* dialog, uint8_t* size)
{
    uint8_t ***args = NULL, *param, *key, *value;

	for (param = strtok((uint8_t*) dialog, DIALOG_DELIMITER); param != NULL; param = strtok(NULL, DIALOG_DELIMITER))
	{
		key = strtok_r(param, PARAM_DELIMITER, &value);
		args = (uint8_t ***) realloc(args, ++(*size) * sizeof(uint8_t *));

		args[*size-1] = (uint8_t **) malloc(2 * sizeof(uint8_t *));
        args[*size-1][0] = (uint8_t *)malloc(connector_string_size(key) * sizeof(uint8_t));
        args[*size-1][1] = (uint8_t *)malloc(connector_string_size(value) * sizeof(uint8_t));

		args[*size - 1][0] = key;
		args[*size - 1][1] = value;
	}

	if((*size) == 1) // if there is only one record -> command incorrect
	{
		strcpy(message, "ERROR:one_parameter_only");
		return NULL;
	}

	if(args != NULL && strcmp(args[0][0], "opt") != 0) // if there is no "opt" key -> command incorrect
	{
		strcpy(message, "ERROR:no_opt_key");
		return NULL;
	}

	return args;
}

void connector_manage_data(uint8_t ***args, uint8_t* size)
{
	uint8_t *opt;

	if(args == NULL)
		return;

	opt = args[0][1], // get first value, which means operation type
	
	memmove(args, args + 1, --(*size) * sizeof(uint8_t *)); // move the array one place forward (removes first row with opt type)

	if(strcmp((void *)opt, "sth") == 0){}
		//prepare_turn(args, size);
	else
		strcpy(message, "ERROR:invalid_opt_value");
	
}

uint8_t connector_string_size(uint8_t *string)
{
	uint8_t i = 0; // number of letters

	while(string[i] != '\0')
		i++;

	return i;
}

uint8_t *connector_start(uint8_t *dialog)
{
	uint8_t size = 0; // number of records
	strcpy(message, ""); // reset message

	connector_manage_data(connector_parse(dialog, &size), &size);
}

uint8_t *connector_build(uint8_t *message)
{
	uint
}


