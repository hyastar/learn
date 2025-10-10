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

#define START_TASK_STACK         128
#define START_TASK_PRIORITY      1
static void start_task(void *pvParameters);


#define LED_TASK_STACK           64
#define LED_TASK_PRIORITY        2
static void led_task(void *pvParameters);


#define OLED_TASK_STACK          128
#define OLED_TASK_PRIORITY       2
static void oled_task(void *pvParameters);


#define BLE_TASK_STACK           256
#define BLE_TASK_PRIORITY        3
static void ble_task(void *pvParameters);





char g_oled_ble_line[32] = "BLE: Waiting...";



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

#define LINE_CHARS 16 
static void oled_task(void *pvParameters)
{
    uint32_t counter = 0;
    char buffer[32];

    OLED_Clear(0x00);

    for (;;)
    {
        sprintf(buffer, "Count: %u", counter++);
        OLED_ShowString(0, 0, (uint8_t*)buffer);

        OLED_ShowString(2, 0, (uint8_t*)"BLE Recv:");

        char local_ble[33];
        
        strncpy(local_ble, g_oled_ble_line, sizeof(local_ble)-1);
        local_ble[sizeof(local_ble)-1] = '\0';
        

        char line1[LINE_CHARS + 1];
        char line2[LINE_CHARS + 1];

        memset(line1, 0, sizeof(line1));
        memset(line2, 0, sizeof(line2));

        strncpy(line1, local_ble, LINE_CHARS);
        if (strlen(local_ble) > LINE_CHARS) {
            strncpy(line2, local_ble + LINE_CHARS, LINE_CHARS);
        } else {
            line2[0] = '\0';
        }

        char disp1[LINE_CHARS + 1];
        char disp2[LINE_CHARS + 1];
        snprintf(disp1, sizeof(disp1), "%-*s", LINE_CHARS, line1);
        snprintf(disp2, sizeof(disp2), "%-*s", LINE_CHARS, line2);

        OLED_ShowString(4, 0, (uint8_t*)disp1);
        OLED_ShowString(6, 0, (uint8_t*)disp2);

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
