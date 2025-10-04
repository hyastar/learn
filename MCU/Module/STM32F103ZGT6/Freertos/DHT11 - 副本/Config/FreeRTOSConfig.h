#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*==================================================================================================
 * --- 1. 基础配置 & 调度器 (核心模块，通常不修改) ---
 *================================================================================================*/
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif

#define configUSE_PREEMPTION                    1       // 1: 启用抢占式调度器
#define configUSE_TIME_SLICING                  1       // 1: 启用时间片调度 (同优先级任务轮流执行)
#define configCPU_CLOCK_HZ                      ( SystemCoreClock ) // CPU主频
#define configTICK_RATE_HZ                      ( ( TickType_t ) 1000 ) // 系统时钟节拍频率 (1000Hz = 1ms/tick)
#define configMAX_PRIORITIES                    ( 5 )   // 最大可用任务优先级数量 (例如 5 表示 0-4)
#define configMAX_TASK_NAME_LEN                 ( 16 )  // 任务名的最大长度
#define configUSE_16_BIT_TICKS                  0       // 0: 使用32位Tick计数器 (适用于长时间运行系统)

/*==================================================================================================
 * --- 2. 内存管理配置 (选择一种内存方案) ---
 *================================================================================================*/
// FreeRTOS 提供5种内存管理方案 (heap_1 ~ heap_5), 必须在项目中添加其中一个.c文件
// heap_4.c 是最常用和推荐的方案，因为它支持内存释放和碎片合并
#define configSUPPORT_DYNAMIC_ALLOCATION        1       // 1: 支持动态内存申请 (pvPortMalloc)
#define configSUPPORT_STATIC_ALLOCATION         0       // 1: 支持静态内存申请 (xTaskCreateStatic等)
#define configTOTAL_HEAP_SIZE                   ( ( size_t ) ( 17 * 1024 ) ) // FreeRTOS可用堆总大小 (17KB)
#define configMINIMAL_STACK_SIZE                ( ( unsigned short ) 128 ) // 空闲任务的栈大小 (单位: Word, 4字节)

/*==================================================================================================
 * --- 3. 内核对象功能模块 (按需开启) ---
 *================================================================================================*/
#define configUSE_MUTEXES                       1       // 1: 使能互斥信号量
#define configUSE_RECURSIVE_MUTEXES             1       // 1: 使能递归互斥信号量
#define configUSE_COUNTING_SEMAPHORES           1       // 1: 使能计数型信号量
#define configUSE_QUEUE_SETS                    1       // 1: 使能队列集
#define configUSE_TASK_NOTIFICATIONS            1       // 1: 使能任务通知 (比信号量和队列更轻快)
#define configUSE_CO_ROUTINES                   0       // 0: 禁用协程 (官方已不推荐使用)

/*==================================================================================================
 * --- 4. 软件定时器模块 (按需开启) ---
 *================================================================================================*/
#define configUSE_TIMERS                        1       // 1: 使能软件定时器
#define configTIMER_TASK_PRIORITY               ( configMAX_PRIORITIES - 1 ) // 定时器服务任务的优先级
#define configTIMER_QUEUE_LENGTH                5       // 定时器命令队列长度
#define configTIMER_TASK_STACK_DEPTH            ( configMINIMAL_STACK_SIZE * 2 ) // 定时器服务任务的栈大小

/*==================================================================================================
 * --- 5. 钩子函数与调试模块 (强烈建议在调试阶段开启) ---
 *================================================================================================*/
/* 常用钩子函数 */
#define configUSE_IDLE_HOOK                     0       // 1: 启用空闲任务钩子函数 (vApplicationIdleHook)
#define configUSE_TICK_HOOK                     0       // 1: 启用滴答定时器钩子函数 (vApplicationTickHook)
#define configUSE_MALLOC_FAILED_HOOK            0       // 1: 启用动态内存分配失败钩子函数 (vApplicationMallocFailedHook)

/* 栈溢出检测 (调试时非常有用的功能) */
// 方法1和2选其一，方法2开销更大但更可靠
#define configCHECK_FOR_STACK_OVERFLOW          0       // 0:关闭, 1:方法一, 2:方法二
#if (configCHECK_FOR_STACK_OVERFLOW > 0)
    // 如果启用，必须提供一个 `vApplicationStackOverflowHook` 函数
    #define configRECORD_STACK_HIGH_ADDRESS     1
#endif

/* 任务状态查询与运行时间统计 */
#define configUSE_TRACE_FACILITY                1       // 1: 启用可视化跟踪与任务状态查询API
#define configUSE_STATS_FORMATTING_FUNCTIONS    1       // 1: 启用 vTaskList() 和 vTaskGetRunTimeStats()
#define configGENERATE_RUN_TIME_STATS           1       // 1: 使能任务运行时间统计
#if (configGENERATE_RUN_TIME_STATS == 1)
    // 必须提供一个高精度时钟源用于统计
    extern volatile unsigned long ulHighFrequencyTimerTicks;
    #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() ( ulHighFrequencyTimerTicks = 0UL )
    #define portGET_RUN_TIME_COUNTER_VALUE()         ulHighFrequencyTimerTicks
#endif

/*==================================================================================================
 * --- 6. 低功耗模式模块 (按需开启) ---
 *================================================================================================*/
#define configUSE_TICKLESS_IDLE                 1       // 1: 使能Tickless低功耗模式
#if (configUSE_TICKLESS_IDLE == 1)
    // 必须提供下面两个宏对应的函数实现
    #include "freertos_tasks.h"
    #define configPRE_SLEEP_PROCESSING( x )         PRE_SLEEP_PROCESSING()
    #define configPOST_SLEEP_PROCESSING( x )        POST_SLEEP_PROCESSING()
#endif

/*==================================================================================================
 * --- 7. 可选API函数使能 (保持默认即可) ---
 *================================================================================================*/
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetHandle                  1
#define INCLUDE_uxTaskGetStackHighWaterMark     1 // 栈历史剩余最小值API，配合栈溢出检测很有用
#define INCLUDE_eTaskGetState                   1

/*==================================================================================================
 * --- 8. MPU支持模块 (高级功能，仅特定MCU支持) ---
 *================================================================================================*/
#define configUSE_MPU                           0       // 0: 禁用MPU (内存保护单元)

/*==================================================================================================
 * --- 9. 断言与中断配置 (内核相关，通常不修改) ---
 *================================================================================================*/
//#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }
#define configASSERT( x )

#ifdef __NVIC_PRIO_BITS
    #define configPRIO_BITS                     __NVIC_PRIO_BITS
#else
    #define configPRIO_BITS                     4
#endif

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5
#define configKERNEL_INTERRUPT_PRIORITY                 ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY            ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* 中断服务函数重映射 */
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
