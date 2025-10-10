#include "bsp_oled.h"
#include "user_config.h"
#include "FreeRTOS.h"
#include "task.h"

#define OLED_ADDRESS    0x78

// ���� bsp_oled.c ����Ҫ�޸ĵĺ���
void OLED_Write(uint8_t data, OLED_MODE mode)
{
    // --- �����ٽ�������ֹRTOS�����л� ---
    taskENTER_CRITICAL();

    uint8_t control_byte = 0x00; // I2C�����У���ʾ�����ֽ�������

    if (mode == OLED_DATA) {
        control_byte = 0x40; // I2C�����У���ʾ�����ֽ�������
    }

    I2C_Start(&g_oled_bus);
    I2C_Write_Byte(&g_oled_bus, OLED_ADDRESS); // �����豸��ַ
    I2C_Write_Byte(&g_oled_bus, control_byte); // ���Ϳ����ֽ�
    I2C_Write_Byte(&g_oled_bus, data);         // ��������������
    I2C_Stop(&g_oled_bus);
    
    // --- �˳��ٽ������ָ������л� ---
    taskEXIT_CRITICAL();
}

void OLED_Config(void)
{
    // OLED�������
    OLED_Write(0XAE,OLED_CMD);  //����ʾ��
    OLED_Write(0x00,OLED_CMD);  //������ʼ��ַ ��
    OLED_Write(0x10,OLED_CMD);  //��
    OLED_Write(0x40,OLED_CMD);  //������ʼ��
    OLED_Write(0x81,OLED_CMD);  //�޸���������
    OLED_Write(0xFF,OLED_CMD);  //�������
    OLED_Write(0xA1,OLED_CMD);  //���ҷ���
    OLED_Write(0xA6,OLED_CMD);  //������
    OLED_Write(0xA8,OLED_CMD);  // multiplex ratio
    OLED_Write(0x3F,OLED_CMD);  // duty = 1/64
    OLED_Write(0xC8,OLED_CMD);  // Com scan direction���·���
    OLED_Write(0xD3,OLED_CMD);  // set display offset
    OLED_Write(0x00,OLED_CMD);
    OLED_Write(0xD5,OLED_CMD);  // set osc division
    OLED_Write(0x80,OLED_CMD);
    OLED_Write(0xD9,OLED_CMD);  // set pre-charge period
    OLED_Write(0x1f,OLED_CMD);
    OLED_Write(0xDA,OLED_CMD);  // set COM pins
    OLED_Write(0x12,OLED_CMD);
    OLED_Write(0xdb,OLED_CMD);  // set vcomh
    OLED_Write(0x30,OLED_CMD);
    OLED_Write(0x8d,OLED_CMD);  // set charge pump enable
    OLED_Write(0x14,OLED_CMD);
    OLED_Write(0xAF,OLED_CMD);  // ����ʾ��
    OLED_Clear(OLED_CLOSE);
}

void OLED_SetPos(uint16_t x, uint16_t y)
{
    OLED_Write(0xB0+x,OLED_CMD);
    OLED_Write(0x00 + (y & 0x0f),OLED_CMD);
    OLED_Write(0x10 + ((y & 0xf0)>>4),OLED_CMD);
}

void OLED_Clear(uint8_t data)
{
    uint8_t i, j;
    for(i=0;i<OLED_PAGE;i++)
    {
        OLED_SetPos(i,0);
        for(j=0;j<OLED_WIGH;j++)
        {
            OLED_Write(data,OLED_DATA);
        }
    }
}


/****************************
�������ƣ�OLED_ShowASCII
�������ã�OLED��ʾ�ַ�
����������
	page	ҳ����0~7��
	line	������0~127��
	buf	��ģ����
��������ֵ����
�������ߣ�
����ʱ�䣺2021.04.23
�޸�ʱ�䣺2021.04.23
����˵����
	�ַ�ȡģ��PCtoLCD2002��:���� ���� ���� C51
		���룺����Ϊ1 ���룺����Ϊ1
****************************/
void OLED_ShowASCII(uint8_t page,uint8_t line,uint8_t *buf)
{
	uint8_t i=0,j=0;
	
	for(i=0;i<2;i++)
	{
		OLED_SetPos(page+i,line);
		for(j=0;j<8;j++)
		{
			OLED_Write(*buf,OLED_DATA);
			buf++;
		}
	}
}

