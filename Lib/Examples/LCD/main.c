#include <avr/io.h>
#include <util/delay.h>

#include "LCD.h"

void LCD_Write_String(char*);

int main(void)
{
    init_LCD();
    
    _delay_ms(10);
    LCD_CMD(0x0C);
    _delay_ms(10);

    while (1)
    {
        LCD_Write_String("Hello World !!!");
        _delay_ms(1000);
        LCD_Write_String("\rPRGM TEST SUCESS");
        _delay_ms(3000);
        LCD_CMD(0x01);
    }
}

void LCD_Write_String(char *a)
{
    if (*a == '\r')
    {
        LCD_CMD(0xC0);
        for (int i = 0; i < 16; i++)
        {
        LCD_DATA(' ');
        }
        LCD_CMD(0xC0);
        a++;
    }
    else
    {
        LCD_CMD(0x80);
        for (int i = 0; i < 16; i++)
        {
        LCD_DATA(' ');
        }
        LCD_CMD(0x80);
    }

    while (*a) {
        LCD_DATA(*a++);                // Write each character in the string
    }
}