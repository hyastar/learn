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
#include "bsp_sht30.h" 
#include "bsp_bmp280.h" // 包含新的BMP280驱动头文件

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

#define SENSOR_TASK_STACK        128
#define SENSOR_TASK_PRIORITY     2
static void sensor_task(void *pvParameters);

#define BLE_TASK_STACK           256
#define BLE_TASK_PRIORITY        3
static void ble_task(void *pvParameters);


// --- 全局变量用于任务间数据共享 ---
char g_oled_ble_line[32] = "BLE: Waiting...";

// SHT30 传感器数据
volatile float g_temperature = -99.0f;
volatile float g_humidity = -99.0f;
volatile uint8_t g_sht30_status = 1; // 0: OK, 1: Error

// 新增 BMP280 传感器数据
volatile float g_pressure = -999.0f;
volatile float g_altitude = -999.0f;
volatile uint8_t g_bmp280_status = 1; // 0: OK, 1: Error


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
        printf("SHT30 sensor initialization FAILED!\r\n");
    }

    // 初始化BMP280传感器
    if(BMP280_Init(&g_oled_bus) == 0) {
        printf("BMP280 sensor initialized successfully.\r\n");
    } else {
        printf("BMP280 sensor initialization FAILED!\r\n");
    }
    
    General_Timer_Init();
    printf("General Timer (TIM2 for stats, TIM3.c for app) initialized.\r\n");
    
    taskENTER_CRITICAL();

    xTaskCreate(led_task, "led_task", LED_TASK_STACK, NULL, LED_TASK_PRIORITY, NULL);
    printf("Task 'led_task' created.\r\n");

    xTaskCreate(oled_task, "oled_task", OLED_TASK_STACK, NULL, OLED_TASK_PRIORITY, NULL);
    printf("Task 'oled_task' created.\r\n");

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

// 修改后的传感器任务，同时读取SHT30和BMP280
static void sensor_task(void *pvParameters)
{
    for(;;)
    {
        float temp, humi, pres, alti;
        
        // --- 读取 SHT30 ---
        if (SHT30_Read_Humiture(&g_oled_bus, &temp, &humi) == 0) {
            g_temperature = temp;
            g_humidity = humi;
            g_sht30_status = 0;
        } else {
            g_sht30_status = 1; 
            printf("SHT30 Read Error!\r\n");
        }

        // --- 读取 BMP280 ---
        // 注意：BMP280也输出温度，但我们这里只用它的气压和海拔，温度以更精确的SHT30为准
        if (BMP280_Get_Data(&g_oled_bus, &pres, &temp, &alti) == 0) {
            g_pressure = pres;
            g_altitude = alti;
            g_bmp280_status = 0;
        } else {
            g_bmp280_status = 1;
            printf("BMP280 Read Error!\r\n");
        }
        
        // 打印所有传感器数据
        if (g_sht30_status == 0 && g_bmp280_status == 0) {
             printf("T:%.1fC, H:%.1f%%, P:%.1fhPa, A:%.1fm\r\n", g_temperature, g_humidity, g_pressure, g_altitude);
        }

        // 每2.5秒读取一次
        vTaskDelay(pdMS_TO_TICKS(2500));
    }
}


#define LINE_CHARS 16 
// 修改后的OLED任务，显示所有传感器数据
static void oled_task(void *pvParameters)
{
    char buffer[32];
    OLED_Clear(0x00);

    for (;;)
    {
        // 第0行: 显示气压和海拔
        if (g_bmp280_status == 0) {
             snprintf(buffer, sizeof(buffer), "P:%.1f A:%.1fm", g_pressure, g_altitude);
        } else {
             snprintf(buffer, sizeof(buffer), "BMP280 Error!");
        }
        OLED_ShowString(0, 0, (uint8_t*)buffer);


        // 第2行: 显示温湿度
        if (g_sht30_status == 0) {
             snprintf(buffer, sizeof(buffer), "T:%.1fC H:%.1f%%", g_temperature, g_humidity);
        } else {
             snprintf(buffer, sizeof(buffer), "SHT30 Error!");
        }
        OLED_ShowString(2, 0, (uint8_t*)buffer);


        // 第4-7行: 显示BLE接收信息
        OLED_ShowString(4, 0, (uint8_t*)"BLE Recv:");
        char local_ble[33];
        taskENTER_CRITICAL();
        strncpy(local_ble, g_oled_ble_line, sizeof(local_ble)-1);
        taskEXIT_CRITICAL();
        local_ble[sizeof(local_ble)-1] = '\0';
        
        char line1[LINE_CHARS + 1] = {0};
        char line2[LINE_CHARS + 1] = {0};

        strncpy(line1, local_ble, LINE_CHARS);
        if (strlen(local_ble) > LINE_CHARS) {
            strncpy(line2, local_ble + LINE_CHARS, LINE_CHARS);
        }

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
