#include "command/partial/val.h"

#include <string.h>

val VAL = {0};

void val_init()
{
    strcpy((void *)VAL.LIMIT, "lim\0");
    strcpy((void *)VAL.NONE, "non\0");
}