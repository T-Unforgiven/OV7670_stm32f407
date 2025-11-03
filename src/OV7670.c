
#include "OV7670.h"

const uint8_t OV7670_reg[][2] =
{
  /* Color mode and resolution settings */
  {OV7670_REG_COM7,             0x14},         // QVGA, RGB
  //{OV7670_REG_RGB444,           0x00},         // RGB444 Disable
  {OV7670_REG_COM15,            0xD0},         // RGB565
  {OV7670_REG_TSLB,             0xC},         // UYVY
  {OV7670_REG_COM13,            0x80},         // gamma enable, UV auto adjust, UYVY
  {OV7670_REG_RSRVD,            0x84},         // Important!
  /* Clock settings */
  {OV7670_REG_COM3,             0x04},         // DCW enable
  {OV7670_REG_COM14,            0x19},         // manual scaling, pclk/=2
  {OV7670_REG_SCALING_XSC,      0x3A},         // scaling_xsc
  {OV7670_REG_SCALING_YSC,      0x35},         // scaling_ysc
  {OV7670_REG_SCALING_DCWCTR,   0x11},         // down sample by 2
  {OV7670_REG_SCALING_PCLK_DIV, 0xf1},         // DSP clock /= 2
  /* Windowing */
  {OV7670_REG_HSTART,           0x16},         // HSTART
  {OV7670_REG_HSTOP,            0x04},         // HSTOP
  {OV7670_REG_HREF,             0x80},         // HREF
  {OV7670_REG_VSTRT,            0x03},         // VSTART =  14 ( = 3 * 4 + 2)
  {OV7670_REG_VSTOP,            0x7b},         // VSTOP  = 494 ( = 123 * 4 + 2)
  {OV7670_REG_VREF,             0x0a},         // VREF (VSTART_LOW = 2, VSTOP_LOW = 2)
  /* Color matrix coefficient */
#if 0
  {OV7670_REG_MTX1,             0xb3},
  {OV7670_REG_MTX2,             0xb3},
  {OV7670_REG_MTX3,             0x00},
  {OV7670_REG_MTX4,             0x3d},
  {OV7670_REG_MTX5,             0xa7},
  {OV7670_REG_MTX6,             0xe4},
  {OV7670_REG_MTXS,             0x9e},
#else
  {OV7670_REG_MTX1,             0x80},
  {OV7670_REG_MTX2,             0x80},
  {OV7670_REG_MTX3,             0x00},
  {OV7670_REG_MTX4,             0x22},
  {OV7670_REG_MTX5,             0x5E},
  {OV7670_REG_MTX6,             0x80},
  {OV7670_REG_MTXS,             0x9E},
#endif
//{OV7670_REG_COM8,             0x84},
//{OV7670_REG_COM9,             0x0a},         // AGC Ceiling = 2x
//{0x5FU,                       0x2f},         // AWB B Gain Range (empirically decided)
        // without this bright scene becomes yellow (purple). might be because of color matrix
//{0x60U,                       0x98},         // AWB R Gain Range (empirically decided)
//{0x61U,                       0x70},         // AWB G Gain Range (empirically decided)
  {OV7670_REG_COM16,            0x38},         // edge enhancement, de-noise, AWG gain enabled
  /* gamma curve */
#if 1
  {OV7670_REG_GAM1,             16},
  {OV7670_REG_GAM2,             30},
  {OV7670_REG_GAM3,             53},
  {OV7670_REG_GAM4,             90},
  {OV7670_REG_GAM5,             105},
  {OV7670_REG_GAM6,             118},
  {OV7670_REG_GAM7,             130},
  {OV7670_REG_GAM8,             140},
  {OV7670_REG_GAM9,             150},
  {OV7670_REG_GAM10,            160},
  {OV7670_REG_GAM11,            180},
  {OV7670_REG_GAM12,            195},
  {OV7670_REG_GAM13,            215},
  {OV7670_REG_GAM14,            230},
  {OV7670_REG_GAM15,            244},
  {OV7670_REG_SLOP,             16},
#else
  /* gamma = 1 */
  {OV7670_REG_GAM1,             4},
  {OV7670_REG_GAM2,             8},
  {OV7670_REG_GAM3,             16},
  {OV7670_REG_GAM4,             32},
  {OV7670_REG_GAM5,             40},
  {OV7670_REG_GAM6,             48},
  {OV7670_REG_GAM7,             56},
  {OV7670_REG_GAM8,             64},
  {OV7670_REG_GAM9,             72},
  {OV7670_REG_GAM10,            80},
  {OV7670_REG_GAM11,            96},
  {OV7670_REG_GAM12,            112},
  {OV7670_REG_GAM13,            144},
  {OV7670_REG_GAM14,            176},
  {OV7670_REG_GAM15,            208},
  {OV7670_REG_SLOP,             64},
#endif
  /* FPS */
//{OV7670_REG_DBLV,             0x4a},         // PLL  x4
  {OV7670_REG_CLKRC,            0x00},         // Pre-scalar = 1/1
  /* Others */
  {OV7670_REG_MVFP,             0x31},         // Mirror flip
//{OV7670_REG_COM17,            0x08},         // Test screen with color bars
  {OV7670_REG_DUMMY,            OV7670_REG_DUMMY},
};

/* camera clk 1.346 MHz */

void init_TIM_clk(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = 1-1;
	TIM2->ARR = 20-1;
	TIM2->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
	TIM2->CCER |= TIM_CCER_CC2E;
	TIM2->CCR2 = 10;
}

void stop_camera_clk(){
	TIM2->CR1 &= ~TIM_CR1_CEN;
}

void start_camera_clk(){
	TIM2->CR1 |= TIM_CR1_CEN;
}

void delay_1us(){
	volatile int i = 3;
	while(i > 0)
		i--;
}

void delay_45us(){
	volatile int i = 200;
	while(i > 0)
		i--;
}

void reset_OV7670(){
	write_data_I2C(0x80, OV7670_write_adress, OV7670_REG_COM7);
	delay_45us();
}

void init_OV7670(){
	reset_OV7670();
	for (uint32_t i = 0; OV7670_reg[i][0] != OV7670_REG_DUMMY; i++){
		write_data_I2C(OV7670_reg[i][1], OV7670_write_adress, OV7670_reg[i][0]);
		delay_1us();
	}
}




