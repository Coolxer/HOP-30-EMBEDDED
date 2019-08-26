#include "connector.h"

#include <stdlib.h> // needed to use malloc, calloc, realloc
#include <string.h> // includes defintion and use of strtok function
#include <stddef.h> // includes NULL value

#include "data_assistant.h"

uint8_t ***connector_parse(uint8_t *dt, uint8_t *args_size)
{
    uint8_t ***args = NULL, *param, *key, *value;

	for (param = strtok((uint8_t*) dt, DIALOG_DELIMITER); param != NULL; param = strtok(NULL, DIALOG_DELIMITER))
	{
		key = strtok_r(param, PARAM_DELIMITER, &value); // assign key & values contents
		args = (uint8_t ***) realloc(args, ++(*args_size) * sizeof(uint8_t *)); // extend array by one row (2 columns)

		args[*args_size-1] = (uint8_t **) malloc(2 * sizeof(uint8_t *)); // reserve memory for one row with 2 columns
        args[*args_size-1][0] = (uint8_t *)malloc(data_size(key) * sizeof(uint8_t)); // reserve memory for key column
        args[*args_size-1][1] = (uint8_t *)malloc(data_size(value) * sizeof(uint8_t)); // reserve memory for value column

		args[*args_size - 1][0] = key; // fill in key column
		args[*args_size - 1][1] = value; // fill in value column
	}

	return args; // return 2d array of array of uint8_t
}

uint8_t *connector_manage_data(uint8_t ***args, uint8_t* args_size)
{
	uint8_t *opt, *fb; //operation type and feedback message

	fb = (uint8_t*)malloc(64 * sizeof(uint8_t)); // reserve memory for feedback (same length as data) --- to change

	if(args == NULL || *args_size < 1) // no records detected!
	{
		strcpy(fb, "_ERROR_no_params");
		return fb;
	}
		
	if(*args_size == 1) // if there is only one record or less -> command incorrect
		strcat(fb, "_ERROR:one_param_only");
		
	if(args != NULL && strcmp(args[0][0], "opt") != 0) // if there is no "opt" key -> command incorrect
	{
		strcat(fb, "_ERROR:no_opt_key");
		return fb;
	}	

	opt = args[0][1], // get first value, which means operation type
	
	memmove(args, args + 1, --(*args_size) * sizeof(uint8_t *)); // move the array one place forward (removes first row with opt type)

	if(data_equal(opt, "sth"))
		fb = prepare_turn(args, args_size);
	else
		strcat(fb, "_ERROR:invalid_opt_value");
	
	return fb; // return feedback
}

uint8_t *connector_process(uint8_t *dt)
{
	uint8_t size = 0, *feedback; // number of records [key, value]

	feedback = connector_manage_data(connector_parse(dt, &size), &size);

	data_build(feedback); 

	return feedback;
}


