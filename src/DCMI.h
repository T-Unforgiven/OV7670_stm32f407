
#ifndef DCMI_H_
#define DCMI_H_

#include "stm32f4xx.h"

#define IMG_WIDTH 680
#define IMG_HEIGHT 480
#define IMG_SIZE (IMG_WIDTH * IMG_HEIGHT * 2)

void init_DCMI();
void DCMI_start();
void DCMI_stop();

#endif /* DCMI_H_ */
