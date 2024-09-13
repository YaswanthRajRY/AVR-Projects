#include <avr/io.h>
#include <util/delay.h>

void init_SPI_Master(void);
void SPI_Transmit(unsigned char);
void sendString(char*);
char* incCounter(unsigned char);

int main(void)
{
    init_SPI_Master();

    uint8_t counter = 0;

    sendString("SPI Communica....\n");
    _delay_ms(100);

    while (1)
    {
        char* s = incCounter(counter++);
        sendString(s);
        _delay_ms(1000);
    }
}

void init_SPI_Master()
{
    DDRB |= (1 << DDB5) | (1 << DDB3) | (1 << DDB2);
    PORTB |= (1 << PORTB2);
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_Transmit(unsigned char tData)
{
    PORTB &= ~(1 << PORTB2);

    SPDR = tData;

    while (!(SPSR & (1 << SPIF)));
    PORTB |= (1 << PORTB2);
}

void sendString(char* str)
{
    while (*str != '\0')
    {
        SPI_Transmit(*str);
        str++;
    }
}

char* incCounter(uint8_t num)
{
    static char str[5];
    str[0] = '\r';
    str[4] = '\n';
    uint8_t i = 3;
    while (num || i != 0)
    {
        str[i--] = (num%10) + '0';
        num /=10; 
    }
    return str;
}