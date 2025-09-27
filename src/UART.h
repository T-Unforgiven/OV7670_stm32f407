
#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"

void init_UART();
void transfer_data_UART(uint8_t data);
uint8_t read_data_UART();

#endif /* UART_H_ */
