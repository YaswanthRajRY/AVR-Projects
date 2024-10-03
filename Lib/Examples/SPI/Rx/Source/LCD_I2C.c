#include <avr/io.h>
#include <util/delay.h>

#include "I2C.h"
#include "LCD_I2C.h"

void init_LCD_I2C()
{
    _delay_ms(50);

    LCD_CMD(0x02);
    _delay_ms(5);

    LCD_CMD(0x28);
    _delay_ms(1);
    
    LCD_CMD(0x0C);
    _delay_ms(1);
    
    LCD_CMD(0x01);
    _delay_ms(2);
    
    LCD_CMD(0x06);
    _delay_ms(1);
    
    LCD_CMD(0x80);
    _delay_ms(1);
}

void LCD_CMD(uint8_t CMD)
{
/*
    7  6  5  4  3  2  1  0
    D7 D6 D5 D4 B/L EN RW RS
*/

    uint8_t tData = (CMD & 0xF0);
    tData &= ~(RW) & ~(RS);
    tData |= EN | 0x08;
    I2C_Transmit(tData);
    I2C_Transmit(tData & ~(EN));

    tData = ((CMD << 4) & 0xF0);
    tData &= ~(RW) & ~(RS);
    tData |= EN | 0x08;
    I2C_Transmit(tData);
    I2C_Transmit(tData & ~(EN));
}

void LCD_DATA(uint8_t DATA)
{
/*
    7  6  5  4  3  2  1  0
    D7 D6 D5 D4 EN RW RS B/L
*/

    uint8_t tData = (DATA & 0xF0);
    tData &= ~(RW);
    tData |= RS | EN | 0x08;
    I2C_Transmit(tData);
    I2C_Transmit(tData & ~(EN));
    
    tData = ((DATA << 4) & 0xF0);
    tData &= ~(RW);
    tData |= RS | EN | 0x08;
    I2C_Transmit(tData);
    I2C_Transmit(tData & ~(EN));

    _delay_us(2);
}

void I2C_Transmit(uint8_t tData)
{
    I2C_Start();

    I2C_SLA_W(SLAVE_ADDR);

    I2C_TxData(tData);

    I2C_Stop();
}