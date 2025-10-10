#include "stm32f10x.h"
#include "sys.h"           
#include "bsp_usart_it.h"  
#include "bsp_led.h"
#include "freertos_tasks.h" 


int main(void)
{
    SYS_Init();
	LED_Init();      
    USART1_Init(115200);


    printf("\r\n==================================\r\n");
    printf(" System Core Initialized.\r\n");
    printf(" Starting FreeRTOS Scheduler...\r\n");
    printf("==================================\r\n");
	LED0_On();
	LED1_On();
    freertos_start();

    while (1)
    {
    }
}
