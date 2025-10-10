#include "freertos_tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

#include "user_config.h"
#include "bsp_led.h"
#include "bsp_oled.h"
#include "bsp_timer.h" 
#include "bsp_ble.h" // <--- 包含蓝牙驱动头文件

#define START_TASK_STACK         128
#define START_TASK_PRIORITY      1
static void start_task(void *pvParameters);


#define LED_TASK_STACK           64
#define LED_TASK_PRIORITY        2
static void led_task(void *pvParameters);


#define OLED_TASK_STACK          128
#define OLED_TASK_PRIORITY       2
static void oled_task(void *pvParameters);

// --- 新增BLE任务定义 ---
#define BLE_TASK_STACK           256
#define BLE_TASK_PRIORITY        3
static void ble_task(void *pvParameters);
// --- 结束 ---



// --- 新增全局变量，用于从ble_task向oled_task传递数据 ---
char g_oled_ble_line[32] = "BLE: Waiting...";
// --- 结束 ---


static void start_task(void *pvParameters)
{
    printf("Start Task: Initializing hardware and creating tasks...\r\n");

    User_Config_Init(); 
    LED_Init();        
    OLED_Config();      
    
    General_Timer_Init();
    printf("General Timer (TIM2 for stats, TIM3.c for app) initialized.\r\n");
    
    taskENTER_CRITICAL();

    xTaskCreate(led_task, "led_task", LED_TASK_STACK, NULL, LED_TASK_PRIORITY, NULL);
    printf("Task 'led_task' created.\r\n");

    xTaskCreate(oled_task, "oled_task", OLED_TASK_STACK, NULL, OLED_TASK_PRIORITY, NULL);
    printf("Task 'oled_task' created.\r\n");

    // --- 新增: 创建BLE任务 ---
    xTaskCreate(ble_task, "ble_task", BLE_TASK_STACK, NULL, BLE_TASK_PRIORITY, NULL);
    printf("Task 'ble_task' created.\r\n");
    // --- 结束 ---



    taskEXIT_CRITICAL();

    printf("Start Task: Deleting self.\r\n\r\n");
    vTaskDelete(NULL);
}


static void led_task(void *pvParameters)
{
    for (;;)
    {
        LED0_Toggle(); 
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

#define LINE_CHARS 16   // 每行字符数（128px / 字体宽度）
static void oled_task(void *pvParameters)
{
    uint32_t counter = 0;
    char buffer[32];

    // 开机清一次屏（可选）
    OLED_Clear(0x00);

    for (;;)
    {
        // 1) 更新计数（第1行）
        sprintf(buffer, "Count: %lu", counter++);
        OLED_ShowString(0, 0, (uint8_t*)buffer);

        // 2) 固定标题（第2行）
        OLED_ShowString(2, 0, (uint8_t*)"BLE Recv:");

        // 3) 读取全局 BLE 缓冲到本地（保持并发安全）
        char local_ble[33]; // 支持最多32字节字符串
        strncpy(local_ble, g_oled_ble_line, sizeof(local_ble)-1);
        local_ble[sizeof(local_ble)-1] = '\0';

        // 4) 将 local_ble 拆成两行，每行 LINE_CHARS 个字符
        char line1[LINE_CHARS + 1];
        char line2[LINE_CHARS + 1];

        // 清零
        memset(line1, 0, sizeof(line1));
        memset(line2, 0, sizeof(line2));

        // 拷贝第一段
        strncpy(line1, local_ble, LINE_CHARS);
        // 拷贝第二段（如果有）
        if (strlen(local_ble) > LINE_CHARS) {
            strncpy(line2, local_ble + LINE_CHARS, LINE_CHARS);
        } else {
            line2[0] = '\0';
        }

        // 5) 用空格填满每行，保证覆盖老内容（%-*s：左对齐，空格补齐）
        char disp1[LINE_CHARS + 1];
        char disp2[LINE_CHARS + 1];
        snprintf(disp1, sizeof(disp1), "%-*s", LINE_CHARS, line1);
        snprintf(disp2, sizeof(disp2), "%-*s", LINE_CHARS, line2);

        // 6) 显示到 OLED（第3行 page=4，第4行 page=6）
        OLED_ShowString(4, 0, (uint8_t*)disp1);
        OLED_ShowString(6, 0, (uint8_t*)disp2);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}



// --- 结束修改 ---

// --- 新增 ble_task 任务函数实现 ---
static void ble_task(void *pvParameters)
{
    // 初始化蓝牙模块 (包括其内部的串口驱动和AT指令配置)
    BLE_Init();

    for (;;)
    {
        // 循环处理接收到的数据
        BLE_Process_RX_Data();
        
        // 挂起任务，让出CPU给其他任务
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
// --- 结束 ---


void freertos_start(void)
{
    xTaskCreate(start_task, "start_task", START_TASK_STACK, NULL, START_TASK_PRIORITY, NULL);
    vTaskStartScheduler();
}

void PRE_SLEEP_PROCESSING(void) {}
void POST_SLEEP_PROCESSING(void) {}
