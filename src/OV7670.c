
#include "OV7670.h"

/* camera clk 1.346 MHz */

void init_TIM_clk(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = 1-1;
	TIM2->ARR = 20-1;
	TIM2->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
	TIM2->CCER |= TIM_CCER_CC2E;
	TIM2->CCR2 = 10;
	TIM2->CR1 |= TIM_CR1_CEN;
}
