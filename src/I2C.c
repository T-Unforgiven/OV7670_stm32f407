
#include "I2C.h"

void init_I2C(){
	RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
	I2C2->CR1 &= ~I2C_CR1_PE;
	I2C2->CR2 |= (13 << 0); // APB1 freq in MHz
	I2C2->CCR |= 65; // setting 100 KHz
	I2C2->TRISE |= 13+1;
	I2C2->CR1 |= I2C_CR1_PE;
}

void write_data_I2C(uint8_t data, uint8_t adr, uint8_t reg){
	I2C2->CR1 |= I2C_CR1_START;
	while(!(I2C2->SR1 & I2C_SR1_SB));
	I2C2->DR = adr;
	while(!(I2C2->SR1 & I2C_SR1_ADDR));
	(void)I2C2->SR2;
	while(!(I2C2->SR1 & I2C_SR1_TXE));
	I2C2->DR = reg;
	while(!(I2C2->SR1 & I2C_SR1_TXE));
	I2C2->DR = data;
	while(!(I2C2->SR1 & I2C_SR1_BTF));
	I2C2->CR1 |= I2C_CR1_STOP;
}


