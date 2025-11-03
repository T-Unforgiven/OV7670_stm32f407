
#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"

#define UART_FIFO_size 2048

struct UART_FIFO{
	uint8_t buffer[UART_FIFO_size];
	uint16_t read_pointer;
	uint16_t write_pointer;
};

void init_UART();
void init_UART_DMA(uint8_t* mem_adr);
void start_UART_DMA();
void transfer_data_UART(uint8_t data);
uint8_t read_data_UART();
void init_UART_FIFO(struct UART_FIFO* f);
void write_data_UART_FIFO(struct UART_FIFO* f, uint8_t data);
uint8_t read_data_UART_FIFO(struct UART_FIFO* f);
uint8_t UART_FIFO_isEmpty(struct UART_FIFO* f);

#endif /* UART_H_ */
