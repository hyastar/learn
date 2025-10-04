#include "bsp_timer.h"
#include "sys.h" 

void General_Timer_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
 
    TIM2->PSC = 72 - 1;      
    TIM2->ARR = 10 - 1;    
    TIM2->DIER |= TIM_DIER_UIE; 

    NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 4, 0));
    NVIC_EnableIRQ(TIM2_IRQn);

    TIM2->CR1 |= TIM_CR1_CEN;  


    TIM3->PSC = 7200 - 1;
    TIM3->ARR = 10000 - 1;
    TIM3->DIER |= TIM_DIER_UIE;

    NVIC_SetPriority(TIM3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 6, 0));
    NVIC_EnableIRQ(TIM3_IRQn);

    TIM3->CR1 |= TIM_CR1_CEN;
}
