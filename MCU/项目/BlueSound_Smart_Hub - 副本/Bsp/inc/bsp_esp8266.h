#ifndef __BSP_ESP8266_H
#define __BSP_ESP8266_H

#include "stm32f10x.h"
#include <stdbool.h> // 使用标准的bool类型

/*==================================================================================================
 * --- 宏定义 ---
 *================================================================================================*/

// --- WiFi 和 MQTT Broker 的凭据 ---
#define WIFI_SSID       "hyastar"
#define WIFI_PASSWORD   "A20040822"
#define MQTT_CLIENT_ID  NULL // ClientID可以为NULL，让服务器自动分配
#define MQTT_USER_NAME  "h64430qweb6wpz3z"
#define MQTT_PASSWORD   "MCaaDvAF50"
#define MQTT_HOST       "bj-2-mqtt.iot-api.com"
#define MQTT_PORT       1883

// --- ESP8266 硬引脚定义 ---
// PA4 -> ESP8266_RST
// PA5 -> ESP8266_EN (CH_PD)
#define ESP8266_GPIO_PORT       GPIOA
#define ESP8266_GPIO_CLK        RCC_APB2ENR_IOPAEN
// MODIFIED: Replaced HAL-style macros with register bitmasks
#define ESP8266_RST_PIN         (1U << 4) // Pin 4
#define ESP8266_EN_PIN          (1U << 5) // Pin 5

// --- ESP8266 硬件控制宏 ---
#define ESP8266_RESET_LOW()     (ESP8266_GPIO_PORT->BSRR = (uint32_t)ESP8266_RST_PIN << 16U)
#define ESP8266_RESET_HIGH()    (ESP8266_GPIO_PORT->BSRR = ESP8266_RST_PIN)
#define ESP8266_ENABLE()        (ESP8266_GPIO_PORT->BSRR = ESP8266_EN_PIN)
#define ESP8266_DISABLE()       (ESP8266_GPIO_PORT->BSRR = (uint32_t)ESP8266_EN_PIN << 16U)

/*==================================================================================================
 * --- 公共函数声明 (API) ---
 *================================================================================================*/

/**
 * @brief  初始化ESP8266模块 (GPIO, USART3, 并测试AT指令)
 * @param  None
 * @retval true: 初始化成功, false: 初始化失败
 */
bool ESP8266_Init(void);

/**
 * @brief  连接到WiFi热点和MQTT服务器
 * @note   此函数会阻塞，直到连接成功或超时失败。内部使用vTaskDelay。
 * @param  None
 * @retval true: 连接成功, false: 连接失败
 */
bool ESP8266_Connect_Server(void);

/**
 * @brief  向指定主题发布MQTT消息
 * @param  topic:   目标主题字符串
 * @param  message: 要发送的消息字符串
 * @retval true: 发布指令发送成功, false: 发布失败
 */
bool ESP8266_Publish(const char *topic, const char *message);

#endif /* __BSP_ESP8266_H */


