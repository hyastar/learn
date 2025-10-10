#include "bsp_mq5.h"
#include "bsp_adc.h"
#include <math.h>

void MQ5_Init(void)
{
    /* 引脚和 ADC 已在 adc.c 里初始化 */
}

MQ5_Data_t MQ5_GetData(void)
{
    MQ5_Data_t sensor_data;
    uint16_t adc_val = adc_dma_buffer[1]; // MQ5 = ch1
    
    // 原始 ADC
    sensor_data.raw_adc_avg = adc_val;
    // 转电压
    sensor_data.voltage = (float)adc_val * 3.3f / 4096.0f;

    // 直接用 CSDN 文章里的公式换算 ppm
    // ppm = (电压 * 210) + 10
    sensor_data.ppm = sensor_data.voltage * 210.0f + 10.0f - 443.0f;

    // 限幅，避免异常
    if (sensor_data.ppm < 0) {
        sensor_data.ppm = 0;
    }
    if (sensor_data.ppm > 10000.0f) {
        sensor_data.ppm = 10000.0f;
    }

    return sensor_data;
}

