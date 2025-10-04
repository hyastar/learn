#include "freertos_tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

// --- ����������Ҫ�õ�����������ͷ�ļ� ---
#include "user_config.h"
#include "bsp_led.h"
#include "bsp_oled.h"
#include "bsp_timer.h" // <--- ������Ķ�ʱ��ͷ�ļ�

//============ ������ ============//
// --- ��ʼ���� ---
#define START_TASK_STACK         128
#define START_TASK_PRIORITY      1
static void start_task(void *pvParameters);

// --- LED�������� ---
#define LED_TASK_STACK           64
#define LED_TASK_PRIORITY        2
static void led_task(void *pvParameters);

// --- OLED��ʾ���� ---
#define OLED_TASK_STACK          128
#define OLED_TASK_PRIORITY       2
static void oled_task(void *pvParameters);

// --- ���ڴ�ӡ���� ---
#define PRINTF_TASK_STACK        256
#define PRINTF_TASK_PRIORITY     3
static void printf_task(void *pvParameters);


//============ ����ʵ�� ============//

// --- ��ʼ����ʵ�� ---
static void start_task(void *pvParameters)
{
    printf("Start Task: Initializing hardware and creating tasks...\r\n");

    // --- ��ʼ������Ӧ����ص�Ӳ�� ---
    User_Config_Init(); // ��ʼ��OLED��I2C����
    LED_Init();         // ��ʼ��LED
    OLED_Config();      // ��ʼ��OLED��Ļ
    
    // �������Լ���ͨ�ö�ʱ����ʼ������
    // ����ͬʱ��ʼ��TIM2(����FreeRTOSͳ��)��TIM3
    General_Timer_Init();
    printf("General Timer (TIM2 for stats, TIM3.c for app) initialized.\r\n");
    
    // --- ������������ ---
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

// --- LED��������ʵ�� ---
static void led_task(void *pvParameters)
{
    for (;;)
    {
        LED0_Toggle(); // ��������һ��LED0_Toggle����
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// --- OLED��ʾ����ʵ�� ---
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

// --- ���ڴ�ӡ����ʵ�� ---
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


//============ ����API����ʵ�� ============//

void freertos_start(void)
{
    xTaskCreate(start_task, "start_task", START_TASK_STACK, NULL, START_TASK_PRIORITY, NULL);
    vTaskStartScheduler();
}

// Tickless Idle ģʽ��Ҫ�Ļص����� (���ֿռ���)
void PRE_SLEEP_PROCESSING(void) {}
void POST_SLEEP_PROCESSING(void) {}
