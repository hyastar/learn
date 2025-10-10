#ifndef __BSP_BMP280_H
#define __BSP_BMP280_H

#include "bsp_i2c.h"
#include <stdint.h>

/**
 * @brief 初始化BMP280传感器
 * @param bus 指向传感器所在的I2C总线对象
 * @return 0:成功, 1:失败 (ID错误或通信失败)
 */
uint8_t BMP280_Init(I2C_Bus_t* bus);

/**
 * @brief 从BMP280读取数据
 * @param bus 指向传感器所在的I2C总线对象
 * @param pressure 指向用于存储气压值的浮点数指针 (单位: hPa)
 * @param temperature 指向用于存储温度值的浮点数指针 (单位: °C)
 * @param altitude 指向用于存储海拔高度的浮点数指针 (单位: m)
 * @return 0:成功, 1:失败
 */
uint8_t BMP280_Get_Data(I2C_Bus_t* bus, float* pressure, float* temperature, float* altitude);

#endif // __BSP_BMP280_H
