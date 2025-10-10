#ifndef __BSP_BLE_H__
#define __BSP_BLE_H__

/**
 * @brief  初始化蓝牙模块（包括其使用的USART3）
 * @param  None
 * @retval None
 */
void BLE_Init(void);

/**
 * @brief  处理蓝牙接收数据的任务函数
 * @param  None
 * @retval None
 * @note   应由一个独立的FreeRTOS任务循环调用
 */
void BLE_Process_RX_Data(void);

/**
 * @brief  通过蓝牙发送字符串
 * @param  str 要发送的字符串
 * @retval None
 */
void BLE_Send_String(const char* str);


#endif // __BSP_BLE_H__
