#include <avr/io.h>
#include <util/delay.h>

void init_SPI_Master(void);
void init_SPI_Slave(void);
void SPI_Transmit(unsigned char);
char SPI_Recive();