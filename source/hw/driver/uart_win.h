#ifndef UART_WIN_H
#define UART_WIN_H


#include <stdint.h>
#include <stdbool.h>


bool uartInit(void);

int uartWrite(uint8_t ch,
              uint8_t *p_data,
              uint32_t length);

bool uartReadBlock(uint8_t ch,
                   uint8_t *p_data,
                   uint32_t timeout);


#endif