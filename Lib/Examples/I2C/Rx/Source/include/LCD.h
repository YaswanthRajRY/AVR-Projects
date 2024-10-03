#define F_CPU 16000000UL
#define EN PORTB5
#define RW PORTB4
#define RS PORTB3
#define DDR_CMD DDRB
#define DDR_DATA DDRD
#define LCD_CMD_PORT PORTB
#define LCD_DATA_PORT PORTD

void init_LCD(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);