#include "cmd_builder.h"

#include <stdlib.h>
#include <string.h>

uint8_t cmd[255]; // too much size but dont worry, will be transmitted only filled characters

void cmd_builder_init()
{
	opts_init();
	keys_init();

	strcpy(RESPONSE.PASSED, "pas\0");
	strcpy(RESPONSE.ERROR, "err\0");
	strcpy(RESPONSE.FINISHED, "fin\0");
}

uint8_t *cmd_builder_buildPas(uint8_t *id)
{
	snprintf(cmd, sizeof(cmd), "%s%c%s%c%s%c%s%s", KEYS.INDEX, '=', id, '|', KEYS.RESPONSE, '=', RESPONSE.PASSED, "|\n");

	return cmd;
}

uint8_t *cmd_builder_buildErr(uint8_t *id, uint8_t *code)
{
    snprintf(cmd, sizeof(cmd), "%s%c%s%c%s%c%s%c%s%c%s%s", KEYS.INDEX, '=', id, '|', KEYS.RESPONSE, '=', RESPONSE.ERROR, '|', KEYS.CODE, '=', code, "|\n");
    
    return cmd; 
}

uint8_t *cmd_builder_buildFin(uint8_t *id, uint8_t *value)
{
	if(strcmp((void*)value, "2") == 0)
		snprintf(cmd, sizeof(cmd), "%s%c%s%c%s%c%s%s", KEYS.INDEX, '=', id, '|', KEYS.RESPONSE, '=', RESPONSE.FINISHED, "|\n");
	else
    	snprintf(cmd, sizeof(cmd), "%s%c%s%c%s%c%s%c%s%c%s%s", KEYS.INDEX, '=', id, '|', KEYS.RESPONSE, '=', RESPONSE.FINISHED, '|', KEYS.VALUE, '=', value, "|\n");
		
    return cmd; 
}
