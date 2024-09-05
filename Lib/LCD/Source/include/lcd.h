#define F_CPU 16000000UL
#define LCD_DATA PORTD
#define LCD_CMD PORTB
#define EN PORTB5
#define RW PORTB4
#define RS PORTB3

void init_LCD(void);
void LCD_cmd(unsigned char);
void LCD_write(unsigned char);
void LCD_Write_String(char*);
