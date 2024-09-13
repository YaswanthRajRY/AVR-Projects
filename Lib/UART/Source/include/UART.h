
#define CPU_FREQ 16000000
#define BAUD 9600
#define BAUD_RATE ((CPU_FREQ/16/BAUD) - 1)

void init_UART();
void UART_Transmit(unsigned char);
char UART_Receive(void);
