#ifndef __BSP_USART_IT_H
#define __BSP_USART_IT_H

#include "stm32f10x.h"
#include "user_config.h"


void USART1_Init(uint32_t baudrate);
uint16_t USART1_Send_Data(const uint8_t *data, uint16_t len);
void USART1_Send_String(const char *str);
uint16_t USART1_Read_Line(char *buffer, uint16_t buffer_size);
uint16_t USART_Read_Bytes(uint8_t *buffer, uint16_t max_len);
uint8_t USART1_IS_TX_Busy(void);
uint16_t USART1_Get_TX_Free_Space(void);
uint16_t USART1_Get_RX_Availabe(void);
void USART1_RX_Flush(void);

#endif
