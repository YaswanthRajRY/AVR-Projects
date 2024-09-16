#include "SPI.h"

void init_SPI_Master()
{
    DDRB |= (1 << DDB5) | (1 << DDB3) | (1 << DDB2);
    PORTB |= (1 << PORTB2);
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void init_SPI_Slave()
{
    DDRB |= (1 << DDB4);
    SPCR = (1 << SPE);
}

void SPI_Transmit(unsigned char tData)
{
    PORTB &= ~(1 << PORTB2);

    SPDR = tData;

    while (!(SPSR & (1 << SPIF)));
    PORTB |= (1 << PORTB2);
}

char SPI_Recive()
{
    while (!(SPSR & (1 << SPIF)));

    return SPDR;
}