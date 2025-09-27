
#include "DCMI.h"

void init_DCMI(){
	RCC->AHB2ENR |= RCC_AHB2ENR_DCMIEN;
	DCMI->CR &= ~DCMI_CR_ENABLE;
	DCMI->IER |= DCMI_IER_FRAME_IE | DCMI_IER_OVF_IE | DCMI_IER_ERR_IE;
	DCMI->CR |= DCMI_CR_ESS | DCMI_CR_CM | DCMI_CR_CAPTURE; // embedded sync, snapshot mode(single frame), enable capture
}

void DCMI_start(){
	DCMI->CR |= DCMI_CR_ENABLE;
}

void DCMI_stop(){
	DCMI->CR &= ~DCMI_CR_ENABLE;
}
