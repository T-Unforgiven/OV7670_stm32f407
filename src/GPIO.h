
#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f4xx.h"

#define setAF(num_pin, num_func) (num_func << ((num_pin%8)*4))

void init_GPIO();
void conf_GPIO();
void start_GPIO();

#endif /* GPIO_H_ */
