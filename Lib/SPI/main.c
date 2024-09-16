#include <avr/io.h>
#include <util/delay.h>

#include "SPI.h"

char buffer[20];
uint8_t xIndex = 0;

void get_SPI_Data(void);

int main(void)
{

    init_SPI_Slave();

    while (1)
    {
        get_SPI_Data();
    }
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
}
