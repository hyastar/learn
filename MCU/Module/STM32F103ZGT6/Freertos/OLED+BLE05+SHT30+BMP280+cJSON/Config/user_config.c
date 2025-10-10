#include "user_config.h"
#include "stm32f10x.h"

volatile unsigned long ulHighFrequencyTimerTicks;

// g_oled_bus �ļĴ����汾����
I2C_Bus_t g_oled_bus = {
    GPIOB,      // SDA Port
    0x0080,     // SDA Pin (PB7 -> ��Ӧ��7λ���� 1 << 7)
    GPIOB,      // SCL Port
    0x0040      // SCL Pin (PB6 -> ��Ӧ��6λ���� 1 << 6)
};

void User_Config_Init(void)
{
    // ��һ�б��ֲ��䣬ʹ�� GPIOB ��ʱ��
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; 

    I2C_Init(&g_oled_bus);
}
