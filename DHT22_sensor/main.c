#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

uint8_t xData[4] = {0, 0, 0, 0};

void ReadSensor(void);
void DisplaySensorData(void);
char* Tostring(uint16_t);

int main(void)
{
    DDRD |= (1 << DDD2) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
    DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3);

    PORTD |= (1 << PORTD2);

    _delay_ms(10);

    init_LCD();

    while (1)
    {
        ReadSensor();
        _delay_ms(1000);
    }
}

void ReadSensor()
{
    uint8_t xBuffer[5] = {0, 0, 0, 0, 0};
    uint8_t i, j, reset;
    reset = 0;

    DDRD |= (1 << DDD2);
    PORTD &= ~(1 << PORTD2);

    _delay_ms(20);

    PORTD |= (1 << PORTD2);
    DDRD &= ~(1 << DDD2);

    _delay_us(30);

    while (PIND & (1 << PIN2))
    {
        return;
    }

    _delay_us(80);

    while (!(PIND & (1 << PIN2)))
    {
        return;
    }

    _delay_us(80);

    for (i=0; i < 5; i++)
    {
        for (j=0; j < 8; j++)
        {
            reset = 0;
            while (!(PIND & (1 << PIN2)))
            {
                _delay_us(2);
                reset += 2;

                if (reset > 50)
                {
                    return;
                }
            }

            _delay_us(30);

            if (PIND & (1 << PIN2))
            {
                xBuffer[i] |= (1 << (7-j)); 
            }
            
            _delay_us(40);
        }
    }

    if (((uint8_t)(xBuffer[0] + xBuffer[1] + xBuffer[2] + xBuffer[3])) != xBuffer[4])
    {
        return;
    }

    for (i = 0; i<4; i++)
    {
        xData[i] = xBuffer[i];
    }

    DisplaySensorData();
}

void DisplaySensorData(void)
{
    LCD_cmd(0x01);
    LCD_cmd(0x80);
    _delay_us(10);

    char* temp = Tostring(xData[2]*256 + xData[3]);
    LCD_Write_String("Temp: ");
    LCD_Write_String(temp);
    LCD_Write_String("%");

    LCD_cmd(0xC0);
    
    char* humd = Tostring(xData[0]*256 + xData[1]);
    LCD_Write_String("Humidity: ");
    LCD_Write_String(humd);
    LCD_Write_String("%");
}

char* Tostring(uint16_t num)
{
    static char string[10];
    uint8_t xint = num/10;
    uint8_t xfloat = num%10;
    uint8_t i = 0;
    uint8_t j = 0;

    string[i++] = xfloat + '0';
    string[i++] = '.';

    while (xint)
    {
        string[i++] = (xint % 10) + '0';
        xint /= 10;
    } 
    string[i] = '\0';
    
    i--;
    while (j<i)
    {
        char temp = string[j];
        string[j] = string[i];
        string[i] = temp;
        j++; i--;
    }

    return string;
}
