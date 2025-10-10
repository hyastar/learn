#include "delay.h"

void delay_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    TIM6->PSC = 72 - 1;
    TIM6->ARR = 0xFFFF;

    TIM6->CR1 |= TIM_CR1_CEN;
}

void delay_us(uint32_t us)
{
    TIM6->CNT = 0;
    while(TIM6->CNT < us);
}

void delay_ms(uint32_t ms)
{
    for(uint32_t i = 0; i < ms; i++)
    {
        delay_us(1000);
    }
}

void delay_s(uint32_t s)
{
    for(uint32_t i = 0; i < s; i++)
    {
        delay_ms(1000);
    }
}
