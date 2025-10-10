#include "bsp_ble.h"
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_oled.h"
#include <stdio.h>
#include <string.h>

// 声明一个来自 freertos_tasks.c 的全局变量，用于在任务间传递数据
extern char g_oled_ble_line[32];

// ===================================================================================
// =================== 内部USART3驱动部分 (Internal USART3 Driver) ===================
// ===================================================================================

// --- 缓冲区大小定义 ---
#define TX_BUF_SIZE 256
#define RX_BUF_SIZE 256

// --- 静态(内部)变量 ---
static volatile uint8_t tx_buffer[TX_BUF_SIZE];
static volatile uint16_t tx_head = 0;
static volatile uint16_t tx_tail = 0;

static volatile uint8_t rx_buffer[RX_BUF_SIZE];
static volatile uint16_t rx_head = 0;
static volatile uint16_t rx_tail = 0;

// --- 静态(内部)函数声明 ---
static void usart3_init(uint32_t baudrate);
static uint16_t usart3_send_data(const uint8_t *data, uint16_t len);
static uint16_t usart3_get_rx_available(void);
static uint16_t usart3_read_bytes(uint8_t *buffer, uint16_t max_len);


/**
 * @brief  初始化USART3硬件
 */
static void usart3_init(uint32_t baudrate)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

    // PB10 (USART3_TX) -> AF Push-pull
    GPIOB->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
    GPIOB->CRH |=  (GPIO_CRH_MODE10_0 | GPIO_CRH_MODE10_1 | GPIO_CRH_CNF10_1);
    // PB11 (USART3_RX) -> Input Floating
    GPIOB->CRH &= ~(GPIO_CRH_MODE11 | GPIO_CRH_CNF11);
    GPIOB->CRH |=  (GPIO_CRH_CNF11_0);

    uint32_t apb1_clock = SystemCoreClock >> 1; // PCLK1 is 36MHz if SysClk is 72MHz
    USART3->BRR = apb1_clock / baudrate;
    USART3->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
    USART3->CR1 |= USART_CR1_UE;

    NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 0));
    NVIC_EnableIRQ(USART3_IRQn);
}

/**
 * @brief  通过USART3发送数据 (内部函数)
 */
static uint16_t usart3_send_data(const uint8_t *data, uint16_t len)
{
    if (!data || len == 0) return 0;

    uint16_t free_space = (tx_head + TX_BUF_SIZE - tx_tail - 1) % TX_BUF_SIZE;
    uint16_t len_to_send = (len > free_space) ? free_space : len;
    
    if (len_to_send == 0) return 0;
    
    __disable_irq();
    uint16_t current_tail = tx_tail;
    for (uint16_t i = 0; i < len_to_send; i++) {
        tx_buffer[current_tail] = data[i];
        current_tail = (current_tail + 1) % TX_BUF_SIZE;
    }
    tx_tail = current_tail;
    __enable_irq();

    if (!(USART3->CR1 & USART_CR1_TXEIE)) {
        USART3->CR1 |= USART_CR1_TXEIE;
    }
    return len_to_send;
}

/**
 * @brief  获取USART3接收缓冲区中可用字节数 (内部函数)
 */
static uint16_t usart3_get_rx_available(void)
{
    return (rx_head + RX_BUF_SIZE - rx_tail) % RX_BUF_SIZE;
}

/**
 * @brief  从USART3接收缓冲区读取数据 (内部函数)
 */
static uint16_t usart3_read_bytes(uint8_t *buffer, uint16_t max_len)
{
    uint16_t available = usart3_get_rx_available();
    uint16_t len_to_read = (max_len > available) ? available : max_len;

    if (len_to_read == 0) return 0;
    
    __disable_irq();
    uint16_t current_tail = rx_tail;
    for (uint16_t i = 0; i < len_to_read; i++) {
        buffer[i] = rx_buffer[current_tail];
        current_tail = (current_tail + 1) % RX_BUF_SIZE;
    }
    rx_tail = current_tail;
    __enable_irq();

    return len_to_read;
}

/**
 * @brief  USART3中断服务函数 (必须为全局)
 */
void USART3_IRQHandler(void)
{
    if(USART3->SR & USART_SR_RXNE) {
        uint8_t data = (uint8_t)USART3->DR;
        uint16_t next_head = (rx_head + 1) % RX_BUF_SIZE;
        if (next_head != rx_tail) {
            rx_buffer[rx_head] = data;
            rx_head = next_head; 
        }
    }
    
    if ((USART3->SR & USART_SR_TXE) && (USART3->CR1 & USART_CR1_TXEIE)) {
        if (tx_head != tx_tail) {
            USART3->DR = tx_buffer[tx_head];
            tx_head = (tx_head + 1) % TX_BUF_SIZE;
        } else {
            USART3->CR1 &= ~USART_CR1_TXEIE;
        }
    }
}

// ===================================================================================
// ======================= 公共蓝牙API部分 (Public BLE API) ========================
// ===================================================================================

void BLE_Init(void)
{
    printf("Initializing BLE module (with internal USART3)...\r\n");
    usart3_init(115200);
    
    vTaskDelay(pdMS_TO_TICKS(500)); 

    printf("Configuring BLE module as slave...\r\n");
    usart3_send_data((uint8_t*)"+++atk", strlen("+++atk"));
    vTaskDelay(pdMS_TO_TICKS(100));
    
    usart3_send_data((uint8_t*)"AT+MODE=0\r\n", strlen("AT+MODE=0\r\n"));
    vTaskDelay(pdMS_TO_TICKS(1000));
    
    usart3_send_data((uint8_t*)"+++atk", strlen("+++atk"));
    vTaskDelay(pdMS_TO_TICKS(100));
    usart3_send_data((uint8_t*)"AT+NAME=BSS_Hub_BLE\r\n", strlen("AT+NAME=BSS_Hub_BLE\r\n"));
    vTaskDelay(pdMS_TO_TICKS(500));
    
    usart3_send_data((uint8_t*)"AT+ENTM\r\n", strlen("AT+ENTM\r\n"));
    vTaskDelay(pdMS_TO_TICKS(100));

    printf("BLE module configuration complete.\r\n");
}

void BLE_Send_String(const char* str)
{
    if (!str) return;
    usart3_send_data((const uint8_t*)str, strlen(str));
}

void BLE_Process_RX_Data(void)
{
    if (usart3_get_rx_available() > 0)
    {
        static char ble_rx_temp_buffer[128];
        uint16_t len = usart3_read_bytes((uint8_t*)ble_rx_temp_buffer, sizeof(ble_rx_temp_buffer) - 1);

        if (len > 0)
        {
            if (len > sizeof(ble_rx_temp_buffer) - 1) len = sizeof(ble_rx_temp_buffer) - 1;
            ble_rx_temp_buffer[len] = '\0';

            printf("[BLE RX]: %s\r\n", ble_rx_temp_buffer);

            taskENTER_CRITICAL();
            // 方法：用 snprintf 完全覆盖并保证以 '\0' 结尾
            snprintf(g_oled_ble_line, sizeof(g_oled_ble_line), "%s", ble_rx_temp_buffer);
            taskEXIT_CRITICAL();
        }
    }
}

