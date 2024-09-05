#include <avr/io.h>
#include <util/delay.h>   
#include "lcd.h"

// Function to send a command to the LCD
void LCD_cmd(unsigned char cmd)
{
    // Send higher nibble
    LCD_DATA = (cmd & 0xF0);      // Set data lines for the higher nibble
    LCD_CMD &= ~(1 << RS);       // RS = 0 for command
    LCD_CMD &= ~(1 << RW);       // RW = 0 for write
    LCD_CMD |= (1 << EN);        // Enable high
    _delay_us(1);                // Short delay
    LCD_CMD &= ~(1 << EN);       // Enable low

    // Send lower nibble
    LCD_DATA = ((cmd << 4) & 0xF0); // Set data lines for the lower nibble
    LCD_CMD |= (1 << EN);        // Enable high
    _delay_us(1);                // Short delay
    LCD_CMD &= ~(1 << EN);       // Enable low

    _delay_ms(2);                // Command execution delay
}

// Function to write data to the LCD
void LCD_write(unsigned char data)
{
    // Send higher nibble
    LCD_DATA = (data & 0xF0);      // Set data lines for the higher nibble
    LCD_CMD |= (1 << RS);         // RS = 1 for data
    LCD_CMD &= ~(1 << RW);        // RW = 0 for write
    LCD_CMD |= (1 << EN);         // Enable high
    _delay_us(1);                 // Short delay
    LCD_CMD &= ~(1 << EN);        // Enable low

    // Send lower nibble
    LCD_DATA = ((data << 4) & 0xF0); // Set data lines for the lower nibble
    LCD_CMD |= (1 << EN);         // Enable high
    _delay_us(1);                 // Short delay
    LCD_CMD &= ~(1 << EN);        // Enable low

    _delay_ms(2);                 // Data write delay
}

// Function to initialize the LCD
void init_LCD(void)
{
    // Initial delay and setup for 4-bit mode
    _delay_ms(20);               // Wait for the LCD to power up

    // Function set command: 4-bit mode, 2 lines, 5x8 font
    LCD_cmd(0x02);               // Initialize LCD in 4-bit mode
    _delay_ms(5);                // Wait for initialization to complete

    LCD_cmd(0x28);               // Function set: 4-bit mode, 2 lines, 5x8 font
    _delay_ms(1);
    
    LCD_cmd(0x0C);               // Display on, cursor off, blink off
    _delay_ms(1);
    
    LCD_cmd(0x01);               // Clear display
    _delay_ms(2);                // Longer delay for clearing display
    
    LCD_cmd(0x06);               // Entry mode: Increment cursor
    _delay_ms(1);
    
    LCD_cmd(0x80);               // Set cursor to the beginning of the first line
    _delay_ms(1);
}

// Function to write a string to the LCD
void LCD_Write_String(char *a)
{
    while (*a) {
        LCD_write(*a++);    // Write each character in the string
    }
}
