
#define CPU_FREQ 16000000
#define BAUD 9600
#define BAUD_RATE ((CPU_FREQ/16/BAUD) - 1)

void UART_init(uint16_t);
void SerialWrite(const char*);