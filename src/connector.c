#include "connector.h"

#include <stddef.h> // includes NULL value
#include <string.h> // includes defintion and use of strtok function
#include <stdlib.h> // needed to use malloc, calloc, realloc

#include "command/cmd_builder.h"
#include "prepare_function.h"

#include "stepper/partial/stepper_intervention.h"

uint8_t *dialog_delimiter = (uint8_t *)"|"; // the dialog delimiter, that seprates 2 sentences; e.g. opt=mov|spp=x|
uint8_t *param_delimiter = (uint8_t *)"=";	// the param (sentence) delimiter, that seperate key and value of sentence; e.g. opt=mov

uint8_t records; // number of rows (key:value) of parsered dialog

uint8_t ***connector_parse(uint8_t *dialog)
{
	uint8_t ***args = NULL, *param = NULL, *key = NULL, *value = NULL;

	records = 0; // number of records (rows) with 2 columns: key:value

	for (param = (uint8_t *)strtok((void *)dialog, (void *)dialog_delimiter); param != NULL; param = (uint8_t *)strtok(NULL, (void *)dialog_delimiter))
	{
		if (param[0] == '=' || strchr((void *)param, *param_delimiter) == NULL)
			break;

		key = (uint8_t *)strtok_r((void *)param, (void *)param_delimiter, (void *)&value); // assigns key & values contents
		args = (uint8_t ***)realloc(args, (++records) * sizeof(uint8_t *));				   // extends array by one row (2 columns)

		args[records - 1] = (uint8_t **)malloc(2 * sizeof(uint8_t *));					 // reserves memory for one row with 2 columns
		args[records - 1][0] = (uint8_t *)malloc((sizeof(key) * 8) * sizeof(uint8_t));	 // reserves memory for key column
		args[records - 1][1] = (uint8_t *)malloc((sizeof(value) * 8) * sizeof(uint8_t)); // reserves memory for value column

		strcpy((void *)args[records - 1][0], (void *)key);	 // copie  key string to the array
		strcpy((void *)args[records - 1][1], (void *)value); // copies value string to the array
	}

	return args; // returns 2d array of array of uint8_t
}

uint8_t *connector_manage(uint8_t ***args)
{
	uint8_t *idx = (uint8_t *)"", *opt = (uint8_t *)"", *str = args[0][1];
	uint8_t i = 0;

	if (records == 0) // check if no records detected
		return cmd_builder_buildErr((uint8_t *)"0", ERR.NO_PARAMS);
	else if (records == 1) // check if there is only one record
		return cmd_builder_buildErr((uint8_t *)"0", ERR.ONE_PARAM_ONLY);
	else if (records > 5) // check if there is more than 5 records
		return cmd_builder_buildErr((uint8_t *)"0", ERR.TO_MANY_PARAMS);

	if (args != NULL && strcmp((void *)args[0][0], (void *)KEY.INDEX) != 0) // check if there is no "idx" key
		return cmd_builder_buildErr((uint8_t *)"0", ERR.NO_INDEX_KEY);

	for (i = 0; i < strlen((void *)str); i++)
	{
		if (str[i] < 48 || str[i] > 57) // check if string contains only numbers
			return cmd_builder_buildErr((uint8_t *)"0", ERR.INVALID_INDEX_VALUE);
	}

	if (args != NULL && strcmp((void *)args[1][0], (void *)KEY.OPERATION) != 0) // check if there is no "opt" key
		return cmd_builder_buildErr(args[0][1], ERR.NO_OPERATION_KEY);

	idx = args[0][1]; // get index value
	opt = args[1][1]; // get operation type

	records = (uint8_t)(records - 2); // decrease number of rows by 2 (remove index and operation)

	memmove(args, args + 2, records * sizeof(uint8_t *)); // moves the array 2 place forward (removes 2 first rows with idx and opt)

	/* checks operation (opt) mode and calls appropriate prepare_function */

	if (strcmp((void *)opt, (void *)OPT.SET_SPEED) == 0)
		return prepare_configuration(idx, args);
	else if (strcmp((void *)opt, (void *)OPT.SWITCH) == 0)
		return prepare_switch(idx, args);
	else if (strcmp((void *)opt, (void *)OPT.HOME) == 0)
		return prepare_home(idx, args);
	else if (strcmp((void *)opt, (void *)OPT.MOVE) == 0)
		return prepare_move(idx, args);
	else if (strcmp((void *)opt, (void *)OPT.PROCESS) == 0)
		return prepare_process(idx, args);
	else if (strcmp((void *)opt, (void *)OPT.PAUSE) == 0)
		return prepare_intervention(idx, args, stepper_pause);
	else if (strcmp((void *)opt, (void *)OPT.RESUME) == 0)
		return prepare_intervention(idx, args, stepper_resume);
	else if (strcmp((void *)opt, (void *)OPT.STOP) == 0)
		return prepare_intervention(idx, args, stepper_stop);
	else
		return cmd_builder_buildErr(idx, ERR.INVALID_OPERATION_VALUE);
}
