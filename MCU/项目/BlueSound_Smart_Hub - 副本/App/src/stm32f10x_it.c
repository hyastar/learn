#include "stm32f10x_it.h" 
#include "user_config.h"
#include "bsp_led.h"

#include "FreeRTOS.h"
#include "task.h"
#include "user_config.h"

// 声明外部的 FreeRTOS SysTick 处理函数
extern void xPortSysTickHandler(void);
/**
  * @brief  TIM2中断服务函数 (优先级4)
  */
void TIM2_IRQHandler(void)
{
    if ((TIM2->SR & TIM_SR_UIF) != 0)
    {
        TIM2->SR &= ~TIM_SR_UIF;
        //LED0_Toggle();
        //printf("TIM2优先级=4,执行....\r\n");
        ulHighFrequencyTimerTicks++;
    }
}

/**
  * @brief  TIM3中断服务函数 (优先级6)
  */
void TIM3_IRQHandler(void)
{
    if ((TIM3->SR & TIM_SR_UIF) != 0)
    {
        TIM3->SR &= ~TIM_SR_UIF;
        //LED1_Toggle();
        //printf("TIM3优先级=6,执行....\r\n");
    }
}
