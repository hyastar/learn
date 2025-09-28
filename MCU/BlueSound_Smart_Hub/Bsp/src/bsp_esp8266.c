#include "bsp_esp8266.h"
#include <stdio.h>
#include <string.h>

// --- FreeRTOS includes ---
#include "FreeRTOS.h"
#include "task.h"

/*==================================================================================================
 * --- 私有宏和变量 ---
 *================================================================================================*/

#define ESP8266_USART           USART3
#define ESP8266_USART_CLK       RCC_APB1ENR_USART3EN
#define ESP8266_USART_BAUDRATE  115200
#define ESP8266_USART_IRQn      USART3_IRQn
#define ESP8266_USART_PRIORITY  6 // 必须 >= configMAX_SYSCALL_INTERRUPT_PRIORITY (5)

#define RX_BUFFER_SIZE          256 // 接收缓冲区大小

// --- 串口接收缓冲区 ---
static volatile uint8_t esp_rx_buffer[RX_BUFFER_SIZE];
static volatile uint16_t esp_rx_count = 0;
static volatile bool esp_rx_flag = false; // 一帧数据接收完成标志

// --- MQTT报文组装缓冲区 ---
// 此缓冲区较大，定义为静态变量以避免栈溢出
static uint8_t MQTT_Packet_Buffer[1024];

/*==================================================================================================
 * --- 私有函数声明 ---
 *================================================================================================*/

static void esp_usart3_init(void);
static void esp_usart3_send(const uint8_t *data, uint16_t len);
static void esp_rx_buffer_clear(void);
static bool cmdAT(const char *cmd, const char *ack1, const char *ack2, uint32_t timeout_ms);
static int Mqtt_Connect_Packet(char *ClientID, char *Username, char *Password);
static int Mqtt_Publish_Packet(const char *topic, const char *message);


/*==================================================================================================
 * --- 公共函数定义 ---
 *================================================================================================*/

bool ESP8266_Init(void)
{
    // 1. 初始化控制引脚 (RST, EN)
    RCC->APB2ENR |= ESP8266_GPIO_CLK;
    
    // 配置 PA4 (RST) 和 PA5 (EN) 为推挽输出
    ESP8266_GPIO_PORT->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4 | GPIO_CRL_MODE5 | GPIO_CRL_CNF5);
    ESP8266_GPIO_PORT->CRL |= (GPIO_CRL_MODE4_0 | GPIO_CRL_MODE4_1); // 50MHz
    ESP8266_GPIO_PORT->CRL |= (GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1); // 50MHz

    // 2. 初始化与ESP8266通信的USART3
    esp_usart3_init();

    // 3. 复位并使能模块
    printf("Resetting ESP8266...\r\n");
    ESP8266_RESET_HIGH();
    ESP8266_ENABLE();
    vTaskDelay(pdMS_TO_TICKS(500));
    ESP8266_RESET_LOW();
    vTaskDelay(pdMS_TO_TICKS(500));
    ESP8266_RESET_HIGH();
    vTaskDelay(pdMS_TO_TICKS(1000));

    // 4. 测试AT指令
    return cmdAT("AT", "OK", NULL, 500);
}

bool ESP8266_Connect_Server(void)
{
    printf("Connecting to AP and Server...\r\n");

    if (!cmdAT("ATE0", "OK", NULL, 500)) return false; // 关闭回显
    if (!cmdAT("AT+CWMODE=1", "OK", NULL, 1000)) return false; // 设置为STA模式
    
    char cmd_buf[128];
    sprintf(cmd_buf, "AT+CWJAP=\"%s\",\"%s\"", WIFI_SSID, WIFI_PASSWORD);
    if (!cmdAT(cmd_buf, "WIFI GOT IP", "OK", 15000)) return false; // 连接WiFi
    
    if (!cmdAT("AT+CIPMUX=0", "OK", NULL, 1000)) return false; // 设置单连接模式

    sprintf(cmd_buf, "AT+CIPSTART=\"TCP\",\"%s\",%d", MQTT_HOST, MQTT_PORT);
    if (!cmdAT(cmd_buf, "CONNECT", "ALREADY", 5000)) return false; // 连接TCP服务器
    
    printf("TCP Connected. Sending MQTT Connect packet...\r\n");
    
    // 组装并发送MQTT连接报文
    int packet_len = Mqtt_Connect_Packet(MQTT_CLIENT_ID, MQTT_USER_NAME, MQTT_PASSWORD);
    sprintf(cmd_buf, "AT+CIPSEND=%d", packet_len);

    if (cmdAT(cmd_buf, ">", NULL, 1000)) {
        // CIPSEND准备好后，直接发送MQTT报文
        if (cmdAT((char*)MQTT_Packet_Buffer, "SEND OK", "+IPD,4", 5000)) {
            printf("MQTT Server Connected Successfully.\r\n");
            return true;
        }
    }
    
    printf("MQTT Connection Failed.\r\n");
    return false;
}

