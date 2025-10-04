#include "stm32f10x.h"
#include "sys.h"             // ��������NVIC�жϷ���
#include "bsp_usart_it.h"    // ��������������printf
#include "freertos_tasks.h"  // FreeRTOS�������

/**
 * @brief  ������ - FreeRTOS �������
 * @note   main��������ֻ������ײ�ĳ�ʼ����Ȼ������FreeRTOS��
 * ����Ӧ�ò�ĳ�ʼ���������� freertos_tasks.c �й���
 */
int main(void)
{
    // 1. ����NVIC�ж����ȼ����飬����FreeRTOS��ȷ���е�ǰ��
    SYS_Init();

    // 2. ��ʼ������1��������115200������printf��ӡ��Ϣ
    USART1_Init(115200);

    // 3. ��ӡ������Ϣ
    printf("\r\n==================================\r\n");
    printf(" BSS_Hub - System Core Initialized.\r\n");
    printf(" Starting FreeRTOS Scheduler...\r\n");
    printf("==================================\r\n");

    // 4. ����FreeRTOS
    //    ��������ᴴ����ʼ���񲢿��������������
    //    ��������￪ʼ��FreeRTOS�ӹܣ������������Զ���᷵�ء�
    freertos_start();

    // -- ���������������´��뽫���ᱻִ�� --
    while (1)
    {
    }
}
