#include "opts.h"

#include <string.h>

void opts_init() {
    strcpy((void*)OPTS.SETUP_SPEED, "ses\0");
    strcpy((void*)OPTS.SETUP_MICROSTEPPING, "sem\0");
    strcpy((void*)OPTS.GET_STATE, "ges\0");
    strcpy((void*)OPTS.SWITCH, "sth\0");
    strcpy((void*)OPTS.MOVE, "mov\0");
    strcpy((void*)OPTS.HOME, "hom\0");
    strcpy((void*)OPTS.PROCESS, "pro\0");

    strcpy((void*)OPTS.PAUSE, "pau\0");
    strcpy((void*)OPTS.RESUME, "res\0");
    strcpy((void*)OPTS.STOP, "sto\0");
}