#ifndef __BSP_OLED_H__
#define __BSP_OLED_H__

#include "stm32f10x.h"

// 包含我们自己的驱动和字库文件
#include "bsp_i2c.h"
#include "bsp_font.h"
#include "bsp_photo.h"

// 定义屏幕大小
#define OLED_WIGH 128
#define OLED_PAGE 8

#define OLED_CLOSE  0X00
#define OLED_OPEN   0XFF

typedef enum
{
    OLED_CMD=0,
    OLED_DATA
} OLED_MODE;

// 公共API函数
void OLED_Config(void);
void OLED_SetPos(uint16_t x, uint16_t y);
void OLED_Clear(uint8_t data);
void OLED_ShowASCII(uint8_t page,uint8_t line,uint8_t *buf);
void OLED_ShowChinese(uint8_t page,uint8_t line,uint8_t *buf);
void OLED_ShowPhoto(uint8_t page,uint8_t line,uint8_t High,uint8_t Wide,uint8_t *buf);
void OLED_ShowString(uint8_t page,uint8_t line,uint8_t *str);

#endif
