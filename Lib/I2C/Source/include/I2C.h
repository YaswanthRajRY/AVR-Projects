#include <avr/io.h>
#include <util/delay.h>

#define SLAVE_ADDR 0x27

void init_I2C(void);
void init_I2C_Slave(void);

uint8_t I2C_Start(void);
uint8_t I2C_Stop(void);

uint8_t I2C_SLA_W(uint8_t);
uint8_t I2C_SLA_R(uint8_t);


uint8_t I2C_Slave_SLA_R(void);
uint8_t I2C_Slave_SLA_W(void);

uint8_t I2C_TxData(uint8_t);
uint8_t I2C_TxData_nBytes(uint8_t*, uint8_t);

uint8_t I2C_RxData(uint8_t*);
uint8_t I2C_RxData_nBytes(uint8_t*, uint8_t);

uint8_t I2C_SlaveTx(uint8_t);
uint8_t I2C_SlaveTx_nBytes(uint8_t*, uint8_t);

uint8_t I2C_SlaveRx(uint8_t*);
uint8_t I2C_SlaveRx_nBytes(uint8_t*, uint8_t);