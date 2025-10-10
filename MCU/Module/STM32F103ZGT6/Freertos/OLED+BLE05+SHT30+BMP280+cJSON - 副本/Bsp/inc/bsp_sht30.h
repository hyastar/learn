#ifndef __BSP_SHT30_H
#define __BSP_SHT30_H

#include "bsp_i2c.h"

// SHT30 I2C address
#define SHT30_ADDRESS 0x44

/**
 * @brief 初始化SHT30传感器（发送软复位或特定配置）
 * @param bus 指向传感器所在的I2C总线对象
 * @return 0:成功, 1:失败
 */
uint8_t SHT30_Init(I2C_Bus_t* bus);

/**
 * @brief 从SHT30读取温度和湿度
 * @param bus 指向传感器所在的I2C总线对象
 * @param temperature 指向用于存储温度值的浮点数指针 (单位: °C)
 * @param humidity 指向用于存储湿度值的浮点数指针 (单位: %RH)
 * @return 0:成功, 1:读取或CRC校验失败
 */
uint8_t SHT30_Read_Humiture(I2C_Bus_t* bus, float* temperature, float* humidity);

#endif // __BSP_SHT30_H
