
#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx.h"
#include "OV7670.h"
#include "UART.h"

void init_I2C();
void write_data_I2C(uint8_t data, uint8_t adr, uint8_t reg);

#endif /* I2C_H_ */
