#include "command/cmd_parser.h"

#include <string.h> // includes defintion and use of strtok function
#include <stdlib.h> // needed to use malloc, calloc, realloc

#include "null.h"
#include "validator.h"

#include "command/cmd_builder.h"
#include "command/cmd_executor.h"
#include "command/cmd_helper.h"

#include "device/low_voltage/stepper/partial/stepper_configuration.h"
#include "device/low_voltage/stepper/partial/stepper_operation.h"
#include "device/low_voltage/stepper/partial/stepper_intervention.h"
#include "device/low_voltage/stepper/partial/stepper_validator.h"

#include "process.h"

uint8_t *dialog_delimiter = (uint8_t *)"|"; // the dialog delimiter, that seprates 2 sentences; e.g. opt=mov|spp=x|
uint8_t *param_delimiter = (uint8_t *)"=";	// the param (sentence) delimiter, that seperate key and value of sentence; e.g. opt=mov

uint8_t records = 0; // number of rows (key:value) of parsered dialog

uint8_t ***cmd_parse(uint8_t *dialog)
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

		strcpy((void *)args[records - 1][0], (void *)key);	 // copy  key string to the array
		strcpy((void *)args[records - 1][1], (void *)value); // copies value string to the array
	}

	return args; // returns 2d array of array of uint8_t
}

uint8_t *cmd_chooseAction(uint8_t *idx, uint8_t *opt, uint8_t ***args)
{
	// checks operation (opt) mode and calls appropriate prepare_function
	if (validate_key(OPT.CONFIGURE_STEPPER, opt) == ERR.NO_ERROR)
		return cmd_stepperAction(idx, args, (uint8_t *[]){KEY.STEPPER, KEY.SPEED, KEY.ACCELERATION}, 3, validate_configure, stepper_configure);

	/* SWITCH ACTIONS */
	else if (validate_key(OPT.SWITCH_STEPPER, opt) == ERR.NO_ERROR)
		return cmd_stepperAction(idx, args, (uint8_t *[]){KEY.STEPPER, KEY.STATE}, 2, validate_switch, stepper_switch);

	else if (validate_key(OPT.SWITCH_POMP, opt) == ERR.NO_ERROR)
		return cmd_hvdAction(idx, args, &POMP);

	else if (validate_key(OPT.SWITCH_TH_PHASE_MOTOR, opt) == ERR.NO_ERROR)
		return cmd_hvdAction(idx, args, &TH_PHASE_MOTOR);
	/* ************** */

	/* MOVE AND PROCESS ACTIONS */
	else if (validate_key(OPT.MOVE_STEPPER, opt) == ERR.NO_ERROR)
		return cmd_stepperAction(idx, args, (uint8_t *[]){KEY.STEPPER, KEY.WAY, KEY.DIRECTION}, 3, validate_move, stepper_move);

	else if (validate_key(OPT.PROCESS_ALL, opt) == ERR.NO_ERROR)
		return cmd_proccessAction(idx, args);
	/* *********************** */

	/* PAUSE RESUME STOP INTERVENTIONS */
	else if (validate_key(OPT.PAUSE_STEPPER, opt) == ERR.NO_ERROR)
		return cmd_stepperAction(idx, args, (uint8_t *[]){KEY.STEPPER}, 1, validate_pause, stepper_pause);

	else if (validate_key(OPT.RESUME_STEPPER, opt) == ERR.NO_ERROR)
		return cmd_stepperAction(idx, args, (uint8_t *[]){KEY.STEPPER}, 1, validate_resume, stepper_resume);

	else if (validate_key(OPT.STOP_STEPPER, opt) == ERR.NO_ERROR)
		return cmd_stepperAction(idx, args, (uint8_t *[]){KEY.STEPPER}, 1, validate_stop, stepper_stop);
	/* ******************************* */

	/* GET STATE ACTIONS */
	else if (validate_key(OPT.GET_STATE_OF_STEPPER, opt) == ERR.NO_ERROR)
		return cmd_getLVDState(idx, args, LVD_STEPPER);

	else if (validate_key(OPT.GET_STATE_OF_ENDSTOP, opt) == ERR.NO_ERROR)
		return cmd_getLVDState(idx, args, LVD_ENDSTOP);

	else if (validate_key(OPT.GET_STATE_OF_POMP, opt) == ERR.NO_ERROR)
		return cmd_getHVDState(idx, args, &POMP);

	else if (validate_key(OPT.GET_STATE_OF_TH_PHASE_MOTOR, opt) == ERR.NO_ERROR)
		return cmd_getHVDState(idx, args, &TH_PHASE_MOTOR);

	/* ***************** */

	return cmd_builder_buildErr(idx, ERR.INVALID_OPERATION_VALUE);
}

uint8_t *cmd_proceed(uint8_t ***args)
{
	uint8_t *index = EMPTY;
	uint8_t *option = EMPTY;

	if (records == 0) // check if no records detected
		return cmd_builder_buildErr(ZER0_INDEX, ERR.NO_PARAMS);
	else if (records == 1) // check if there is only one record
		return cmd_builder_buildErr(ZER0_INDEX, ERR.ONE_PARAM_ONLY);
	else if (records > 5) // check if there is more than 5 records
		return cmd_builder_buildErr(ZER0_INDEX, ERR.TO_MANY_PARAMS);

	if (args != NULL && validate_key(KEY.INDEX, args[0][0]) == ERR.ERROR) // check if there is no "idx" key
		return cmd_builder_buildErr(ZER0_INDEX, ERR.NO_INDEX_KEY);

	index = args[0][1];

	if (!containsOnlyDigits(index))
		return cmd_builder_buildErr(ZER0_INDEX, ERR.INVALID_INDEX_VALUE);

	if (args != NULL && validate_key(KEY.OPERATION, args[1][0]) == ERR.ERROR) // check if there is no "opt" key
		return cmd_builder_buildErr(index, ERR.NO_OPERATION_KEY);

	option = args[1][1];

	// decrease number of rows by 2 (remove index and operation)
	records = (uint8_t)(records - 2);

	// moves the array 2 place forward (removes 2 first rows with idx and opt)
	memmove(args, args + 2, records * sizeof(uint8_t *));

	return cmd_chooseAction(index, option, args);
}
