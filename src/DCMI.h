
#ifndef DCMI_H_
#define DCMI_H_

#include "stm32f4xx.h"

#define IMG_WIDTH 640
#define IMG_HEIGHT 480
#define IMG_SIZE (IMG_WIDTH * IMG_HEIGHT * 2)

#define DCMI_FIFO_size 512

struct DCMI_FIFO{
	uint32_t buffer[DCMI_FIFO_size];
	uint16_t read_pointer;
	uint16_t write_pointer;
};

void init_DCMI();
void init_DMA_DCMI(uint32_t* p);
void Start_DCMI_DMA();
void DCMI_start();
void DCMI_stop();
void init_DCMI_FIFO(struct DCMI_FIFO* f);
void write_data_DCMI_FIFO(struct DCMI_FIFO* f, uint32_t data);
uint32_t read_data_DCMI_FIFO(struct DCMI_FIFO* f);
uint8_t DCMI_FIFO_isEmpty(struct DCMI_FIFO* f);

#endif /* DCMI_H_ */
