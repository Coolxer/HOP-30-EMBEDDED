#include "command/partial/res.h"

#include <string.h>

void res_init()
{
    strcpy((void *)RES.PASSED, "pas\0");
    strcpy((void *)RES.ERR, "err\0");
    strcpy((void *)RES.FINISHED, "fin\0");
}