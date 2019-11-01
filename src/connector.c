#include "connector.h"

#include <stdlib.h> // needed to use malloc, calloc, realloc
#include <string.h> // includes defintion and use of strtok function
#include <stddef.h> // includes NULL value

#include "data_assistant.h"

uint8_t *dialog_delimiter = "|";
uint8_t *param_delimiter = "=";

uint8_t ***connector_parse(uint8_t* dialog)
{
    uint8_t ***args = NULL, *param = NULL, *key = NULL, *value = NULL;

	records = 0; // number of records (rows) with 2 columns: key:value

	for (param = strtok(dialog, dialog_delimiter); param != NULL; param = strtok(NULL, dialog_delimiter))
	{
		if(strchr(param, *param_delimiter) == NULL) // checks if there is NULL
			continue;

		key = strtok_r(param, param_delimiter, &value); // assigns key & values contents
		args = (uint8_t ***) realloc(args, (++records) * sizeof(uint8_t *)); // extends array by one row (2 columns)

		args[records-1] = (uint8_t **) malloc(2 * sizeof(uint8_t *)); // reserves memory for one row with 2 columns
        args[records-1][0] = (uint8_t *)malloc((sizeof(key) * 8) * sizeof(uint8_t)); // reserves memory for key column
        args[records-1][1] = (uint8_t *)malloc((sizeof(value) * 8) * sizeof(uint8_t)); // reserves memory for value column

		strcpy(args[records-1][0], key); // copie  key string to the array
        strcpy(args[records-1][1], value); // copies value string to the array
	}

	return args; // returns 2d array of array of uint8_t
}

uint8_t *connector_manage_data(uint8_t ***args, uint8_t dt_size)
{
	uint8_t *opt, *feedback;

	feedback = (uint8_t*)malloc(dt_size * sizeof(uint8_t)); // reserves memory for feedback message
	data_clear(feedback, dt_size); // clears feedback message

	if(args == NULL || records < 1) // checks if no records detected!
		return "_ERROR_no_params";

	if(records == 1) // if there is only one record -> command incorrect
		strcpy(feedback, "_ERROR:one_param_only");

	if(args != NULL && strcmp(args[0][0], "opt") != 0) // if there is no "opt" key -> command incorrect
	{
		strcat(feedback, "_ERROR:no_opt_key\0");
		return feedback;
	}	

	opt = args[0][1]; // gets first value, which means operation type
	
	memmove(args, args + 1, --(records) * sizeof(uint8_t *)); // moves the array one place forward (removes first row with opt type)

	/* checks operation (opt) mode and calls appropriate prepare_function */

	if(strcmp(opt, "sth") == 0)
		strcat(feedback, prepare_turn(args, records, dt_size));
	else if(strcmp(opt, "set") == 0)
		strcat(feedback, prepare_set(args, records, dt_size));
	else if(strcmp(opt, "hom") == 0)
		strcat(feedback, prepare_home(args, records, dt_size));
	else if(strcmp(opt, "mov") == 0)
		strcat(feedback, prepare_move(args, records, dt_size));
	else
		strcat(feedback, "_ERROR:invalid_opt_value");

	return feedback;
}



