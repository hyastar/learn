#include "stm32f10x.h"
#include "user_config.h"  // 包含用户硬件配置文件，会调用它来初始化I2C引脚
#include "bsp_oled.h"     // 包含OLED应用函数
#include "sys.h"          // 假设这是你的系统时钟初始化文件
#include "delay.h"        // 假设这是你的延时函数文件

/**
 * @brief  主函数
 * @param  无
 * @retval 无
 */
int main(void)
{
    // 1. 初始化系统时钟和基础配置 (例如：中断分组)
    SYS_Init();
    // 初始化延时函数
    delay_init(); 

    // 2. 初始化OLED相关的硬件
    //    这个函数会开启 GPIOG 的时钟，并初始化 PG14 和 PG15 为I2C模式
    User_Config_Init(); 
    
    // 3. 初始化OLED屏幕本身
    //    这个函数会通过I2C发送一系列指令来点亮和配置屏幕
    OLED_Config();      
    
    // 4. 清理屏幕 (0x00为全黑)
    OLED_Clear(0x00);   
    
    // 5. 在屏幕上显示一些有用的信息，用于验证
    //    参数: 页(0-7), 列(0-127), 字符串
    OLED_ShowString(0, 0, (uint8_t*)"Project: BSS_Hub");
    OLED_ShowString(2, 0, (uint8_t*)"SCL Pin: PG14");
    OLED_ShowString(4, 0, (uint8_t*)"SDA Pin: PG15");
    OLED_ShowString(6, 0, (uint8_t*)"OLED Init OK!");

    // 6. 进入主循环，程序停在这里
    while (1)
    {
        // 在这个最小化测试中，主循环可以什么都不做。
        // 你也可以在这里添加一些动态效果，比如闪烁一个LED或更新屏幕上的时间。
    }
}
