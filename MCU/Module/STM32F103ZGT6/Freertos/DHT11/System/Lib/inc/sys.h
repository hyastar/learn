#ifndef __SYS_H
#define __SYS_H

#include "stm32f10x.h"

/**
 * SYS_SUPPORT_OS用于定义系统文件夹是否支持OS
 * 0,不支持OS
 * 1,支持OS
 */
#define SYS_SUPPORT_OS          0


/* sys_nvic_ex_config专用宏定义 */
#define SYS_GPIO_FTIR           1       /* 下降沿触发 */
#define SYS_GPIO_RTIR           2       /* 上升沿触发 */
#define SYS_GPIO_BTIR           3       /* 任意边沿触发 */

/* GPIO设置专用宏定义 */
#define SYS_GPIO_MODE_IN        0       /* 普通输入模式 */
#define SYS_GPIO_MODE_OUT       1       /* 普通输出模式 */
#define SYS_GPIO_MODE_AF        2       /* AF功能模式 */
#define SYS_GPIO_MODE_AIN       3       /* 模拟输入模式 */

#define SYS_GPIO_SPEED_LOW      2       /* GPIO速度(低速,2M) */
#define SYS_GPIO_SPEED_MID      1       /* GPIO速度(中速,10M) */
#define SYS_GPIO_SPEED_HIGH     3       /* GPIO速度(高速,50M) */

#define SYS_GPIO_PUPD_NONE      0       /* 不带上下拉 */
#define SYS_GPIO_PUPD_PU        1       /* 上拉 */
#define SYS_GPIO_PUPD_PD        2       /* 下拉 */

#define SYS_GPIO_OTYPE_PP       0       /* 推挽输出 */
#define SYS_GPIO_OTYPE_OD       1       /* 开漏输出 */

/* GPIO引脚位置宏定义  */
#define SYS_GPIO_PIN_0           1<<0
#define SYS_GPIO_PIN_1           1<<1
#define SYS_GPIO_PIN_2           1<<2
#define SYS_GPIO_PIN_3           1<<3
#define SYS_GPIO_PIN_4           1<<4
#define SYS_GPIO_PIN_5           1<<5
#define SYS_GPIO_PIN_6           1<<6
#define SYS_GPIO_PIN_7           1<<7
#define SYS_GPIO_PIN_8           1<<8
#define SYS_GPIO_PIN_9           1<<9
#define SYS_GPIO_PIN_10          1<<10
#define SYS_GPIO_PIN_11          1<<11
#define SYS_GPIO_PIN_12          1<<12
#define SYS_GPIO_PIN_13          1<<13
#define SYS_GPIO_PIN_14          1<<14
#define SYS_GPIO_PIN_15          1<<15


void SYS_Init(void);
void SYS_GPIO_PIN_SET(GPIO_TypeDef *p_gpiox, uint16_t pinx, uint8_t status);    /* 设置GPIO某个引脚的输出状态 */
uint8_t SYS_GPIO_PIN_GET(GPIO_TypeDef *p_gpiox, uint16_t pinx);                 /* 读取GPIO某个引脚的状态 */

#endif
