#ifndef POMP_SETUP_H
#define POMP_SETUP_H

#include "device/pomp/pomp.h"

void pomp_init(Pomp *pomp, GPIO_TypeDef *port, uint16_t pin);

/* PRIVATE */ //void pomp_setupGpio(Pomp *pomp);

#endif // POMP_SETUP_H
