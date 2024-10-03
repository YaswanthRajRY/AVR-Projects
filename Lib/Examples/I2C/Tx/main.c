#include <avr/io.h>
#include <util/delay.h>

#include "UART.h"
#include "I2C.h"

#define MAX_SIZE 5

uint8_t xBuffer[5] = {0, 0, 0, 0, 0};

void LOG(char*);
uint8_t get_DHT11_values(void);
void I2C_Tx(void);

int main(void)
{
    init_UART();
    init_I2C_Master();

    while (1)
    {
        if(get_DHT11_values())
            I2C_Tx();
        
        _delay_ms(1000);
    } 
}

uint8_t get_DHT11_values()
{
    uint8_t reset = 0;
    uint8_t i;
    uint8_t j;
    
    DDRD |= (1 << DDD4);
    PORTD |= (1 << PORTD4);
    _delay_ms(100);
    
    PORTD &= ~(1 << PORTD4);
    _delay_ms(18);
    PORTD |= (1 << PORTD4);

    DDRD &= ~(1 << DDD4);
    _delay_us(40);

    if (PIND & (1 << PIN4))
    {
        return 0;
    }
    
    _delay_us(80);
    if (!(PIND & (1 << PIN4)))
    {
        return 0;
    }
    
    _delay_us(80);
    if (PIND & (1 << PIN4))
    {
        return 0;
    }
        
        for (i = 0; i < 5; i++)
    {
        uint8_t xData = 0;
        for (j = 0; j < 8; j++)
        {
            reset = 0;
            while (!(PIND & (1 << PIN4)))
            {
                reset += 2;
                _delay_us(2);

                if (reset > 50)
                {    
                    return 0;
                }
            }

            _delay_us(40);

            if (PIND & (1 << PIN4))
            {
                xData |= (1 << (7-j));
            }

            reset = 0;
            while (PIND & (1 << PIN4))
            {
                reset += 2;
                _delay_us(2);

                if (reset > 50)
                {    
                    return 0;
                }
            }
        }
        xBuffer[i] = xData;
    }

    if (((xBuffer[0] + xBuffer[1] + xBuffer[2] + xBuffer[3]) & 0xFF) != xBuffer[4])
    {   
        return 0;
    }

    return 1;
}


void I2C_Tx()
{
    LOG("Start sent");
    if(I2C_Start())
        LOG(" received\n\r");

    LOG("SLA+W sent");
    if(I2C_SLA_W(SLAVE_ADDR))
        LOG(" recived\n\r");

    LOG("Data sent");
    if(I2C_TxData_nBytes(xBuffer, MAX_SIZE))
        LOG(" recived\n\r");

    LOG("Stop\n\n\n\r");
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
  