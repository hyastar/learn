#include "bsp_adc.h"
#include "bsp_dma.h"
#include "delay.h"
#include "stm32f10x.h"


#define TEMP_SENSOR_ADC_CHANNEL 16 
#define MQ5_ADC_CHANNEL 1 


volatile uint16_t adc_dma_buffer[ADC_TOTAL_CHANNELS];


void ADC_DMA_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;
    RCC->AHBENR  |= RCC_AHBENR_DMA1EN;

    GPIOA->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1);

    RCC->CFGR &= ~RCC_CFGR_ADCPRE;
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    ADC1->CR2 |= ADC_CR2_ADON;
    delay_ms(1);

    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while (ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL);

    ADC1->CR1  = ADC_CR1_SCAN; 
    ADC1->CR2 |= ADC_CR2_CONT | ADC_CR2_DMA; 
    ADC1->CR2 |= ADC_CR2_TSVREFE; 


    ADC1->SQR1 = (ADC_TOTAL_CHANNELS - 1) << 20;
    ADC1->SQR3 = (TEMP_SENSOR_ADC_CHANNEL << 0) | (MQ5_ADC_CHANNEL << 5);


    ADC1->SMPR1 |= (7 << (3 * (TEMP_SENSOR_ADC_CHANNEL - 10))); 
    ADC1->SMPR2 |= (7 << (3 * MQ5_ADC_CHANNEL)); 


    DMA1_Channel1->CPAR  = (uint32_t)&ADC1->DR;
    DMA1_Channel1->CMAR  = (uint32_t)adc_dma_buffer;
    DMA1_Channel1->CNDTR = ADC_TOTAL_CHANNELS;
    DMA1_Channel1->CCR   = DMA_CCR_MINC | DMA_CCR_CIRC; 
    DMA1_Channel1->CCR  |= DMA_CCR_PSIZE_0 | DMA_CCR_MSIZE_0; 
    DMA1_Channel1->CCR  |= DMA_CCR_EN;


    ADC1->CR2 |= ADC_CR2_ADON;
    delay_ms(1);
    ADC1->CR2 |= ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_EXTTRIG; 
    //ADC1->CR2 |= ADC_CR2_SWSTART;
}

void ADC_Start_Conversion(void)
{
    ADC1->CR2 |= ADC_CR2_SWSTART;
}
