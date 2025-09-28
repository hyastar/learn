#ifndef _BSP_FONT_H_
#define _BSP_FONT_H_

#include "stm32f10x.h"

extern uint8_t ASCIIFont_Lib[];
extern uint8_t ChineseFont_Lib[];

int ASCII_GetOffset(uint8_t data);
int Chinese_GetOffset(uint8_t data1,uint8_t data2);

#endif
