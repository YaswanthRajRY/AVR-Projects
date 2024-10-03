#include "I2C.h"

void init_I2C_Master()
{
    DDRC |= 0x30;
    PORTC |= 0x30;

    TWBR = 0x0C;                                            // Set Bit rate
    TWSR = 0x00;                                            // Clear status register
    TWCR |= (1 << TWEN);                                    // Enable I2C
}

void init_I2C_Slave(void)
{
    DDRC |= 0x30;
    PORTC |= 0x30;
    
    TWAR = (SLAVE_ADDR << 1);                               // Load slave address to TWAR register
    TWCR |= (1 << TWEN) | (1 << TWEA);                      // Enable I2C and ACK
}

uint8_t I2C_Start()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);       // set intrupt, start and enable bit in TWCR register

    while (!(TWCR & (1 << TWINT)));                         // Wait till start signal is transmit

    if ((TWSR & 0xF8) == 0x08)                              // Check status in TWSR register
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
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);       // set intrupt, stop and enable bit in TWCR register
    
    while (TWCR & (1 << TWSTO));                            // Wait till stop signal is transmit

    return 0;
}

uint8_t I2C_SLA_W(uint8_t addr)
{
    TWDR = (addr << 1);                                     // add 0 in LSB to represent write
    TWCR = (1 << TWINT) | (1 << TWEN);                      // Set intrupt and enable bit

    while (!(TWCR & (1 << TWINT)));                         // Wait till data is transmit

    if ((TWSR & 0xF8) == 0x18)                              // Check status
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
    TWDR = (addr << 1) | 0x01;                              // add 1 in LSB to represent read
    TWCR = (1 << TWINT) | (1 << TWEN);                      // Set intrupt and enable bit

    while (!(TWCR & (1 << TWINT)));                         // Wait till data is transmit

    if ((TWSR & 0xF8) == 0x40)                              // Check status
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t I2C_Slave_SLA_W()
{
    TWCR |= (1 << TWINT) | (1 << TWEA) | (1 << TWEN);       // set intrupt, start and enable bit in TWCR register

    while (!(TWCR & (1 << TWINT)));                         // wait till start signal is transmit

    if ((TWSR & 0xF8) == 0x60)                              // check status
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
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);        // set intrupt, start and enable bit in TWCR register

    while (!(TWSR & (1 << TWINT)));                         // wait till start signal is transmit

    if ((TWSR & 0xF8) == 0xA8)                              // check status
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
    TWDR = tData;                                           // Load data to be transmit
    TWCR = (1 << TWINT) | (1 << TWEN);                      // Enable intrupt and I2C

    while (!(TWCR & (1 << TWINT)));                         // Wait till data is transmission is done

    if ((TWSR & 0xF8) == 0x28)                              // Check status
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t I2C_TxData_nBytes(uint8_t* tData, uint8_t maxSize)
{
    uint8_t i;

    for (i=0; i<maxSize; i++)
    {
        if (!(I2C_TxData(tData[i])))
        {
            return 0;
        }
    }

    return 1;
}

uint8_t I2C_RxData(uint8_t* rData)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);        // Set intrupt, I2C enable and ACK bit in TWCR register

    while (!(TWCR & (1 << TWINT)));                         // Wait for data
    
    *rData = TWDR;                                          // Copy data from register

    if ((TWSR & 0xF8) == 0x50)                              // Check status
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t I2C_RxData_nBytes(uint8_t* rData, uint8_t maxSize)
{
    uint8_t i;

    for (i=0; i<maxSize; i++)
    {
        if (!(I2C_RxData(rData + i)))
        {
            return 0;
        }
    }

    return 1;
}

uint8_t I2C_SlaveTx(uint8_t tData)
{
    TWDR = tData;                                           // Load data for transmit
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);        // Set intrupt, I2C enable and ACK bit in TWCR register

    while (!(TWCR & (1 << TWINT)));                         // Wait for data to be transmit

    if ((TWSR & 0xF8) == 0x28)                              // Check status
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t I2C_SlaveTx_nBytes(uint8_t* tData, uint8_t maxSize)
{
    uint8_t i;

    for (i=0; i<maxSize; i++)
    {
        if (!(I2C_SlaveTx(tData[i])))
        {
            return 0;
        }
    }

    return 1;
}

uint8_t I2C_SlaveRx(uint8_t* rData)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);    // Set intrupt, I2C enable and ACK bit in TWCR register

    while (!(TWCR & (1 << TWINT)));                     // Wait for data to be received
    
    *rData = TWDR;                                      // Copy data

    if ((TWSR & 0xF8) == 0x80)                          // Check status
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t I2C_SlaveRx_nBytes(uint8_t* rData, uint8_t maxSize)
{
    uint8_t i;

    for (i=0; i<maxSize; i++)
    {
        if (!(I2C_SlaveRx(rData + i)))
        {
            return 0;
        }
    }

    return 1;
}