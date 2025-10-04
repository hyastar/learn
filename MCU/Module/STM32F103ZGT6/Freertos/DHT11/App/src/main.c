#include "stm32f10x.h"
#include "sys.h" 
#include "delay.h"
#include "user_config.h"       
#include "bsp_usart_it.h"  
#include "bsp_led.h"
#include "bsp_dht11.h"
#include "freertos_tasks.h" 


int main(void)
{
    SYS_Init();
    LED_Init();      
    USART1_Init(115200);
    delay_init(); // 初始化延时定时器 TIM6

    printf("\r\n==================================\r\n");
    printf(" System Core Initialized.\r\n");
    
    // -------- 添加诊断代码开始 --------
    printf(" Testing delay_ms function...\r\n");
    for (int i = 0; i < 5; i++)
    {
        LED0_On();
        delay_ms(200); // 延时200ms
        LED0_Off();
        delay_ms(200); // 延时200ms
    }
    printf(" Delay test finished.\r\n");
    // -------- 添加诊断代码结束 --------
    
    printf(" Starting DHT11 Init...\r\n");
    printf("==================================\r\n");
    
    while (dht11_init() != 0)
    {
        printf("DHT11 Init Error, Retrying...\r\n");
        delay_ms(500);
    }
    printf("DHT11 Init OK!\r\n");
    //freertos_start();
}