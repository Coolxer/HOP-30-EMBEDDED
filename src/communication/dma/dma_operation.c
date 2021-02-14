#include "communication/dma/partial/dma_operation.h"

#include "command/partial/data_assistant.h"

uint8_t dma_isEmpty()
{
    return dma.empty;
}

void dma_clear()
{
    dma.empty = 1;
}

uint8_t dma_isReady()
{
    if (dma.commands_count) // check if commands_count is greater than 0
        return 1;

    return 0;
}

uint8_t dma_getChar()
{
    if (dma.head == dma.tail)
        return 0;

    dma.tail = (dma.tail + 1) % UART_BUFFER_SIZE; // set tail index
    return dma.uart_buffer[dma.tail];             // return character from buffer
}

uint8_t *dma_getCommand()
{
    uint8_t ch;
    uint8_t *cmd = (uint8_t *)"";

    while ((ch = dma_getChar()))
    {
        if (ch == '\n') // check if there is end of line (LF), which means command end?
            break;

        cmd = char_append(cmd, ch); // append char to command
    }

    if (dma.commands_count)
        dma.commands_count--; // decrease number of commands, which exists in buffer

    return cmd;
}

void useTC()
{
    tcReady = 0;
}