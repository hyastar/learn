#include "bsp_dma.h"
#include "stm32f10x.h"


void DMA_Init_Common(void)
{
RCC->AHBENR |= RCC_AHBENR_DMA1EN;
}

