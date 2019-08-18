#include "connector.h"

//#include "prepare_functions.h"

uint8_t ***connector_parse(uint8_t *dialog)
{
	uint8_t *param = NULL, *key = NULL, *value = NULL, ***args = NULL, size = 0;

	for(param = (uint8_t *)strtok((void *) dialog, DIALOG_DELIMITER); param != NULL; param = (uint8_t *)strtok(NULL, DIALOG_DELIMITER))
	{
		key = (uint8_t *)strtok_r((void *)param, PARAM_DELIMITER, (void*)value);
		args = (uint8_t ***) realloc (args, (++size) * sizeof(uint8_t *));

		args[size - 1] = (uint8_t **) malloc (2 * sizeof(uint8_t * ));
		args[size - 1][0] = (uint8_t *) malloc(connector_string_size(key)+ 1);
		args[size - 1][1] = (uint8_t *) malloc(connector_string_size(key) + 1);

		strcpy(args[size-1][0], key);
        strcpy(args[size-1][1], value);	
	}

    free(param);
	free(key);
	free(value);

	return args;
}

void connector_manage_data(uint8_t ***args)
{
	uint8_t *opt = args[0][1], size = connector_data_size(args);

	memmove(args, args + 1, (--size) * sizeof(uint8_t *));

	if(strcmp((void *)opt, "sth") == 0)
		prepare_turn(args, size);
}

uint8_t connector_string_size(uint8_t *string)
{
	uint8_t i = 0;

	while(i != '\0')
		i++;

	return i;
}

uint8_t connector_data_size(uint8_t ***args)
{
	return sizeof(args)/sizeof(uint8_t *);
}

