#include "command/builder/partial/res.h"

#include <string.h>

res RES = {0};

void res_init()
{
    strcpy((void *)RES.ERROR, "err\0");

    strcpy((void *)RES.PASSED, "pas\0");
    strcpy((void *)RES.IN_PROGRESS, "inp\0");
    strcpy((void *)RES.FINISHED, "fin\0");

    strcpy((void *)RES.VALUE, "val\0");
}