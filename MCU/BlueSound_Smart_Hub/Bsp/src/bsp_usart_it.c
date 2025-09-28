#include "bsp_usart_it.h"
#include "stm32f10x.h"

// --- 缓冲区大小定义 ---
#define TX_BUFFER_SIZE 256
#define RX_BUFFER_SIZE 256

// --- 发送环形缓冲区 ---
static volatile uint8_t tx_buffer[TX_BUFFER_SIZE];
static volatile uint16_t tx_head = 0;
static volatile uint16_t tx_tail = 0;

// --- 接收环形缓冲区 ---
static volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
static volatile uint16_t rx_head = 0;
static volatile uint16_t rx_tail = 0;


void USART1_Init(uint32_t baudrate)
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;

    GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
    GPIOA->CRH |=  (GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1);
    GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
    GPIOA->CRH |=  (GPIO_CRH_CNF10_0);

    USART1->BRR = SystemCoreClock / baudrate;
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE; 
    USART1->CR1 |= USART_CR1_UE;

    NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 4, 0));
    NVIC_EnableIRQ(USART1_IRQn);
}

// ======================= 发送相关函数 =======================

uint16_t USART1_Get_TX_Free_Space(void)
{
    volatile uint16_t local_tx_head = tx_head;
    volatile uint16_t local_tx_tail = tx_tail;
    return (local_tx_head + TX_BUFFER_SIZE - local_tx_tail - 1) % TX_BUFFER_SIZE;
}

uint16_t USART1_Send_Data(const uint8_t *data, uint16_t len)
{
    if (!data || len == 0) return 0;

    uint16_t free_space = USART1_Get_TX_Free_Space();
    uint16_t len_to_send = (len > free_space) ? free_space : len;
    
    if (len_to_send == 0) {
        return 0;
    }

    uint16_t part1_len = TX_BUFFER_SIZE - tx_tail;
    if (part1_len > len_to_send) {
        memcpy((void*)&tx_buffer[tx_tail], data, len_to_send);
    } else {
        memcpy((void*)&tx_buffer[tx_tail], data, part1_len);
        memcpy((void*)&tx_buffer[0], data + part1_len, len_to_send - part1_len);
    }

    tx_tail = (tx_tail + len_to_send) % TX_BUFFER_SIZE;

    if (!(USART1->CR1 & USART_CR1_TXEIE)) {
        USART1->CR1 |= USART_CR1_TXEIE;
    }

    return len_to_send;
}

void USART1_Send_String(const char *str)
{
    if (!str) return;
    USART1_Send_Data((const uint8_t*)str, strlen(str));
}

uint8_t USART1_is_TX_Busy(void)
{
    return (tx_head != tx_tail);
}


// ======================= 接收相关函数 =======================

uint16_t USART1_Get_RX_Available(void)
{
    volatile uint16_t local_rx_head = rx_head;
    volatile uint16_t local_rx_tail = rx_tail;
    return (local_rx_head + RX_BUFFER_SIZE - local_rx_tail) % RX_BUFFER_SIZE;
}

void USART1_RX_Flush(void)
{
    rx_tail = rx_head;
}

uint16_t USART1_Read_Bytes(uint8_t *buffer, uint16_t max_len)
{
    if (!buffer || max_len == 0) return 0;
    
    uint16_t available = USART1_Get_RX_Available();
    uint16_t len_to_read = (max_len > available) ? available : max_len;

    if (len_to_read == 0) return 0;

    uint16_t part1_len = RX_BUFFER_SIZE - rx_tail;
    if (part1_len > len_to_read) {
        memcpy(buffer, (void*)&rx_buffer[rx_tail], len_to_read);
    } else {
        memcpy(buffer, (void*)&rx_buffer[rx_tail], part1_len);
        memcpy(buffer + part1_len, (void*)&rx_buffer[0], len_to_read - part1_len);
    }

    rx_tail = (rx_tail + len_to_read) % RX_BUFFER_SIZE;

    return len_to_read;
}

uint16_t USART1_Read_Line(char *buffer, uint16_t buffer_size)
{
    if (!buffer || buffer_size < 2) return 0;
    
    uint16_t i = 0;
    volatile uint16_t local_rx_head = rx_head;

    for (i = 0; i < buffer_size - 1; ++i) {
        uint16_t current_pos = (rx_tail + i) % RX_BUFFER_SIZE;
        
        if (current_pos == local_rx_head) return 0;

        char c = rx_buffer[current_pos];
        if (c == '\n' || c == '\r') {
            buffer[i] = '\0';
            rx_tail = (current_pos + 1) % RX_BUFFER_SIZE;
            return i;
        }
        buffer[i] = c;
    }
    return 0;
}


// ======================= 中断与Printf支持 =======================

void USART1_IRQHandler(void)
{
    uint32_t sr = USART1->SR;
    
    if(sr & (USART_SR_ORE | USART_SR_FE | USART_SR_PE)) {
        volatile uint8_t dummy_read = USART1->DR; 
        (void)dummy_read;
    }

    if (sr & USART_SR_RXNE) {
        uint8_t data = (uint8_t)USART1->DR;
        uint16_t next_head = (rx_head + 1) % RX_BUFFER_SIZE;
        if (next_head != rx_tail) {
            rx_buffer[rx_head] = data;
            rx_head = next_head; 
        }
    }
    
    if ((sr & USART_SR_TXE) && (USART1->CR1 & USART_CR1_TXEIE)) {
        if (tx_head != tx_tail) {
            USART1->DR = tx_buffer[tx_head];
            tx_head = (tx_head + 1) % TX_BUFFER_SIZE;
        } else {
            USART1->CR1 &= ~USART_CR1_TXEIE;
        }
    }
}

int fputc(int ch, FILE *f)
{
    uint8_t byte = (uint8_t)ch;
    
    if (USART1_Send_Data(&byte, 1) == 0) {

        for (volatile int i = 0; i < 1000; i++) {
            if (USART1_Send_Data(&byte, 1) > 0) {
                break;
            }
        }
    }
    
    return ch;
}
