#include "connector.h"

#include <stdlib.h> // needed to use malloc, calloc, realloc
#include <string.h> // includes defintion and use of strtok function
#include <stddef.h> // includes NULL value

#include "data_assistant.h"

uint8_t ***connector_parse(uint8_t* dialog)
{
    uint8_t ***args = NULL, *param, *key, *value;

	records = 0;

	for (param = strtok((uint8_t*)dialog, DIALOG_DELIMITER); param != NULL; param = strtok(NULL, DIALOG_DELIMITER))
	{
		key = strtok_r(param, PARAM_DELIMITER, &value); // assign key & values contents
		args = (uint8_t ***) realloc(args, (++records) * sizeof(uint8_t *)); // extend array by one row (2 columns)

		args[records-1] = (uint8_t **) malloc(2 * sizeof(uint8_t *)); // reserve memory for one row with 2 columns
        args[records-1][0] = (uint8_t *)malloc((sizeof(key) * 8) * sizeof(uint8_t)); // reserve memory for key column
        args[records-1][1] = (uint8_t *)malloc((sizeof(value) * 8) * sizeof(uint8_t)); // reserve memory for value column

		strcpy(args[records-1][0], key);
        strcpy(args[records-1][1], value);
	}

	return args; // return 2d array of array of uint8_t
}

uint8_t *connector_manage_data(uint8_t ***args, uint8_t dt_size)
{
	uint8_t *opt, *feedback;

	feedback = (uint8_t*)malloc(dt_size * sizeof(uint8_t));
	data_clear(feedback, dt_size);

	if(args == NULL || records < 1) // no records detected!
		return "_ERROR_no_params\0";

	if(records == 1) // if there is only one record -> command incorrect
		strcpy(feedback, "_ERROR:one_param_only");

	if(args != NULL && strcmp(args[0][0], "opt") != 0) // if there is no "opt" key -> command incorrect
	{
		strcat(feedback, "_ERROR:no_opt_key\0");
		return feedback;
	}	

	opt = args[0][1]; // get first value, which means operation type
	
	memmove(args, args + 1, --(records) * sizeof(uint8_t *)); // move the array one place forward (removes first row with opt type)

	if(strcmp(opt, "sth") == 0)
		strcat(feedback, prepare_turn(args, records, dt_size));
	else
		strcat(feedback, "_ERROR:invalid_opt_value");

	//strcat(feedback, '\0');

	return feedback;
}



