#include "sys.h"

/**
 * @brief  系统初始化函数，主要用于设置NVIC中断优先级分组
 * @note   这个函数非常重要，必须在main函数早期被调用
 * FreeRTOS 依赖于一个确定的优先级分组来管理中断
 */
void SYS_Init(void)
{
    /*
     * 设置优先级分组为 3: 4位用于抢占优先级, 0位用于子优先级。
     * 这是FreeRTOS官方推荐的配置。
     * 你的代码 (0x3 << 8) 设置的正是这个分组，是完全正确的。
     */
    SCB->AIRCR = (0x5FA << 16) | (0x3 << 8);
}


/**
 * @brief  SysTick_Handler 已被 FreeRTOS 接管
 * @note   在 FreeRTOSConfig.h 中，我们已经通过 #define xPortSysTickHandler SysTick_Handler
 * 将 FreeRTOS 内核的中断处理函数直接映射到了 SysTick_Handler。
 * 因此，我们不再需要在这个文件中手动实现它，否则会导致链接器报重复定义错误。
 */


/**
 * @brief  通用 NVIC 配置函数
 * @note   这是一个很好的辅助函数，可以保留用于配置其他外设中断。
 */
