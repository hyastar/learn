#ifndef __BSP_DHT11_H
#define __BSP_DHT11_H 

#include "stm32f10x.h"
#include "sys.h"
/******************************************************************************************/
/* DHT11 引脚 定义 */

#define DHT11_DQ_GPIO_PORT                  GPIOG
#define DHT11_DQ_GPIO_PIN                   SYS_GPIO_PIN11
#define DHT11_DQ_GPIO_CLK_ENABLE()          do{ RCC->APB2ENR |= 1 << 8; }while(0)   /* PG口时钟使能 */

/******************************************************************************************/

/* * IO操作宏定义 - 直接操作寄存器
 * 使用BSRR和BRR寄存器进行原子操作，确保不受中断干扰
 */
#define DHT11_DQ_OUT(x)         do{ x ? (DHT11_DQ_GPIO_PORT->BSRR = DHT11_DQ_GPIO_PIN) : (DHT11_DQ_GPIO_PORT->BRR = DHT11_DQ_GPIO_PIN); }while(0)
#define DHT11_DQ_IN             (DHT11_DQ_GPIO_PORT->IDR & DHT11_DQ_GPIO_PIN)     /* 读取输入数据寄存器 IDR */


uint8_t dht11_init(void);   /* 初始化DHT11 */
uint8_t dht11_read_data(uint8_t *temp,uint8_t *humi);   /* 读取温湿度 */

#endif