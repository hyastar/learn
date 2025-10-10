#include "user_config.h"
#include "stm32f10x.h"

volatile unsigned long ulHighFrequencyTimerTicks;

// g_oled_bus 的寄存器版本定义
I2C_Bus_t g_oled_bus = {
    GPIOB,      // SDA Port
    0x0080,     // SDA Pin (PB7 -> 对应第7位，即 1 << 7)
    GPIOB,      // SCL Port
    0x0040      // SCL Pin (PB6 -> 对应第6位，即 1 << 6)
};

void User_Config_Init(void)
{
    // 这一行保持不变，使能 GPIOB 的时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; 

    I2C_Init(&g_oled_bus);
}
