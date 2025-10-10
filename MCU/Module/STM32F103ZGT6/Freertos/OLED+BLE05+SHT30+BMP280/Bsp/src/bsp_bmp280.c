#include "bsp_bmp280.h"
#include "FreeRTOS.h"
#include "task.h"
#include <math.h>

// BMP280 寄存器地址和ID
#define BMP280_7BIT_ADDR                (0x76)
#define BMP280_DEFAULT_CHIP_ID          (0x58)
#define BMP280_CHIP_ID_REG              (0xD0)
#define BMP280_RESET_REG                (0xE0)
#define BMP280_CTRL_MEAS_REG            (0xF4)
#define BMP280_CONFIG_REG               (0xF5)
#define BMP280_PRESSURE_MSB_REG         (0xF7)
#define BMP280_CALIB_DATA_REG           (0x88)
#define BMP280_CALIB_DATA_LENGTH        (24)
#define BMP280_DATA_FRAME_LENGTH        (6)

// BMP280 配置参数
#define BMP280_OVERSAMP_16X             (0x05)
#define BMP280_OVERSAMP_8X              (0x04)
#define BMP280_NORMAL_MODE              (0x03)
#define BMP280_CONFIG_MODE  (BMP280_OVERSAMP_8X << 2 | BMP280_OVERSAMP_16X << 5 | BMP280_NORMAL_MODE)

// 校准数据结构体
typedef struct {
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;
    int32_t  t_fine;
} bmp280_calib_data_t;

// 全局变量保存校准数据
static bmp280_calib_data_t g_bmp280_calib;

// ===== 底层I2C读写函数 (RTOS安全) =====
static uint8_t BMP280_Write_Byte(I2C_Bus_t* bus, uint8_t reg, uint8_t data) {
    uint8_t status = 1;
    taskENTER_CRITICAL();
    I2C_Start(bus);
    if (I2C_Write_Byte(bus, (BMP280_7BIT_ADDR << 1) | 0) == 0) {
        if (I2C_Write_Byte(bus, reg) == 0) {
            if (I2C_Write_Byte(bus, data) == 0) {
                status = 0;
            }
        }
    }
    I2C_Stop(bus);
    taskEXIT_CRITICAL();
    return status;
}

static uint8_t BMP280_Read_Bytes(I2C_Bus_t* bus, uint8_t reg, uint8_t* buffer, uint8_t len) {
    uint8_t status = 1;
    taskENTER_CRITICAL();
    I2C_Start(bus);
    if (I2C_Write_Byte(bus, (BMP280_7BIT_ADDR << 1) | 0) == 0) {
        if (I2C_Write_Byte(bus, reg) == 0) {
            I2C_Start(bus);
            if (I2C_Write_Byte(bus, (BMP280_7BIT_ADDR << 1) | 1) == 0) {
                for (uint8_t i = 0; i < len; i++) {
                    buffer[i] = I2C_Read_Byte(bus, (i == len - 1) ? 0 : 1);
                }
                status = 0;
            }
        }
    }
    I2C_Stop(bus);
    taskEXIT_CRITICAL();
    return status;
}

// ===== 官方补偿算法 (来自Bosch Sensortec) =====
static int32_t compensate_T(int32_t adc_T) {
    int32_t var1, var2, T;
    var1 = ((((adc_T >> 3) - ((int32_t)g_bmp280_calib.dig_T1 << 1))) * ((int32_t)g_bmp280_calib.dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)g_bmp280_calib.dig_T1)) * ((adc_T >> 4) - ((int32_t)g_bmp280_calib.dig_T1))) >> 12) * ((int32_t)g_bmp280_calib.dig_T3)) >> 14;
    g_bmp280_calib.t_fine = var1 + var2;
    T = (g_bmp280_calib.t_fine * 5 + 128) >> 8;
    return T;
}

static uint32_t compensate_P(int32_t adc_P) {
    int64_t var1, var2, p;
    var1 = ((int64_t)g_bmp280_calib.t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)g_bmp280_calib.dig_P6;
    var2 = var2 + ((var1 * (int64_t)g_bmp280_calib.dig_P5) << 17);
    var2 = var2 + (((int64_t)g_bmp280_calib.dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)g_bmp280_calib.dig_P3) >> 8) + ((var1 * (int64_t)g_bmp280_calib.dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)g_bmp280_calib.dig_P1) >> 33;
    if (var1 == 0) return 0;
    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)g_bmp280_calib.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)g_bmp280_calib.dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)g_bmp280_calib.dig_P7) << 4);
    return (uint32_t)p;
}

static float pressure_to_altitude(float pressure_hPa) {
    if (pressure_hPa > 0) {
        return 44330.0 * (1.0 - pow(pressure_hPa / 1013.25, 0.1903));
    }
    return 0;
}

// ===== 公共API函数实现 =====
uint8_t BMP280_Init(I2C_Bus_t* bus) {
    uint8_t chip_id = 0;
    if (BMP280_Read_Bytes(bus, BMP280_CHIP_ID_REG, &chip_id, 1) != 0 || chip_id != BMP280_DEFAULT_CHIP_ID) {
        return 1; // ID读取失败或ID不匹配
    }

    if (BMP280_Read_Bytes(bus, BMP280_CALIB_DATA_REG, (uint8_t*)&g_bmp280_calib, BMP280_CALIB_DATA_LENGTH) != 0) {
        return 1; // 读取校准数据失败
    }

    if (BMP280_Write_Byte(bus, BMP280_CTRL_MEAS_REG, BMP280_CONFIG_MODE) != 0) {
        return 1; // 写入测量控制寄存器失败
    }

    if (BMP280_Write_Byte(bus, BMP280_CONFIG_REG, (5 << 2)) != 0) {
        return 1; // 写入配置寄存器失败
    }

    return 0; // 初始化成功
}

uint8_t BMP280_Get_Data(I2C_Bus_t* bus, float* pressure, float* temperature, float* altitude) {
    uint8_t data[BMP280_DATA_FRAME_LENGTH];
    
    if (BMP280_Read_Bytes(bus, BMP280_PRESSURE_MSB_REG, data, BMP280_DATA_FRAME_LENGTH) != 0) {
        return 1; // 读取传感器数据失败
    }

    int32_t adc_P = (int32_t)(((uint32_t)(data[0]) << 12) | (((uint32_t)(data[1])) << 4) | ((uint32_t)data[2] >> 4));
    int32_t adc_T = (int32_t)(((uint32_t)(data[3]) << 12) | (((uint32_t)(data[4])) << 4) | ((uint32_t)data[5] >> 4));

    if (adc_P == 0x80000 || adc_T == 0x80000) { // 无效数据
        return 1;
    }

    int32_t temp_comp = compensate_T(adc_T);
    uint32_t pres_comp = compensate_P(adc_P);

    *temperature = (float)temp_comp / 100.0f;
    *pressure = (float)pres_comp / 256.0f / 100.0f; // 最终单位hPa
    *altitude = pressure_to_altitude(*pressure);

    return 0; // 成功
}
