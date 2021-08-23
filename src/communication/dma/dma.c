#include "communication/dma/dma.h"

DMA dma = {0};

void dma_structure_init()
{
    dma.TRANSFER_COMPLETE = 1;
    dma.READY_FOR_TRANSFER = 1;
}