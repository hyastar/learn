#include "bsp_oled.h"
#include "user_config.h"
#include "FreeRTOS.h"
#include "task.h"

#define OLED_ADDRESS    0x78

// 这是 bsp_oled.c 中需要修改的函数
void OLED_Write(uint8_t data, OLED_MODE mode)
{
    // --- 进入临界区，防止RTOS任务切换 ---
    taskENTER_CRITICAL();

    uint8_t control_byte = 0x00; // I2C传输中，表示后续字节是命令

    if (mode == OLED_DATA) {
        control_byte = 0x40; // I2C传输中，表示后续字节是数据
    }

    I2C_Start(&g_oled_bus);
    I2C_Write_Byte(&g_oled_bus, OLED_ADDRESS); // 发送设备地址
    I2C_Write_Byte(&g_oled_bus, control_byte); // 发送控制字节
    I2C_Write_Byte(&g_oled_bus, data);         // 发送真正的数据
    I2C_Stop(&g_oled_bus);
    
    // --- 退出临界区，恢复任务切换 ---
    taskEXIT_CRITICAL();
}

void OLED_Config(void)
{
    // OLED驱动编程
    OLED_Write(0XAE,OLED_CMD);  //关显示屏
    OLED_Write(0x00,OLED_CMD);  //设置起始地址 低
    OLED_Write(0x10,OLED_CMD);  //高
    OLED_Write(0x40,OLED_CMD);  //设置起始行
    OLED_Write(0x81,OLED_CMD);  //修改亮度命令
    OLED_Write(0xFF,OLED_CMD);  //最大亮度
    OLED_Write(0xA1,OLED_CMD);  //左右反置
    OLED_Write(0xA6,OLED_CMD);  //正反向
    OLED_Write(0xA8,OLED_CMD);  // multiplex ratio
    OLED_Write(0x3F,OLED_CMD);  // duty = 1/64
    OLED_Write(0xC8,OLED_CMD);  // Com scan direction上下反置
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
    OLED_Write(0xAF,OLED_CMD);  // 开显示屏
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
函数名称：OLED_ShowASCII
函数作用：OLED显示字符
函数参数：
	page	页数（0~7）
	line	列数（0~127）
	buf	字模数组
函数返回值：无
函数作者：
创建时间：2021.04.23
修改时间：2021.04.23
补充说明：
	字符取模（PCtoLCD2002）:阴码 列行 逆向 C51
		阳码：背景为1 阴码：字体为1
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
函数名称：OLED_ShowChinese
函数作用：OLED显示汉字
函数参数：
	page	页数（0~7）
	line	列数（0~127）
	buf		字模数组
函数返回值：无
函数作者：WRH
创建时间：2021.04.23
修改时间：2021.04.23
补充说明：
	字符取模（PCtoLCD2002）:阴码 列行 逆向 C51
		阳码：背景为1 阴码：字体为1
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
函数名称：OLED_ShowPhoto
函数作用：OLED显示图片
函数参数：
	page	页数（0~7）
	line	列数（0~127）
	High	图片高度
	Wide	图片宽度
	buf		字模数组
函数返回值：无
创建时间：2021.04.23
修改时间：2021.04.23
补充说明：
	图片取模（Img2LCD）:
		数据水平，字节垂直
		单色
		字节内像素反序
****************************/
void OLED_ShowPhoto(uint8_t page,uint8_t line,uint8_t High,uint8_t Wide,uint8_t *buf) //高和宽为照片像素点，在属性中查找
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
函数名称：OLED_ShowString
函数作用：OLED显示字符串
函数参数：
	page	页数（0~7）
	line	列数（0~127）
	str		字模数组
函数返回值：无
函数作者：WRH
创建时间：2021.04.23
修改时间：2021.04.23
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
