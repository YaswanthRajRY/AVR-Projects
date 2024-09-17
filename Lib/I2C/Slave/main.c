#include <avr/io.h>
#include <util/delay.h>

#include "UART.h"
#include "I2C.h"

char buffer[30];
uint8_t xIndex = 0;

void get_I2C_Data(void);
void LOG(char*);

int main(void)
{
    
    //DDRD = 0xFF;
    //DDRC = 0x0F;
    DDRC |= 0x30;
    PORTC |= 0x30;

    init_I2C_Slave();
    init_UART();

    while (1)
    {
        get_I2C_Data();
    }
}

void get_I2C_Data()
{
    uint8_t temp = 0;
    if (I2C_Slave_SLA_W())
    {
        I2C_SlaveRx(&temp);
        UART_Transmit(temp);
    }
/*
    while (1)
    {
        if (I2C_Slave_SLA_W())
        {
            I2C_SlaveRx(&temp);
            //UART_Transmit(temp);

            buffer[xIndex++] = temp;

            if (temp == '\r')
            {
                break;
            }
        }
    }
    buffer[xIndex] = '\0';
    
    LOG(buffer);
*/
}

void LOG(char* s)
{
    while (*s)
    {
        UART_Transmit(*s);
        s++;
    }
}
