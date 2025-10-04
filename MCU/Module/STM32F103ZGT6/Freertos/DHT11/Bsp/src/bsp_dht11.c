/**
 ****************************************************************************************************
 * @file        dht11.c
 * @author      ALIENTEK & YourName (Register-level modification)
 * @version     V2.0 - Pure Register Version
 * @date        2025-09-29
 * @brief       DHT11数字温湿度传感器 驱动代码 (纯寄存器版)
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 */

#include "bsp_dht11.h"
#include "delay.h"


/*
 * ================================================================================================
 * 内部GPIO模式配置函数
 * ================================================================================================
 */

/**
 * @brief       设置DHT11的DQ引脚模式
 * @param       mode: 0, 输出模式; 1, 输入模式
 * @retval      无
 */
static void dht11_dq_mode_set(uint8_t mode)
{
    uint32_t crh_val = DHT11_DQ_GPIO_PORT->CRH;
    crh_val &= ~(0x0F << 12); // 清除Pin11对应的CNF和MODE位 (bits 15:12)

    if (mode == 0) // 设置为通用推挽输出, 50MHz
    {
        crh_val |= (3 << 12); // MODE=11 (50MHz), CNF=00 (通用推挽)
    }
    else // 设置为上拉输入 (Input with Pull-up)
    {
        crh_val |= (8 << 12); // MODE=00 (输入), CNF=10 (上/下拉输入模式)
        // 在F1系列中, 配置为上/下拉输入后,
        // 通过ODR寄存器选择是上拉还是下拉: 写1为上拉, 写0为下拉。
        DHT11_DQ_GPIO_PORT->BSRR = DHT11_DQ_PIN; // 通过BSRR将ODR的对应位置1, 选择上拉
    }
    DHT11_DQ_GPIO_PORT->CRH = crh_val;
}


/*
 * ================================================================================================
 * DHT11 核心驱动函数
 * ================================================================================================
 */
 
/**
 * @brief       复位DHT11
 * @param       无
 * @retval      无
 */
static void dht11_reset(void)
{
    dht11_dq_mode_set(0);       // 设置为输出模式
    DHT11_DQ_OUT(0);            /* 拉低DQ */
    delay_ms(20);         /* 拉低至少18ms */
    DHT11_DQ_OUT(1);            /* 拉高DQ */
    delay_us(30);         /* 主机拉高20~40us */
    dht11_dq_mode_set(1);       // 设置为输入模式, 准备接收数据
}

/**
 * @brief       等待DHT11的回应
 * @param       无
 * @retval      0, DHT11正常
 * 1, DHT11异常/不存在
 */
static uint8_t dht11_check(void)
{
    uint8_t retry = 0;
    uint8_t rval = 0;

    // 等待DHT11将总线拉低 (约80us)
    // while循环+retry用来做超时判断, 防止程序卡死
    while (DHT11_DQ_IN && retry < 100)
    {
        retry++;
        delay_us(1);
    }

    if (retry >= 100)
    {
        rval = 1; // 超时失败
    }
    else
    {
        retry = 0;
        // DHT11拉低后会再次拉高 (约80us)
        while (!DHT11_DQ_IN && retry < 100)
        {
            retry++;
            delay_us(1);
        }
        if (retry >= 100)
        {
            rval = 1; // 超时失败
        }
    }
    
    return rval;
}

/**
 * @brief       从DHT11读取一个位
 * @param       无
 * @retval      读取到的位值: 0 / 1
 */
static uint8_t dht11_read_bit(void)
{
    uint8_t retry = 0;

    while (DHT11_DQ_IN && retry < 100)  /* 等待变为低电平 (每一位数据开始前的50us低电平结束) */
    {
        retry++;
        delay_us(1);
    }

    retry = 0;
    while (!DHT11_DQ_IN && retry < 100) /* 等待变高电平 (数据"0"或"1"的高电平开始) */
    {
        retry++;
        delay_us(1);
    }

    delay_us(40); // 等待40us

    if (DHT11_DQ_IN)    /* 40us后, 如果还是高电平, 说明是数据"1" (因为"1"的高电平约70us) */
    {
        // 等待数据位结束
        while(DHT11_DQ_IN);
        return 1;
    }
    else                /* 否则, 说明是数据"0" (因为"0"的高电平约26-28us) */
    {
        return 0;
    }
}

/**
 * @brief       从DHT11读取一个字节
 * @param       无
 * @retval      读到的数据
 */
static uint8_t dht11_read_byte(void)
{
    uint8_t i, data = 0;

    for (i = 0; i < 8; i++)
    {
        data <<= 1;
        data |= dht11_read_bit();
    }

    return data;
}

/**
 * @brief       从DHT11读取一次数据
 * @param       temp: 温度值(整数)
 * @param       humi: 湿度值(整数)
 * @retval      0, 读取成功
 * 1, 读取失败
 */
uint8_t dht11_read_data(uint8_t *temp, uint8_t *humi)
{
    uint8_t buf[5];
    uint8_t i;
    
    dht11_reset();

    if (dht11_check() == 0)
    {
        for (i = 0; i < 5; i++)
        {
            buf[i] = dht11_read_byte();
        }

        if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
        {
            *humi = buf[0];
            *temp = buf[2];
        }
        else
        {
            return 1; // 校验和错误
        }
    }
    else
    {
        return 1; // 传感器无响应
    }
    
    return 0; // 读取成功
}

/**
 * @brief       初始化DHT11
 * @param       无
 * @retval      0, 初始化成功
 * 1, DHT11不存在/不正常
 */
uint8_t dht11_init(void)
{

    DHT11_DQ_GPIO_CLK_ENABLE();
    
    dht11_reset();
    return dht11_check();
}
