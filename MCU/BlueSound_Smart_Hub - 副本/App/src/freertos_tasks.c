#include "freertos_tasks.h"

#include "FreeRTOS.h"
#include "task.h"

// --- BSP/Driver Includes ---
#include "bsp_led.h"
#include "bsp_mq5.h"
#include "bsp_esp8266.h"

#include <stdio.h>
#include <string.h>


#define START_TASK_STACK         128
#define START_TASK_PRIORITY      1
static void start_task(void *pvParameters);


void freertos_start(void)
{
    xTaskCreate(start_task, "start_task", START_TASK_STACK, NULL, START_TASK_PRIORITY, NULL);
    vTaskStartScheduler();
}

static void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();

    taskEXIT_CRITICAL();
    vTaskDelete(NULL);
}

void PRE_SLEEP_PROCESSING(void)
{

}


void POST_SLEEP_PROCESSING(void)
{
    
}



