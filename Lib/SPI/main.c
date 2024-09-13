#include <avr/io.h>
#include <util/delay.h>

#include "UART.h"

void SPI_Slaveinit(void);
void SPI_recive(void);

int main(void)
{
    SPI_Slaveinit();
    UART_init(BAUD_RATE);
    
    _delay_ms(10);
    while(1)
    {
        SPI_recive();
        _delay_ms(100);
    }
}

void SPI_Slaveinit()
{
    DDRB |= (1 << DDB4); 
    SPCR |= (1 << SPE); // enable SPR, set this device as Slave
    SerialWrite("Intitialization done\n");
}

void SPI_recive()
{
    while(!(SPSR & (1 << SPIF)));

    SerialWrite("In recive function\n");
}
