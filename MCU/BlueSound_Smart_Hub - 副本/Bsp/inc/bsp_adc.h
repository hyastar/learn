#ifndef _BSP_ADC_H_
#define _BSP_ADC_H_


#include <stdint.h>


#define ADC_TOTAL_CHANNELS 2


extern volatile uint16_t adc_dma_buffer[ADC_TOTAL_CHANNELS];


void ADC_DMA_Init(void);

void ADC_Start_Conversion(void);

#endif // _ADC_H_

