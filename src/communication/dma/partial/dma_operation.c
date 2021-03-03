#include "communication/dma/partial/dma_operation.h"

#include "enum/type.h"
#include "command/partial/data_assistant.h"

uint8_t dma_isReady()
{
    return dma.commands_count;
}

uint8_t dma_getChar()
{
    if (dma.head == dma.tail)
        return FALSE;

    dma.tail = (uint16_t)((dma.tail + 1) % UART_BUFFER_SIZE); // set tail index
    return dma.uart_buffer[dma.tail];                         // return character from buffer
}

uint8_t *dma_getCommand()
{
    uint8_t ch = '\0';
    uint8_t *cmd = (uint8_t *)"\0";

    while ((ch = dma_getChar()))
    {
        if (ch == '\n') // check if there is end of line (LF), which means command end?
            break;

        cmd = charAppend(cmd, ch); // append char to command
    }

    if (dma.commands_count)
        dma.commands_count--; // decrease number of commands, which exists in buffer

    return cmd;
}
