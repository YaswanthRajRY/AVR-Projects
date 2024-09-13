#include <avr/io.h>
#include <util/delay.h>

#include "UART.h"

int main(void)
{
    init_UART();
    while (1)
    {
        UART_Transmit('A');
        _delay_ms(1000);
    }
}