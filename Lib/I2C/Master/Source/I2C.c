#include <avr/io.h>
#include <util/delay.h>

#include "I2C.h"

void init_I2C()
{
    DDRB |= 0x30;
    PORTB |= 0x30;

    TWBR = 0x0C;
    TWSR = 0x00;
    TWCR |= (1 << TWEN);
}

void init_I2C_Slave(void)
{
    DDRB |= 0x30;
    PORTB |= 0x30;

    TWAR = (SLAVE_ADDR << 1);
    TWCR |= (1 << TWEA) | (1 << TWEN);
}

uint8_t I2C_Start()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)));

    if ((TWSR & 0xF8) == 0x10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t I2C_SLA_W(uint8_t addr)
{
    TWDR = (addr << 1);
    TWCR = (1 << TWINT) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)));

    if ((TWSR & 0xF8) == 0x18)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t I2C_SLA_R(uint8_t addr)
{
    TWDR = (addr << 1) | 0x01;
    TWCR = (1 << TWINT) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)));

    if ((TWSR & 0xF8) == 0x40)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t I2C_TxData(uint8_t tData)
{
    TWDR = tData;
    TWCR = (1 << TWINT) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)));

    if ((TWSR & 0xF8) == 0x28)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t I2C_RxData(uint8_t* tData)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    while (!(TWCR & (1 << TWINT)));
    
    *tData = TWDR;

    if ((TWSR & 0xF8) == 0x50)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t I2C_Stop()
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    
    while (TWCR & (1 << TWSTO));

    return 0;
}


uint8_t I2C_Slave_SLA_W()
{
    TWCR |= (1 << TWINT) | (1 << TWEA) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)));

    if ((TWSR & 0xF8) == 0x60)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t I2C_Slave_SLA_R()
{
    
}

uint8_t I2C_SlaveTx(uint8_t tData)
{

}

uint8_t I2C_SlaveRx(uint8_t* tData)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    while (!(TWCR & (1 << TWINT)));
    
    *tData = TWDR;

    if ((TWSR & 0xF8) == 0x80)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}