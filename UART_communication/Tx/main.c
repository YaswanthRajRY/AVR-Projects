#include <avr/io.h>
#include <util/delay.h>

#include "UART.h"

void sendString(char*);

int main(void)
{
    init_UART();

    while (1)
    {
        sendString("Yaswanth Raj\n");
        _delay_ms(3000);
        sendString("\rTest_1 Hello\n");
        _delay_ms(3000);
        sendString("\rTest_2 World\n");
        _delay_ms(3000);
        sendString("Top Gun\n");
        _delay_ms(3000);
        sendString("\rMaveric\n");
        _delay_ms(3000);
    } 
}

void sendString(char* str)
{
    while (*str != '\0')
    {
        UART_Transmit(*str);
        str++;
    }
}