#include "communication/dma/partial/dma_operation.h"

#include "null.h"
#include "command/partial/data_assistant.h"

#include "config.h"

uint8_t dma_isReady()
{
    return dma.commands_count;
}

uint8_t dma_getChar()
{
    if (dma.head == dma.tail)
        return 0;

    dma.tail = (uint16_t)((dma.tail + 1) % UART_BUFFER_SIZE); // set tail index
    return dma.uart_buffer[dma.tail];                         // return character from buffer
}

uint8_t *dma_getCommand()
{
    uint8_t ch = '\0';
    uint8_t *cmd = EMPTY;

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

void dma_processData(uint8_t length)
{
    uint8_t i = 0;
    uint16_t temp = 0;

    if (length >= MIN_COMMAND_LENGTH) // min length of command is 21 (calculated, first validation)
    {
        for (i = 0; i < length; i++)
        {
            temp = (uint16_t)((dma.head + 1) % UART_BUFFER_SIZE);

            if (temp == dma.tail)
                dma.head = dma.tail;
            else
            {
                dma.uart_buffer[temp] = dma.dma_buffer[i];

                if (dma.uart_buffer[temp] == '\n') // if there is end of line sign, that means this is end of command
                    dma.commands_count++;          // so increase number of commands

                dma.head = temp;
            }
        }

        if (!dma.commands_count) // situation then command is valid length but there is no \n on the end
            dma.commands_count = 1;
    }
}
