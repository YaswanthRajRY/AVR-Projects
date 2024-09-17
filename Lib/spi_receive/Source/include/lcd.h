#define F_CPU 16000000UL
#define LCD_DATA PORTD
#define LCD_CMD PORTC
#define EN PORTC2
#define RW PORTC1
#define RS PORTC0

void init_LCD(void);
void LCD_cmd(unsigned char);
void LCD_write(unsigned char);
void LCD_Write_String(char*);