bool ESP8266_Publish(const char *topic, const char *message)
{
    char cmd_buf[32];
    int packet_len = Mqtt_Publish_Packet(topic, message);
    
    sprintf(cmd_buf, "AT+CIPSEND=%d", packet_len);

    if (cmdAT(cmd_buf, ">", NULL, 1000)) {
        // CIPSEND准备好后，直接发送MQTT发布报文
        if (cmdAT((char*)MQTT_Packet_Buffer, "SEND OK", NULL, 5000)) {
            return true;
        }
    }
    return false;
}

/*==================================================================================================
 * --- 私有函数定义 ---
 *================================================================================================*/

static void esp_usart3_init(void)
{
    // 1. 开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR |= ESP8266_USART_CLK;

    // 2. 配置GPIO (PB10 TX, PB11 RX)
    GPIOB->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10 | GPIO_CRH_MODE11 | GPIO_CRH_CNF11);
    GPIOB->CRH |= (GPIO_CRH_MODE10_0 | GPIO_CRH_MODE10_1 | GPIO_CRH_CNF10_1); // TX: 50MHz, AF Push-Pull
    GPIOB->CRH |= GPIO_CRH_CNF11_0; // RX: Floating input

    // 3. 配置USART3
    uint32_t apb1_clock = SystemCoreClock / 2;
    ESP8266_USART->BRR = apb1_clock / ESP8266_USART_BAUDRATE;
    ESP8266_USART->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_IDLEIE;
    
    // 4. 配置NVIC
    NVIC_SetPriority(ESP8266_USART_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), ESP8266_USART_PRIORITY, 0));
    NVIC_EnableIRQ(ESP8266_USART_IRQn);
    
    // 5. 使能USART3
    ESP8266_USART->CR1 |= USART_CR1_UE;
}

static void esp_usart3_send(const uint8_t *data, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++) {
        while (!(ESP8266_USART->SR & USART_SR_TXE));
        ESP8266_USART->DR = data[i];
    }
}

static void esp_rx_buffer_clear(void)
{
    memset((void*)esp_rx_buffer, 0, RX_BUFFER_SIZE);
    esp_rx_count = 0;
    esp_rx_flag = false;
}

static bool cmdAT(const char *cmd, const char *ack1, const char *ack2, uint32_t timeout_ms)
{
    esp_rx_buffer_clear();

    printf(">> ESP8266 CMD: %s\r\n", cmd);
    
    if (cmd != (char*)MQTT_Packet_Buffer) {
        esp_usart3_send((uint8_t*)cmd, strlen(cmd));
        esp_usart3_send((uint8_t*)"\r\n", 2);
    } else {
        // MQTT报文可能包含'\0'，必须用strlen计算出的长度
        esp_usart3_send((uint8_t*)cmd, strlen(cmd));
    }


    uint32_t start_ticks = xTaskGetTickCount();
    while (xTaskGetTickCount() - start_ticks < pdMS_TO_TICKS(timeout_ms)) {
        if (esp_rx_flag) {
            printf("<< ESP8266 RSP: %s\r\n", (char*)esp_rx_buffer);
            if (ack1 && strstr((const char*)esp_rx_buffer, ack1)) {
                return true;
            }
            if (ack2 && strstr((const char*)esp_rx_buffer, ack2)) {
                return true;
            }
            // 收到响应但不匹配，则认为失败
            return false;
        }
        vTaskDelay(pdMS_TO_TICKS(10)); // 释放CPU
    }

    printf("!! ESP8266 TIMEOUT\r\n");
    return false; // 超时
}


