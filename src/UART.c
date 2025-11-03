
#include "UART.h"

void init_UART(){
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	USART1->BRR = (26880000/115200); // set 115200 baudrate
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
	//USART1->CR1 |= USART_CR1_TXEIE;
	USART1->CR3 |= USART_CR3_DMAT;
	USART1->CR1 |= USART_CR1_RXNEIE;
	NVIC_SetPriority(USART1_IRQn, 3);
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

void init_UART_DMA(uint8_t* mem_adr){
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	DMA2_Stream7->CR &= ~DMA_SxCR_EN;
	while(DMA2_Stream7->CR & DMA_SxCR_EN);
	DMA2_Stream7->CR = DMA_SxCR_CHSEL_2 |
	                   DMA_SxCR_MINC |
	                   DMA_SxCR_DIR_0 |
	                   DMA_SxCR_TCIE;

	DMA2_Stream7->PAR = (uint32_t)&(USART1->DR);
	DMA2_Stream7->M0AR = (uint32_t)mem_adr;
	DMA2_Stream7->NDTR = UART_FIFO_size;
	NVIC_EnableIRQ(DMA2_Stream7_IRQn);
	NVIC_SetPriority(DMA2_Stream7_IRQn, 1);
}

void start_UART_DMA(){
	DMA2_Stream7->CR |= DMA_SxCR_EN;
}

void init_UART_FIFO(struct UART_FIFO* f){
	f->read_pointer = 0;
	f->write_pointer = 0;
}

void write_data_UART_FIFO(struct UART_FIFO* f, uint8_t data){
	f->buffer[f->write_pointer%UART_FIFO_size] = data;
	f->write_pointer++;
}

uint8_t read_data_UART_FIFO(struct UART_FIFO* f){
	uint8_t data;
	data = f->buffer[f->read_pointer%UART_FIFO_size];
	f->read_pointer++;
	return data;
}

uint8_t UART_FIFO_isEmpty(struct UART_FIFO* f){
	return (f->read_pointer == f->write_pointer) ? 1 : 0;
}
