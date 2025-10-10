#include "stm32f10x.h"
#include "user_config.h"  // �����û�Ӳ�������ļ��������������ʼ��I2C����
#include "bsp_oled.h"     // ����OLEDӦ�ú���
#include "sys.h"          // �����������ϵͳʱ�ӳ�ʼ���ļ�
#include "delay.h"        // �������������ʱ�����ļ�

/**
 * @brief  ������
 * @param  ��
 * @retval ��
 */
int main(void)
{
    // 1. ��ʼ��ϵͳʱ�Ӻͻ������� (���磺�жϷ���)
    SYS_Init();
    // ��ʼ����ʱ����
    delay_init(); 

    // 2. ��ʼ��OLED��ص�Ӳ��
    //    ��������Ὺ�� GPIOG ��ʱ�ӣ�����ʼ�� PG14 �� PG15 ΪI2Cģʽ
    User_Config_Init(); 
    
    // 3. ��ʼ��OLED��Ļ����
    //    ���������ͨ��I2C����һϵ��ָ����������������Ļ
    OLED_Config();      
    
    // 4. ������Ļ (0x00Ϊȫ��)
    OLED_Clear(0x00);   
    
    // 5. ����Ļ����ʾһЩ���õ���Ϣ��������֤
    //    ����: ҳ(0-7), ��(0-127), �ַ���
    OLED_ShowString(0, 0, (uint8_t*)"Project: BSS_Hub");
    OLED_ShowString(2, 0, (uint8_t*)"SCL Pin: PG14");
    OLED_ShowString(4, 0, (uint8_t*)"SDA Pin: PG15");
    OLED_ShowString(6, 0, (uint8_t*)"OLED Init OK!");

    // 6. ������ѭ��������ͣ������
    while (1)
    {
        // �������С�������У���ѭ������ʲô��������
        // ��Ҳ�������������һЩ��̬Ч����������˸һ��LED�������Ļ�ϵ�ʱ�䡣
    }
}
