#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

void init_SPI_Master(void);
void init_SPI_Slave(void);
void SPI_Transmit(unsigned char);
char SPI_Recive();
void get_SPI_Data(void);

char buffer[20];
uint8_t xIndex = 0;

int main(void)
{
    
    DDRD = 0xFF;
    DDRC = 0x0F;

    init_SPI_Slave();
    init_LCD();

    while (1)
    {
        get_SPI_Data();
    }
}

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

void get_SPI_Data()
{
    uint8_t reset = 0;
    while (1)
    {
        reset += 1;
        if (reset >=255)
        {
            break;
        }
        char temp = SPI_Recive();

        if (temp == '\n')
        {
            buffer[xIndex] = '\0';
            xIndex = 0;
            break;
        }
        else
        {
            buffer[xIndex++] = temp;
        }
    }
    LCD_Write_String(buffer);
}
