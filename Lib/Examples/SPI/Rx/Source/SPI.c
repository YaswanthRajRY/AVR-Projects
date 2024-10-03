#include "SPI.h"

void init_SPI_Master()
{
    DDRB |= (1 << DDB5) | (1 << DDB3) | (1 << DDB2);        // Set MOSI, CLK and SS as output and other as input in port B
    PORTB |= (1 << PORTB2);
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);	        // Enable SPI, Master mode and set clock frequency
}

void init_SPI_Slave()
{
    DDRB |= (1 << DDB4);				                    // Set MISO as output and other as input in port B
    DDRB &= ~((1 << DDB5) | (1 << DDB3) | (1 << DDB2));
    SPCR = (1 << SPE);					                    // Enable SPI
}

void SPI_Transmit(uint8_t tData)
{
    SPDR = tData;					                        // Load data

    while (!(SPSR & (1 << SPIF)));			                // Wait for data in register to be shift out
    PORTB |= (1 << PORTB2);				                    // Set High SS pin to deselect the slave
}

uint8_t SPI_Recive()
{
    while (!(SPSR & (1 << SPIF)));			                // Wait for data

    return SPDR;					                        // Return data received in register
}