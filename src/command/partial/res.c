#include "command/partial/res.h"

#include <string.h>

res RES = {0};

uint8_t *ZERO_INDEX = (uint8_t *)"0\0";
uint8_t *SHUTDOWN_REQUEST = (uint8_t *)"SHUTDOWN|||||||||||||||\n";
uint8_t *SHUTDOWN_RESPONSE = (uint8_t *)"SHUTDOWNED||||||||||||\n";

void res_init()
{
    strcpy((void *)RES.ERROR, "err\0");

    strcpy((void *)RES.PASSED, "pas\0");
    strcpy((void *)RES.IN_PROGRESS, "inp\0");
    strcpy((void *)RES.FINISHED, "fin\0");

    strcpy((void *)RES.VALUE, "val\0");
}