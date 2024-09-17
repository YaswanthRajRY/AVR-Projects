#include <avr/io.h>
#include <util/delay.h>

#include "I2C.h"
#include "UART.h"

void sendMSG(char*);
void TransmitData(unsigned char);
void LOG(char*);

int main(void)
{
    init_I2C();
    init_UART();

    DDRC |= 0x30;
    PORTC |= 0x30;

    while (1)
    {
        sendMSG("Hello World !!!\n\r");
        sendMSG("If you can read this display message\n\r");
        sendMSG("Congratualtions you have sucessfully developed I2C Master to slave communication :)\n\r");
        sendMSG("\n\r");
        sendMSG("\n\r");
        sendMSG("\n\r");
        _delay_ms(1000);
    }
}

void sendMSG(char* str)
{
    while (*str != '\0')
    {
        TransmitData(*str);
        str++;
    }
}

void TransmitData(unsigned char tData)
{   
    LOG("Start sent");
    I2C_Start();
    LOG(" received\n\r");

    LOG("SLA+W sent");
    I2C_SLA_W(SLAVE_ADDR);
    LOG(" recived\n\r");

    LOG("Data sent");
    I2C_TxData(tData);
    LOG(" recived\n\r");

    LOG("Stop\n\r");
    I2C_Stop();
}

void LOG(char* s)
{
    while (*s)
    {
        UART_Transmit(*s);
        s++;
    }
}