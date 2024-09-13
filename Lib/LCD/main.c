#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

int main(void)
{
    DDRD = 0xFF;
    DDRB = 0x38;

    init_LCD();
    _delay_ms(10);
    LCD_cmd(0x0C);
    _delay_ms(10);

    while (1)
    {
        LCD_cmd(0x80);
        LCD_Write_String("Hello World");
        _delay_ms(1000);
        LCD_cmd(0xC0);
        LCD_Write_String("PRGM TEST");
        _delay_ms(3000);
        LCD_cmd(0x01);
    }
}