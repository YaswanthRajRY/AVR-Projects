#define F_CPU 16000000UL
#define EN 0x04
#define RW 0x02
#define RS 0x01

void init_LCD_I2C(void);
void LCD_CMD(uint8_t);
void LCD_DATA(uint8_t);
void I2C_Transmit(uint8_t);
