#include "stm32f10x.h"
#include "sys.h"             
#include "bsp_usart_it.h"   
#include "freertos_tasks.h"  


int main(void)
{
    SYS_Init();

    USART1_Init(115200);

    // 3. 打印启动信息
    printf("\r\n==================================\r\n");
    printf(" BSS_Hub - System Core Initialized.\r\n");
    printf(" Starting FreeRTOS Scheduler...\r\n");
    printf("==================================\r\n");


    freertos_start();

    while (1)
    {
    }
}
