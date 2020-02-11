#include "connector.h"

#include <stdlib.h> // needed to use malloc, calloc, realloc
#include <string.h> // includes defintion and use of strtok function
#include <stddef.h> // includes NULL value

#include "data_assistant.h"
#include "prepare_functions.h"
#include "stepper.h"

uint8_t *dialog_delimiter = (uint8_t*)"|"; // the dialog delimiter, that seprates 2 sentences; e.g. opt=mov|spp=x|
uint8_t *param_delimiter = (uint8_t*)"=";	// the param (sentence) delimiter, that seperate key and value of sentence; e.g. opt=mov

uint8_t records; // number of rows (key:value) of parsered dialog 

uint8_t ***connector_parse(uint8_t* dialog)
{
    uint8_t ***args = NULL, *param = NULL, *key = NULL, *value = NULL;

	records = 0; // number of records (rows) with 2 columns: key:value

	for (param = (uint8_t*)strtok((void *)dialog, (void *)dialog_delimiter); param != NULL; param = (uint8_t *)strtok(NULL, (void *)dialog_delimiter))
	{
		if(param[0] == '=' || strchr((void *)param, *param_delimiter) == NULL)
			break;

		//if(strchr(param, *param_delimiter) == NULL)
		//	continue;

		key = (uint8_t*)strtok_r((void *)param, (void *)param_delimiter, &value); // assigns key & values contents
		args = (uint8_t ***) realloc(args, (++records) * sizeof(uint8_t *)); // extends array by one row (2 columns)

		args[records - 1] = (uint8_t **) malloc(2 * sizeof(uint8_t *)); // reserves memory for one row with 2 columns
        args[records - 1][0] = (uint8_t *)malloc((sizeof(key) * 8) * sizeof(uint8_t)); // reserves memory for key column
        args[records - 1][1] = (uint8_t *)malloc((sizeof(value) * 8) * sizeof(uint8_t)); // reserves memory for value column

		strcpy((void*)args[records - 1][0], (void*)key); // copie  key string to the array
        strcpy((void*)args[records - 1][1], (void*)value); // copies value string to the array
	}

	return args; // returns 2d array of array of uint8_t
}

uint8_t *connector_manage(uint8_t ***args)
{
	uint8_t *opt;

	if(records < 1) // checks if no records detected!
		return (uint8_t*)"_ERROR_no_params";

	if(records == 1) // if there is only one record -> command incorrect
		return (uint8_t*)"_ERROR_one_param_only";

	if(records > 3)
		return (uint8_t*)"_ERROR_to_many_arguments";
		
	if(args != NULL && strcmp((void*)args[0][0], "opt") != 0) // if there is no "opt" key -> command incorrect
		return (uint8_t*)"_ERROR_no_opt_key";

	opt = args[0][1]; // gets first value, which means operation type
	
	memmove(args, args + 1, --(records) * sizeof(uint8_t *)); // moves the array one place forward (removes first row with opt type)

	/* checks operation (opt) mode and calls appropriate prepare_function */

	if(strcmp((void *)opt, "sth") == 0)
		return prepare_switch(args, records);
	else if(strcmp((void *)opt, "spd") == 0)
		return prepare_settings(args, records, (uint8_t*)"spd", stepper_setSpeed);
	else if(strcmp((void *)opt, "msp") == 0)
		return prepare_settings(args, records, (uint8_t*)"msp", stepper_setMicrostepping);
	else if(strcmp((void *)opt, "hom") == 0)
		return prepare_home(args, records);
	else if(strcmp((void *)opt, "mov") == 0)
		return prepare_move(args, records);
	else if(strcmp((void *)opt, "pro") == 0)
		return prepare_process(args, records);
	else if(strcmp((void *)opt, "pau") == 0)
		return prepare_intervention(args, records, stepper_pause);
	else if(strcmp((void *)opt, "res") == 0)
		return prepare_intervention(args, records, stepper_resume);
	else if(strcmp((void *)opt, "sto") == 0)
		return prepare_intervention(args, records, stepper_stop);
	else
		return (uint8_t*)"_ERROR:invalid_opt_value";
}



