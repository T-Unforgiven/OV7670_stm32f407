
#include "UART.h"

void init_UART(){
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	USART1->BRR = (26880000/115200); // set 115200 baudrate
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
	USART1->CR1 |= USART_CR1_TXEIE;
	//USART1->CR1 |= USART_CR1_RXNEIE;
	NVIC_SetPriority(USART1_IRQn, 1);
	NVIC_EnableIRQ(USART1_IRQn);
	USART1->CR1 |= USART_CR1_UE;
}

void transfer_data_UART(uint8_t data){
	USART1->DR = data;
}

uint8_t read_data_UART(){
	uint8_t data;
	data = USART1->DR;
	return data;
}


