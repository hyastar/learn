#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f10x.h"

#define KEY0_PRESSED   1
#define KEY1_PRESSED   2
#define KEY2_PRESSED   3
#define NO_KEY_PRESSED    0

void KEY_Init(void);
uint8_t key_scan(void);

#endif
