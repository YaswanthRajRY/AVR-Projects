#include <avr/io.h>
#include <util/delay.h>

#include "UART.h"
#include "lcd.h"

uint8_t xIndex = 0;
char buffer[20];

char* get_UART_data(void);
void send_to_LCD(char*);

int main(void)
{
    DDRD = 0xF0;
    DDRB = 0x38;

    init_UART();
    init_LCD();

    while (1)
    {
        char* printData = get_UART_data();
        send_to_LCD(printData);
    }
}

char* get_UART_data()
{
    uint8_t reset = 0;
    while (1)
    {
        reset += 1;
        if (reset >= 255)
        {
            break;
        }
        char temp = UART_Receive();
        if (temp == '\n')
        {
            buffer[xIndex] = '\0';
            xIndex = 0;
            break;
        }

        buffer[xIndex++] = temp;
    }

    return buffer;
}

void send_to_LCD(char* pData)
{
    LCD_Write_String(pData);
}