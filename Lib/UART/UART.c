#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

void UART_init(uint16_t UBR)
{
    UBRR0H = (unsigned char)(UBR >> 8);     // Set BAUD RATE value in USART BAUD RATE REGISTER high register
    UBRR0L = (unsigned char)UBR;            // Set BAUD RATE value in USART BAUD RATE REGISTER low register

    UCSR0B = (1 << TXEN0);          // Set TX bet in USART CONTROL AND STATUS REGISTER n B
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);         // Set UCSZ01 and UCSZ00 bit for 8-bit data length in USART CONTROL AND STATUS REGISTER n C

    UCSR0C |= (1 << UPM01);          // Set UPM01 bit for enabling even parity in USART CONTROL AND STATUS REGISTER n C
}

void SerialWrite(const char* DataToTransmit)
{
    while (*DataToTransmit)
    {
        while ( !(UCSR0A & (1 << UDRE0)) );

        UDR0 = *DataToTransmit;

        if (*DataToTransmit == '\n')
        {
            while (!(UCSR0A & (1 << UDRE0)));
            UDR0 = '\r';
        }

        DataToTransmit++;
    }
}
