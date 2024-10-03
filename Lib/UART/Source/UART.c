#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

void init_UART()
{
    UBRR0H = (unsigned char)(BAUD_RATE >> 8);     // Set BAUD RATE value in USART BAUD RATE REGISTER high register
    UBRR0L = (unsigned char)BAUD_RATE;            // Set BAUD RATE value in USART BAUD RATE REGISTER low register

    UCSR0B = (1 << TXEN0) | (1 << RXEN0);         // Set TX bet in USART CONTROL AND STATUS REGISTER n B
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);       // Set UCSZ01 and UCSZ00 bit for 8-bit data length in USART CONTROL AND STATUS REGISTER n C

    UCSR0C |= (1 << UPM01);                       // Set UPM01 bit for enabling even parity in USART CONTROL AND STATUS REGISTER n C
}

void UART_Transmit(unsigned char tData)
{
    while (!(UCSR0A & (1 << UDRE0)));		 // wait for transmt buffer to be empty by checking UDRE0 flag

    UDR0 = tData;				 // Load data
}

char UART_Receive()
{
    while (!(UCSR0A & (1 << RXC0)));		 // wait for data to be received

    return UDR0;				 // return content in UDR0 register
}
