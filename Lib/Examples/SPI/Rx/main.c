#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "I2C.h"
#include "SPI.h"
#include "UART.h"
#include "LCD_I2C.h"

void LCD_print(char*);
void print_Temp_Humd(void);
char* convert_toString(uint8_t);
void get_SPI_Data(uint8_t*, uint8_t*);
void print_DHT11_values(uint8_t, uint8_t);

uint8_t SPI_Buffer[5] = {0, 0, 0, 0, 0};
static uint8_t temperature = 0;
static uint8_t humidity = 0;
uint8_t i = 0;

int main(void)
{
    init_I2C();
    init_UART();
    init_LCD_I2C();
    init_SPI_Slave();

    print_Temp_Humd();

    while (1)
    {
        get_SPI_Data(&temperature, &humidity);
        print_DHT11_values(temperature, humidity);
    }
}

void get_SPI_Data(uint8_t* temp, uint8_t* humd)
{
    while (SPI_Recive() != 0xFF);

    for (i = 0; i < 5; i++)
    {
        uint8_t data = SPI_Recive();
        
        SPI_Buffer[i] = data;
    }
    
    *temp = SPI_Buffer[2];
    *humd = SPI_Buffer[0];
}

void print_Temp_Humd()
{
    LCD_CMD(0x80);
    LCD_print("Temp: ");
    
    LCD_CMD(0xC0);
    LCD_print("Humd: ");    
}

char* convert_toString(uint8_t value)
{
    char* str = (char*)malloc(sizeof(char) * 4);
    uint8_t i = 0;
    uint8_t j = 0;

    while (value)
    {
        str[i++] = (value%10) + '0';
        value /= 10;
    }
    str[i--] = '\0';

    while (j < i)
    {
        char temp = str[j];
        str[j] = str[i];
        str[i] = temp;
        i--; j++;
    }

    return str;
}

void print_DHT11_values(uint8_t Tvalue, uint8_t Hvalue)
{
    char* ctemp = convert_toString(Tvalue);
    char* chumd = convert_toString(Hvalue);

    LCD_CMD((0x80) + 6);
    LCD_print(ctemp);
    LCD_DATA(0xDF);

    LCD_CMD((0xC0) + 6);
    LCD_print(chumd);
    LCD_DATA('%');

    free(ctemp);
    free(chumd);
}

void LCD_print(char* s)
{
    while(*s)
    {
        LCD_DATA(*s++);
    }
}