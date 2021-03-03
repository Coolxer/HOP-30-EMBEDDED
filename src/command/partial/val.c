#include "command/partial/val.h"

#include <string.h>

val VAL;

void val_init()
{
    strcpy((void *)VAL.PROCESS, "pro\0");
    strcpy((void *)VAL.ALL, "all\0");
}