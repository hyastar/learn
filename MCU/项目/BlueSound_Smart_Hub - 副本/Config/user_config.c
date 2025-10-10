#include "user_config.h"

volatile unsigned long ulHighFrequencyTimerTicks;

I2C_Bus_t g_oled_bus = {
    GPIOG,      // SDA Port
    0x8000,     // SDA Pin (PG15 -> 1 << 15)
    GPIOG,      // SCL Port
    0x4000      // SCL Pin (PG14 -> 1 << 14)
};

void User_Config_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPGEN; 

    I2C_Init(&g_oled_bus);
}
