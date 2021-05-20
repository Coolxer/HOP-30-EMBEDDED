#include "command/partial/res.h"

#include <string.h>

res RES;

void res_init()
{
    strcpy((void *)RES.PASSED, "pas\0");
    strcpy((void *)RES.ERROR, "err\0");
    strcpy((void *)RES.FINISHED, "fin\0");
    strcpy((void *)RES.VALUE, "val\0");
}