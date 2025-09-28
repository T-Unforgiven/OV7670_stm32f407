
#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"

#define FIFO_size 1024

struct FIFO{
	uint8_t buffer[FIFO_size];
	uint16_t read_pointer;
	uint16_t write_pointer;
};

void init_UART();
void transfer_data_UART(uint8_t data);
uint8_t read_data_UART();
void init_FIFO(struct FIFO* f);
void write_data_FIFO(struct FIFO* f, uint8_t data);
uint8_t read_data_FIFO(struct FIFO* f);

#endif /* UART_H_ */
