
#include "DCMI.h"

void init_DCMI(){
	RCC->AHB2ENR |= RCC_AHB2ENR_DCMIEN;
	DCMI->CR &= ~DCMI_CR_ENABLE;
	DCMI->IER |= DCMI_IER_FRAME_IE | DCMI_IER_OVF_IE | DCMI_IER_ERR_IE;
	DCMI->CR |= DCMI_CR_ESS | DCMI_CR_CM | DCMI_CR_CAPTURE; // embedded sync, snapshot mode(single frame), enable capture
}

void init_DMA_DCMI(uint32_t* p){
	 RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	 DMA2_Stream1->CR &= ~DMA_SxCR_EN;
	 while(DMA2_Stream1->CR & DMA_SxCR_EN);
	 DMA2_Stream1->PAR = (uint32_t)&DCMI->DR;
	 DMA2_Stream1->M0AR = (uint32_t)p;
	 DMA2_Stream1->NDTR = DCMI_FIFO_size;
	 DMA2_Stream1->CR = (DMA_SxCR_MINC | DMA_SxCR_PSIZE_1 | DMA_SxCR_MSIZE_1 | DMA_SxCR_TCIE | DMA_SxCR_CHSEL_0);
	 NVIC_EnableIRQ(DMA2_Stream1_IRQn);
	 NVIC_SetPriority(DMA2_Stream1_IRQn, 0);
}

void Start_DCMI_DMA(){
	 DMA2_Stream1->CR |= DMA_SxCR_EN;
}

void DCMI_start(){
	DCMI->CR |= DCMI_CR_ENABLE;
}

void DCMI_stop(){
	DCMI->CR &= ~DCMI_CR_ENABLE;
}

void init_DCMI_FIFO(struct DCMI_FIFO* f){
	f->read_pointer = 0;
	f->write_pointer = 0;
}

void write_data_DCMI_FIFO(struct DCMI_FIFO* f, uint32_t data){
	f->buffer[f->write_pointer%DCMI_FIFO_size] = data;
	f->write_pointer++;
}

uint32_t read_data_DCMI_FIFO(struct DCMI_FIFO* f){
	uint32_t data;
	data = f->buffer[f->read_pointer%DCMI_FIFO_size];
	f->read_pointer++;
	return data;
}

uint8_t DCMI_FIFO_isEmpty(struct DCMI_FIFO* f){
	return (f->read_pointer == f->write_pointer) ? 1 : 0;
}
