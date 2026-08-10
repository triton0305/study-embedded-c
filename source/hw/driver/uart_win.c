#include "uart_win.h"

#include <stdio.h>
#include <windows.h>

static HANDLE hStdout = NULL;
static HANDLE hStdin = NULL;

bool uartInit(void)
{
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (hStdout != INVALID_HANDLE_VALUE)
    {
        DWORD mode = 0;

        GetConsoleMode(hStdout, &mode);

        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        SetConsoleMode(hStdout, mode);
    }

    if(hStdin != INVALID_HANDLE_VALUE)
    {
        DWORD mode = 0;

        GetConsoleMode(hStdin, &mode);

        mode &= ~ENABLE_LINE_INPUT;
        mode &= ~ENABLE_ECHO_INPUT;
        mode &= ~ENABLE_PROCESSED_INPUT;

        mode |= ENABLE_VIRTUAL_TERMINAL_INPUT;

        SetConsoleMode(hStdin, mode);
    }
    
    return true;
}

int uartWrite(uint8_t ch ,uint8_t *p_data, uint32_t length)
{
    DWORD written = 0;

    (void)ch;

    if(hStdout != INVALID_HANDLE_VALUE)
    {
        fwrite(p_data, 1, length, stdout);

        fflush(stdout);

        written = (DWORD)length;
    }

    return (int)written;
}

bool uartReadBlock(uint8_t ch, uint8_t *p_data, uint32_t timeout)
{
    DWORD read_bytes = 0;
    DWORD result;
    
    (void) ch;

    if(hStdin == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    result = WaitForSingleObject(hStdin, timeout);

    if (result == WAIT_OBJECT_0)
    {
        if (ReadFile(hStdin, p_data, 1, &read_bytes, NULL))
        {
            if (read_bytes > 0)
            {
                return true;
            }
        }
    }
    return false;
}