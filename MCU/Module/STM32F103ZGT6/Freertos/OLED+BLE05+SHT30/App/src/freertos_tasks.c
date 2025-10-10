#include "freertos_tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

#include "user_config.h"
#include "bsp_led.h"
#include "bsp_oled.h"
#include "bsp_timer.h" 
#include "bsp_ble.h"
#include "bsp_sht30.h" // 包含新的SHT30驱动头文件

// Task Defines
#define START_TASK_STACK         128
#define START_TASK_PRIORITY      1
static void start_task(void *pvParameters);

#define LED_TASK_STACK           64
#define LED_TASK_PRIORITY        2
static void led_task(void *pvParameters);

#define OLED_TASK_STACK          128
#define OLED_TASK_PRIORITY       2
static void oled_task(void *pvParameters);

// 新增 Sensor Task 定义
#define SENSOR_TASK_STACK        128
#define SENSOR_TASK_PRIORITY     2
static void sensor_task(void *pvParameters);

#define BLE_TASK_STACK           256
#define BLE_TASK_PRIORITY        3
static void ble_task(void *pvParameters);


// --- 全局变量用于任务间数据共享 ---
// 用于OLED显示BLE信息
char g_oled_ble_line[32] = "BLE: Waiting...";

// 新增全局变量用于存储传感器数据
volatile float g_temperature = -99.0f;
volatile float g_humidity = -99.0f;
volatile uint8_t g_sensor_status = 1; // 0: OK, 1: Error

static void start_task(void *pvParameters)
{
    printf("Start Task: Initializing hardware and creating tasks...\r\n");

    User_Config_Init(); 
    LED_Init();        
    OLED_Config();      
    
    // 初始化SHT30传感器
    if(SHT30_Init(&g_oled_bus) == 0) {
        printf("SHT30 sensor initialized successfully.\r\n");
    } else {
        printf("SHT30 sensor initialization failed!\r\n");
    }
    
    General_Timer_Init();
    printf("General Timer (TIM2 for stats, TIM3.c for app) initialized.\r\n");
    
    taskENTER_CRITICAL();

    xTaskCreate(led_task, "led_task", LED_TASK_STACK, NULL, LED_TASK_PRIORITY, NULL);
    printf("Task 'led_task' created.\r\n");

    xTaskCreate(oled_task, "oled_task", OLED_TASK_STACK, NULL, OLED_TASK_PRIORITY, NULL);
    printf("Task 'oled_task' created.\r\n");

    // 创建新的传感器任务
    xTaskCreate(sensor_task, "sensor_task", SENSOR_TASK_STACK, NULL, SENSOR_TASK_PRIORITY, NULL);
    printf("Task 'sensor_task' created.\r\n");

    xTaskCreate(ble_task, "ble_task", BLE_TASK_STACK, NULL, BLE_TASK_PRIORITY, NULL);
    printf("Task 'ble_task' created.\r\n");

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

// 新增的传感器任务
static void sensor_task(void *pvParameters)
{
    for(;;)
    {
        float temp, humi;
        // 调用新的SHT30读取函数，并更新全局变量
        if (SHT30_Read_Humiture(&g_oled_bus, &temp, &humi) == 0) {
            g_temperature = temp;
            g_humidity = humi;
            g_sensor_status = 0;
        } else {
            g_sensor_status = 1; // 如果读取失败，设置错误状态
        }

        // 每2秒读取一次
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}


#define LINE_CHARS 16 
// 修改后的OLED任务，用于显示所有信息
static void oled_task(void *pvParameters)
{
    uint32_t counter = 0;
    char buffer[32];

    OLED_Clear(0x00);

    for (;;)
    {
		OLED_Clear(0x00);
        // 第0行: 显示计数器
        sprintf(buffer, "Count: %-9u", counter++);
        OLED_ShowString(0, 0, (uint8_t*)buffer);

		// 第2行: 显示温湿度
        if (g_sensor_status == 0) {
            // 这行代码是为OLED准备的
            sprintf(buffer, "T:%.1fC H:%.1f%%", g_temperature, g_humidity);
            
            // 下面这行就是新增的打印功能
            // 我们在末尾加上 \r\n 来实现换行，这样在串口助手中看起来更整洁
            printf("Temperature: %.1f C, Humidity: %.1f %%\r\n", g_temperature, g_humidity);

        } else {
            // 这行代码是为OLED准备的
            sprintf(buffer, "Sensor Error!");
            
            // 同样，在出错时也打印信息
            printf("Sensor Error!\r\n");
        }
        // 这行代码将buffer中的内容显示到OLED上
        OLED_ShowString(2, 0, (uint8_t*)buffer);


        // 第4-6行: 显示BLE接收信息
        OLED_ShowString(4, 0, (uint8_t*)"BLE Recv:");

        char local_ble[33];
        taskENTER_CRITICAL(); // 简单保护全局变量
        strncpy(local_ble, g_oled_ble_line, sizeof(local_ble)-1);
        taskEXIT_CRITICAL();
        local_ble[sizeof(local_ble)-1] = '\0';
        
        char line1[LINE_CHARS + 1];
        char line2[LINE_CHARS + 1];

        memset(line1, 0, sizeof(line1));
        memset(line2, 0, sizeof(line2));

        strncpy(line1, local_ble, LINE_CHARS);
        if (strlen(local_ble) > LINE_CHARS) {
            strncpy(line2, local_ble + LINE_CHARS, LINE_CHARS);
        }

        // 使用snprintf填充空格，避免旧字符残留
        char disp_line[LINE_CHARS + 1];
        snprintf(disp_line, sizeof(disp_line), "%-*s", LINE_CHARS, line1);
        OLED_ShowString(6, 0, (uint8_t*)disp_line);
        
        snprintf(disp_line, sizeof(disp_line), "%-*s", LINE_CHARS, line2);
        OLED_ShowString(7, 0, (uint8_t*)disp_line);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void ble_task(void *pvParameters)
{
    BLE_Init();
    for (;;)
    {
        BLE_Process_RX_Data();
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void freertos_start(void)
{
    xTaskCreate(start_task, "start_task", START_TASK_STACK, NULL, START_TASK_PRIORITY, NULL);
    vTaskStartScheduler();
}

void PRE_SLEEP_PROCESSING(void) {}
void POST_SLEEP_PROCESSING(void) {}