/*==================================================================================================
 * --- MQTT 报文组装函数 (移植自原wifi.c) ---
 *================================================================================================*/

static int Mqtt_Connect_Packet(char *ClientID, char *Username, char *Password)
{
    int ClientIDLen = (ClientID) ? strlen(ClientID) : 0;
    int UsernameLen = strlen(Username);
    int PasswordLen = strlen(Password);
    int DataLen = 0;
    int Index = 0;
    
    DataLen = 12 + ClientIDLen + 2 + UsernameLen + 2 + PasswordLen;
    // 固定报头
    MQTT_Packet_Buffer[Index++] = 0x10; // CONNECT
    MQTT_Packet_Buffer[Index++] = DataLen;
    // 可变报头
    MQTT_Packet_Buffer[Index++] = 0;
    MQTT_Packet_Buffer[Index++] = 4;
    MQTT_Packet_Buffer[Index++] = 'M';
    MQTT_Packet_Buffer[Index++] = 'Q';
    MQTT_Packet_Buffer[Index++] = 'T';
    MQTT_Packet_Buffer[Index++] = 'T';
    MQTT_Packet_Buffer[Index++] = 4;      // Protocol v4
    MQTT_Packet_Buffer[Index++] = 0xC2;   // Flags: Clean Session, User, Pass
    MQTT_Packet_Buffer[Index++] = 0x00;   // Keep-alive MSB
    MQTT_Packet_Buffer[Index++] = 0x3C;   // Keep-alive LSB (60s)
    // 有效载荷
    MQTT_Packet_Buffer[Index++] = (ClientIDLen >> 8) & 0xFF;
    MQTT_Packet_Buffer[Index++] = ClientIDLen & 0xFF;
    if (ClientIDLen > 0) {
        memcpy(&MQTT_Packet_Buffer[Index], ClientID, ClientIDLen);
        Index += ClientIDLen;
    }
    
    MQTT_Packet_Buffer[Index++] = (UsernameLen >> 8) & 0xFF;
    MQTT_Packet_Buffer[Index++] = UsernameLen & 0xFF;
    memcpy(&MQTT_Packet_Buffer[Index], Username, UsernameLen);
    Index += UsernameLen;

    MQTT_Packet_Buffer[Index++] = (PasswordLen >> 8) & 0xFF;
    MQTT_Packet_Buffer[Index++] = PasswordLen & 0xFF;
    memcpy(&MQTT_Packet_Buffer[Index], Password, PasswordLen);
    Index += PasswordLen;

    return Index;
}

static int Mqtt_Publish_Packet(const char *topic, const char *message)
{
    int topic_len = strlen(topic);
    int message_len = strlen(message);
    int remaining_len = 2 + topic_len + message_len;
    int index = 0;

    MQTT_Packet_Buffer[index++] = 0x30; // PUBLISH, QoS 0
    
    // 编码剩余长度 (只支持单字节)
    if (remaining_len > 127) {
        printf("Error: MQTT packet too long.\r\n");
        return 0;
    }
    MQTT_Packet_Buffer[index++] = remaining_len;
    
    MQTT_Packet_Buffer[index++] = (topic_len >> 8) & 0xFF;
    MQTT_Packet_Buffer[index++] = topic_len & 0xFF;
    memcpy(&MQTT_Packet_Buffer[index], topic, topic_len);
    index += topic_len;
    
    memcpy(&MQTT_Packet_Buffer[index], message, message_len);
    index += message_len;

    return index;
}

/*==================================================================================================
 * --- 中断服务函数 ---
 *================================================================================================*/

void USART3_IRQHandler(void)
{
    uint32_t sr = ESP8266_USART->SR;
    
    if (sr & USART_SR_RXNE) {
        uint8_t data = (uint8_t)(ESP8266_USART->DR & 0xFF);
        if (esp_rx_count < RX_BUFFER_SIZE -1) {
            esp_rx_buffer[esp_rx_count++] = data;
        }
    }

    if (sr & USART_SR_IDLE) {
       volatile uint32_t dummy_read;
       dummy_read = ESP8266_USART->SR;
       dummy_read = ESP8266_USART->DR;
       esp_rx_flag = true; // 收到空闲帧，认为一帧数据接收完毕
    }
}

