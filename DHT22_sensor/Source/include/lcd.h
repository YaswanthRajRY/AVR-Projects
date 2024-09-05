#define F_CPU 16000000UL
#define LCD_DATA PORTB
#define LCD_CMD PORTD
#define EN PORTD7
#define RW PORTD6
#define RS PORTD5

void init_LCD(void);
void LCD_cmd(unsigned char);
void LCD_write(unsigned char);
void LCD_Write_String(char*);
