#include "User.h"
#include <string.h>
uint8_t uart_rx_buffer[128];
uint8_t uart_rx_index = 0;
uint32_t uart_rx_tick = 0;




void UART0_IRQHandler(void)
{

    uart_rx_tick = uwTick;
    uart_rx_buffer[uart_rx_index++] =
        ((uint8_t)(UART_0_INST->RXDATA & UART_RXDATA_DATA_MASK));
    if (uart_rx_index >= 128) {
        uart_rx_index = 0;
    }
}

void uart_printf(UART_Regs *uart, char *fmt, ...)
{
    char buf[128];
    va_list args;
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);
    for (uint8_t i = 0; i < strlen(buf); i++)
    {
        while( DL_UART_isBusy(UART_0_INST) == true );
        uart->TXDATA = buf[i];
    }
}

void uart_task(void)
{
    if(uart_rx_index == 0) return;
    if(uwTick - uart_rx_tick > 100)
    {
        
        uart_printf(UART_0_INST, "receve : %s", uart_rx_buffer);
        memset(uart_rx_buffer, 0, uart_rx_index);
        uart_rx_index = 0;
    }
}