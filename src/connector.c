#include "connector.h"

#include <stdlib.h> // needed to use malloc, calloc, realloc
#include <string.h> // includes defintion and use of strtok function
#include <stddef.h> // includes NULL value

#include "cmd_builder.h"
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

		key = (uint8_t*)strtok_r((void *)param, (void *)param_delimiter, (void*)&value); // assigns key & values contents
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
	uint8_t *idx = (uint8_t *)"";
	uint8_t *opt = (uint8_t *)"";;
	uint8_t i;
	uint8_t* str = args[0][1];

	if(records == 0) // check if no records detected
		return cmd_builder_buildErr((uint8_t*)"0", (uint8_t*)"1");
	else if(records == 1) // check if there is only one record 
		return cmd_builder_buildErr((uint8_t*)"0", (uint8_t*)"2");
	else if(records > 4) // check if there is more than 34 records 
		return cmd_builder_buildErr((uint8_t*)"0", (uint8_t*)"3");

	if(args != NULL && strcmp((void*)args[0][0], (void*)KEYS.INDEX) != 0) // check if there is no "idx" key
		return cmd_builder_buildErr((uint8_t*)"0", (uint8_t*)"4");

	for(i = 0; i < strlen((void*)str); i++)
	{
		if(str[i] < 48 || str[i] > 57)  // check if string contains only numbers
			break;
	}

	if(i != strlen((void*)args[0][1]))
		return cmd_builder_buildErr((uint8_t*)"0", (uint8_t*)"5"); 
		
	if(args != NULL && strcmp((void*)args[1][0], (void*)KEYS.OPERATION) != 0) // check if there is no "opt" key
		return cmd_builder_buildErr(args[0][1], (uint8_t*)"6");

	idx = args[0][1]; // get index value 
	opt = args[1][1]; // get operation type

	records -= 2;
	
	memmove(args, args + 2, records * sizeof(uint8_t *)); // moves the array 2 place forward (removes 2 first rows with idx and opt)

	/* checks operation (opt) mode and calls appropriate prepare_function */

	if(strcmp((void *)opt, (void*)OPTS.SETUP_SPEED) == 0)
		return prepare_settings(idx, args, KEYS.SPEED, stepper_setSpeed);
	else if(strcmp((void *)opt, (void*)OPTS.SETUP_MICROSTEPPING) == 0)
		return prepare_settings(idx, args, KEYS.MICROSTEPPING, stepper_setMicrostepping);
	else if(strcmp((void *)opt, (void*)OPTS.GET_STATE) == 0)
		return prepare_getEndstopState(idx, args);
	else if(strcmp((void *)opt, (void*)OPTS.SWITCH) == 0)
		return prepare_switch(idx, args);
	else if(strcmp((void *)opt, (void*)OPTS.HOME) == 0)
		return prepare_home(idx, args);
	else if(strcmp((void *)opt, (void*)OPTS.MOVE) == 0)
		return prepare_move(idx, args);
	else if(strcmp((void *)opt, (void*)OPTS.PROCESS) == 0)
		return prepare_process(idx, args);
	else if(strcmp((void *)opt, (void*)OPTS.PAUSE) == 0)
		return prepare_intervention(idx, args, stepper_pause);
	else if(strcmp((void *)opt, (void*)OPTS.RESUME) == 0)
		return prepare_intervention(idx, args, stepper_resume);
	else if(strcmp((void *)opt, (void*)OPTS.STOP) == 0)
		return prepare_intervention(idx, args, stepper_stop);
	else
		return cmd_builder_buildErr(idx, (uint8_t*)"7");
}



