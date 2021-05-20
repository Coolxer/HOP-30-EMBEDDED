#include "command/cmd_builder.h"

#include <stdio.h>
#include <string.h>

#include "null.h"

uint8_t *ZER0_INDEX = (uint8_t *)"0";
uint8_t *SHUTDOWN_REQUEST = (uint8_t *)"SHUTDOWN|||||||||||||||\n";
uint8_t *SHUTDOWN_RESPONSE = (uint8_t *)"SHUTDOWNED||||||||||||\n";

uint8_t cmd[255]; // too much size but dont worry, will be transmitted only filled characters

void cmd_builder_init()
{
	opt_init();
	key_init();
	res_init();
	err_init();
	val_init();
}

uint8_t *cmd_builder_buildPas(uint8_t *id)
{
	snprintf((void *)cmd, sizeof(cmd), "%s%c%s%c%s%c%s%s", KEY.INDEX, '=', id, '|', KEY.RESPONSE, '=', RES.PASSED, "|\n");

	return cmd;
}

uint8_t *cmd_builder_buildErr(uint8_t *id, uint8_t code)
{
	snprintf((void *)cmd, sizeof(cmd), "%s%c%s%c%s%c%s%c%s%c%u%s", KEY.INDEX, '=', id, '|', KEY.RESPONSE, '=', RES.ERR, '|', KEY.CODE, '=', code, "|\n");

	return cmd;
}

uint8_t *cmd_builder_buildFin(uint8_t *id)
{
	snprintf((void *)cmd, sizeof(cmd), "%s%c%s%c%s%c%s%s", KEY.INDEX, '=', id, '|', KEY.RESPONSE, '=', RES.FINISHED, "|\n");

	return cmd;
}

uint8_t getErrorByKey(uint8_t *key, enum ErrorType et)
{
	if (stringEqual(key, KEY.INDEX))
		return et == KEY_ERROR ? ERR.NO_INDEX_KEY : ERR.INVALID_INDEX_VALUE;

	else if (stringEqual(key, KEY.OPERATION))
		return et == KEY_ERROR ? ERR.NO_OPERATION_KEY : ERR.INVALID_OPERATION_VALUE;

	else if (stringEqual(key, KEY.STEPPER))
		return et == KEY_ERROR ? ERR.NO_STEPPER_KEY : ERR.INVALID_STEPPER_VALUE;

	else if (stringEqual(key, KEY.ENDSTOP))
		return et == KEY_ERROR ? ERR.NO_ENDSTOP_KEY : ERR.INVALID_ENDSTOP_VALUE;

	else if (stringEqual(key, KEY.SPEED))
		return et == KEY_ERROR ? ERR.NO_SPEED_KEY : ERR.INVALID_SPEED_VALUE;

	else if (stringEqual(key, KEY.ACCELERATION))
		return et == KEY_ERROR ? ERR.NO_ACCELERATION_KEY : ERR.INVALID_ACCELERATION_VALUE;

	else if (stringEqual(key, KEY.WAY))
		return et == KEY_ERROR ? ERR.NO_WAY_KEY : ERR.INVALID_WAY_VALUE;

	else if (stringEqual(key, KEY.STATE))
		return et == KEY_ERROR ? ERR.NO_STATE_KEY : ERR.INVALID_STATE_VALUE;

	else if (stringEqual(key, KEY.DIRECTION))
		return et == KEY_ERROR ? ERR.NO_DIRECTION_KEY : ERR.INVALID_DIRECTION_VALUE;
}