/****************************
�������ƣ�OLED_ShowChinese
�������ã�OLED��ʾ����
����������
	page	ҳ����0~7��
	line	������0~127��
	buf		��ģ����
��������ֵ����
�������ߣ�WRH
����ʱ�䣺2021.04.23
�޸�ʱ�䣺2021.04.23
����˵����
	�ַ�ȡģ��PCtoLCD2002��:���� ���� ���� C51
		���룺����Ϊ1 ���룺����Ϊ1
****************************/
void OLED_ShowChinese(uint8_t page,uint8_t line,uint8_t *buf)
{
	uint8_t i=0,j=0;
	
	for(i=0;i<2;i++)
	{
		OLED_SetPos(page+i,line);
		for(j=0;j<16;j++)
		{
			OLED_Write(*buf,OLED_DATA);
			buf++;
		}
	}
}

/****************************
�������ƣ�OLED_ShowPhoto
�������ã�OLED��ʾͼƬ
����������
	page	ҳ����0~7��
	line	������0~127��
	High	ͼƬ�߶�
	Wide	ͼƬ���
	buf		��ģ����
��������ֵ����
����ʱ�䣺2021.04.23
�޸�ʱ�䣺2021.04.23
����˵����
	ͼƬȡģ��Img2LCD��:
		����ˮƽ���ֽڴ�ֱ
		��ɫ
		�ֽ������ط���
****************************/
void OLED_ShowPhoto(uint8_t page,uint8_t line,uint8_t High,uint8_t Wide,uint8_t *buf) //�ߺͿ�Ϊ��Ƭ���ص㣬�������в���
{
	uint8_t i=0,j=0,temp_high = 0;
	
	if((High%8) == 0)
		temp_high = High/8;
	else
		temp_high = High/8 + 1;
	
	for(i=0;i<temp_high;i++)
	{
		OLED_SetPos(page+i,line);
		for(j=0;j<Wide;j++)
		{
			OLED_Write(*buf,OLED_DATA);
			buf++;
		}
	}
}

/****************************
�������ƣ�OLED_ShowString
�������ã�OLED��ʾ�ַ���
����������
	page	ҳ����0~7��
	line	������0~127��
	str		��ģ����
��������ֵ����
�������ߣ�WRH
����ʱ�䣺2021.04.23
�޸�ʱ�䣺2021.04.23
****************************/
void OLED_ShowString(uint8_t page,uint8_t line,uint8_t *str)
{
	uint8_t Temp_page = 0,Temp_line = 0;
	int Lib_offset = 0;
	Temp_page = page;
	Temp_line = line;
	
	while(*str != '\0')
	{
		if(*str < 128)
		{
			if(Temp_line > 120)
			{
				Temp_page += 2;
				Temp_line = 0;
			}
				
			Lib_offset = ASCII_GetOffset(*str);
			if(Lib_offset != (-1))
				OLED_ShowASCII(Temp_page,Temp_line,&ASCIIFont_Lib[Lib_offset*16]);
			else
			{
				if(*str == 10)
					Temp_page += 2;
					Temp_line = 0;
			}
			Temp_line+=8;
			str++;
		}
		else
		{
			if(Temp_line > 112)
			{
				Temp_page += 2;
				Temp_line = 0;
			}
			
				Lib_offset = Chinese_GetOffset(*str,*(str+1));
				if(Lib_offset != (-1))
					OLED_ShowChinese(Temp_page,Temp_line,&ChineseFont_Lib[Lib_offset*32]);

			Temp_line+=16;
			str+=2;
		}
	}
}
