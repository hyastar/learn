#include "stm32f10x.h"
#include "sys.h"             // 用于设置NVIC中断分组
#include "bsp_usart_it.h"    // 串口驱动，用于printf
#include "freertos_tasks.h"  // FreeRTOS任务入口

/**
 * @brief  主函数 - FreeRTOS 启动入口
 * @note   main函数现在只负责最底层的初始化，然后启动FreeRTOS。
 * 所有应用层的初始化和任务都在 freertos_tasks.c 中管理。
 */
int main(void)
{
    // 1. 设置NVIC中断优先级分组，这是FreeRTOS正确运行的前提
    SYS_Init();

    // 2. 初始化串口1，波特率115200，用于printf打印信息
    USART1_Init(115200);

    // 3. 打印启动信息
    printf("\r\n==================================\r\n");
    printf(" BSS_Hub - System Core Initialized.\r\n");
    printf(" Starting FreeRTOS Scheduler...\r\n");
    printf("==================================\r\n");

    // 4. 启动FreeRTOS
    //    这个函数会创建起始任务并开启任务调度器。
    //    代码从这里开始由FreeRTOS接管，正常情况下永远不会返回。
    freertos_start();

    // -- 调度器启动后，以下代码将不会被执行 --
    while (1)
    {
    }
}
