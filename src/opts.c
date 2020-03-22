#include "opts.h"

#include <string.h>

void opts_init() {
    strcpy(OPTS.SETUP_SPEED, "ses\0");
    strcpy(OPTS.SETUP_MICROSTEPPING, "sem\0");
    strcpy(OPTS.GET_STATE, "ges\0");
    strcpy(OPTS.SWITCH, "sth\0");
    strcpy(OPTS.MOVE, "mov\0");
    strcpy(OPTS.HOME, "hom\0");
    strcpy(OPTS.PROCESS, "pro\0");

    strcpy(OPTS.PAUSE, "pau\0");
    strcpy(OPTS.RESUME, "res\0");
    strcpy(OPTS.STOP, "sto\0");
}