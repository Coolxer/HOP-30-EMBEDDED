#include "command/cmd_builder.h"

#include <string.h>
#include <stdio.h>

uint8_t cmd[255]; // too much size but dont worry, will be transmitted only filled characters

void cmd_builder_init()
{
	opt_init();
	key_init();
	res_init();
}

uint8_t *cmd_builder_buildPas(uint8_t *id)
{
	snprintf((void *)cmd, sizeof(cmd), "%s%c%s%c%s%c%s%s", KEY.INDEX, '=', id, '|', KEY.RESPONSE, '=', RES.PASSED, "|\n");

	return cmd;
}

uint8_t *cmd_builder_buildErr(uint8_t *id, uint8_t *code)
{
	snprintf((void *)cmd, sizeof(cmd), "%s%c%s%c%s%c%s%c%s%c%s%s", KEY.INDEX, '=', id, '|', KEY.RESPONSE, '=', RES.ERROR, '|', KEY.CODE, '=', code, "|\n");

	return cmd;
}

uint8_t *cmd_builder_buildFin(uint8_t *id, uint8_t *value)
{
	if (strcmp((void *)value, "2") == 0)
		snprintf((void *)cmd, sizeof(cmd), "%s%c%s%c%s%c%s%s", KEY.INDEX, '=', id, '|', KEY.RESPONSE, '=', RES.FINISHED, "|\n");
	else
		snprintf((void *)cmd, sizeof(cmd), "%s%c%s%c%s%c%s%c%s%c%s%s", KEY.INDEX, '=', id, '|', KEY.RESPONSE, '=', RES.FINISHED, '|', KEY.VALUE, '=', value, "|\n");

	return cmd;
}
