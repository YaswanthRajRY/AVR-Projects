#include <avr/io.h>
#include <util/delay.h>   
#include "LCD.h"

void LCD_CMD(unsigned char cmd)
{
    // Send higher nibble
    LCD_DATA_PORT = (cmd & 0xF0);            // Set data lines for the higher nibble
    LCD_CMD_PORT &= ~(1 << RS);              // RS = 0 for command
    LCD_CMD_PORT &= ~(1 << RW);              // RW = 0 for write
    LCD_CMD_PORT |= (1 << EN);               // Enable high
    _delay_us(1);                       // Short delay
    LCD_CMD_PORT &= ~(1 << EN);              // Enable low

    // Send lower nibble
    LCD_DATA_PORT = ((cmd << 4) & 0xF0);     // Set data lines for the lower nibble
    LCD_CMD_PORT |= (1 << EN);               // Enable high
    _delay_us(1);                       // Short delay
    LCD_CMD_PORT &= ~(1 << EN);              // Enable low

    _delay_ms(2);                       // Command execution delay
}

void LCD_DATA(unsigned char data)
{
    // Send higher nibble
    LCD_DATA_PORT = (data & 0xF0);           // Set data lines for the higher nibble
    LCD_CMD_PORT |= (1 << RS);               // RS = 1 for data
    LCD_CMD_PORT &= ~(1 << RW);              // RW = 0 for write
    LCD_CMD_PORT |= (1 << EN);               // Enable high
    _delay_us(1);                       // Short delay
    LCD_CMD_PORT &= ~(1 << EN);              // Enable low

    // Send lower nibble
    LCD_DATA_PORT = ((data << 4) & 0xF0);    // Set data lines for the lower nibble
    LCD_CMD_PORT |= (1 << EN);               // Enable high
    _delay_us(1);                       // Short delay
    LCD_CMD_PORT &= ~(1 << EN);              // Enable low

    _delay_ms(2);                       // Data write delay
}

void init_LCD(void)
{
    DDR_CMD |= 0x38;
    DDR_DATA |= 0xF0;

    _delay_ms(20);                      // Wait for the LCD to power up

    LCD_CMD(0x02);                      // Initialize LCD in 4-bit mode
    _delay_ms(5);                       // Wait for initialization to complete

    LCD_CMD(0x28);                      // Function set: 4-bit mode, 2 lines, 5x8 font
    _delay_ms(1);
    
    LCD_CMD(0x0C);                      // Display on, cursor off, blink off
    _delay_ms(1);
    
    LCD_CMD(0x01);                      // Clear display
    _delay_ms(2);                       // Longer delay for clearing display
    
    LCD_CMD(0x06);                      // Entry mode: Increment cursor
    _delay_ms(1);
    
    LCD_CMD(0x80);                      // Set cursor to the beginning of the first line
    _delay_ms(1);
}