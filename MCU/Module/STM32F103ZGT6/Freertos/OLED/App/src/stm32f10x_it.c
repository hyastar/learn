#include "stm32f10x_it.h" 
#include "user_config.h"
#include "bsp_led.h"

#include "FreeRTOS.h"
#include "task.h"
#include "user_config.h"

// �����ⲿ�� FreeRTOS SysTick ������
extern void xPortSysTickHandler(void);
/**
  * @brief  TIM2�жϷ����� (���ȼ�4)
  */
void TIM2_IRQHandler(void)
{
    if ((TIM2->SR & TIM_SR_UIF) != 0)
    {
        TIM2->SR &= ~TIM_SR_UIF;
        //LED0_Toggle();
        //printf("TIM2���ȼ�=4,ִ��....\r\n");
        ulHighFrequencyTimerTicks++;
    }
}

/**
  * @brief  TIM3�жϷ����� (���ȼ�6)
  */
void TIM3_IRQHandler(void)
{
    if ((TIM3->SR & TIM_SR_UIF) != 0)
    {
        TIM3->SR &= ~TIM_SR_UIF;
        //LED1_Toggle();
        //printf("TIM3���ȼ�=6,ִ��....\r\n");
    }
}
