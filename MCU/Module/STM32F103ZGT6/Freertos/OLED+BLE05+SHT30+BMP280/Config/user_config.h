#ifndef __CONFIG_H
#define __CONFIG_H

#include "stm32f10x.h"
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "bsp_i2c.h"

#define DEBUG_MODE   1

extern volatile unsigned long ulHighFrequencyTimerTicks;


extern I2C_Bus_t g_oled_bus; 
void User_Config_Init(void);

#endif
