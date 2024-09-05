#include <avr/io.h>
#include <util/delay.h>

#include "UART.h"

int main(void)
{
    UART_init(BAUD_RATE);
    while (1)
    {
        SerialWrite("RA1711004010613\n");
        //_delay_ms(1000);
        SerialWrite("62434541\n");
        //_delay_ms(1000);
        SerialWrite("My Reg No: 22MES1005\n");
        //_delay_ms(1000);
        SerialWrite("This is my first UART program code :)\n");
        SerialWrite("\n\n");
        _delay_ms(5000);
    }
}