#include "freertos_tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

// --- 包含所有需要用到的外设驱动头文件 ---
#include "user_config.h"
#include "bsp_led.h"
#include "bsp_oled.h"
#include "bsp_timer.h" // <--- 添加您的定时器头文件

//============ 任务定义 ============//
// --- 起始任务 ---
#define START_TASK_STACK         128
#define START_TASK_PRIORITY      1
static void start_task(void *pvParameters);

// --- LED心跳任务 ---
#define LED_TASK_STACK           64
#define LED_TASK_PRIORITY        2
static void led_task(void *pvParameters);

// --- OLED显示任务 ---
#define OLED_TASK_STACK          128
#define OLED_TASK_PRIORITY       2
static void oled_task(void *pvParameters);

// --- 串口打印任务 ---
#define PRINTF_TASK_STACK        256
#define PRINTF_TASK_PRIORITY     3
static void printf_task(void *pvParameters);


//============ 任务实现 ============//

// --- 起始任务实现 ---
static void start_task(void *pvParameters)
{
    printf("Start Task: Initializing hardware and creating tasks...\r\n");

    // --- 初始化所有应用相关的硬件 ---
    User_Config_Init(); // 初始化OLED的I2C引脚
    LED_Init();         // 初始化LED
    OLED_Config();      // 初始化OLED屏幕
    
    // 调用您自己的通用定时器初始化函数
    // 它会同时初始化TIM2(用于FreeRTOS统计)和TIM3
    General_Timer_Init();
    printf("General Timer (TIM2 for stats, TIM3.c for app) initialized.\r\n");
    
    // --- 创建其他任务 ---
    taskENTER_CRITICAL();

    xTaskCreate(led_task, "led_task", LED_TASK_STACK, NULL, LED_TASK_PRIORITY, NULL);
    printf("Task 'led_task' created.\r\n");

    xTaskCreate(oled_task, "oled_task", OLED_TASK_STACK, NULL, OLED_TASK_PRIORITY, NULL);
    printf("Task 'oled_task' created.\r\n");

    xTaskCreate(printf_task, "printf_task", PRINTF_TASK_STACK, NULL, PRINTF_TASK_PRIORITY, NULL);
    printf("Task 'printf_task' created.\r\n");

    taskEXIT_CRITICAL();

    printf("Start Task: Deleting self.\r\n\r\n");
    vTaskDelete(NULL);
}

// --- LED心跳任务实现 ---
static void led_task(void *pvParameters)
{
    for (;;)
    {
        LED0_Toggle(); // 假设你有一个LED0_Toggle函数
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// --- OLED显示任务实现 ---
static void oled_task(void *pvParameters)
{
    uint32_t counter = 0;
    char buffer[32];

    for (;;)
    {
        sprintf(buffer, "Counter: %lu", counter++);
        
        OLED_ShowString(0, 0, (uint8_t*)"FreeRTOS Running");
        OLED_ShowString(2, 0, (uint8_t*)buffer);
        OLED_ShowString(4, 0, (uint8_t*)"SCL: PG14");
        OLED_ShowString(6, 0, (uint8_t*)"SDA: PG15");

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// --- 串口打印任务实现 ---
static void printf_task(void *pvParameters)
{
    char stats_buffer[512];

    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));

        printf("---------------------------------------------------\r\n");
        printf("Task Name\tStatus\tPrio\tStack\tTask#\tCPU Usage\r\n");
        
        vTaskList(stats_buffer);
        printf("%s\r\n", stats_buffer);
        
        printf("---------------------------------------------------\r\n");
    }
}


//============ 公共API函数实现 ============//

void freertos_start(void)
{
    xTaskCreate(start_task, "start_task", START_TASK_STACK, NULL, START_TASK_PRIORITY, NULL);
    vTaskStartScheduler();
}

// Tickless Idle 模式需要的回调函数 (保持空即可)
void PRE_SLEEP_PROCESSING(void) {}
void POST_SLEEP_PROCESSING(void) {}
