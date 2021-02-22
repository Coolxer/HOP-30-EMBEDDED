#include "command/cmd_builder.h"

#include <string.h>
#include <stdio.h>

uint8_t cmd[255]; // too much size but dont worry, will be transmitted only filled characters

void cmd_builder_init()
{
	opt_init();
	key_init();
	res_init();
	err_init();
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

uint8_t *cmd_builder_buildPasFinErr(uint8_t *id, uint8_t pas, uint8_t code, Stepper *stepper)
{
	// if there is no ERR code
	if (code == 0)
	{
		if (pas == 1)
		{
			cmd_builder_buildPas(id);
			stepper->index = id;
		}
		else
			cmd_builder_buildFin(id);
	}

	else // if there was an ERR
		cmd_builder_buildErr(id, code);

	return cmd;
}
