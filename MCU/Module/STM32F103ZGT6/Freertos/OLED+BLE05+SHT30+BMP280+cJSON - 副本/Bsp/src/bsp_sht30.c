#include "bsp_sht30.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

// SHT30 命令
#define SHT30_CMD_READ_SERIAL_NUMBER 0x3780
#define SHT30_CMD_READ_STATUS        0xF32D
#define SHT30_CMD_CLEAR_STATUS       0x3041
#define SHT30_CMD_HEATER_ENABLE      0x306D
#define SHT30_CMD_HEATER_DISABLE     0x3066
#define SHT30_CMD_SOFT_RESET         0x30A2
#define SHT30_CMD_MEAS_HIGH_REP      0x2400 // 高重复性测量
#define SHT30_CMD_MEAS_MED_REP       0x240B // 中重复性测量
#define SHT30_CMD_MEAS_LOW_REP       0x2416 // 低重复性测量

#define POLYNOMIAL 0x31 // CRC多项式: X^8 + X^5 + X^4 + 1

// 简单的延时函数
static void SHT30_Delay(volatile uint32_t count)
{
    while(count--);
}

/**
 * @brief SHT3X CRC校验函数
 */
static uint8_t SHT3X_CRC(uint8_t *data, uint8_t len)
{
    uint8_t crc = 0xFF;
    for(uint8_t byteCtr = 0; byteCtr < len; byteCtr++) {
        crc ^= (data[byteCtr]);
        for(uint8_t bit = 8; bit > 0; --bit) {
            if(crc & 0x80) {
                crc = (crc << 1) ^ POLYNOMIAL;
            } else {
                crc = (crc << 1);
            }
        }
    }
    return crc;
}

/**
 * @brief 向SHT30发送一条16位命令
 */
static uint8_t SHT30_Send_Cmd(I2C_Bus_t* bus, uint16_t cmd)
{
    //uint8_t ack;
    I2C_Start(bus);
    
    // 发送设备地址 + Write
    if (I2C_Write_Byte(bus, (SHT30_ADDRESS << 1) | 0) != 0) {
        I2C_Stop(bus);
        return 1; // NACK
    }
    
    // 发送命令高八位
    if (I2C_Write_Byte(bus, (uint8_t)(cmd >> 8)) != 0) {
        I2C_Stop(bus);
        return 1; // NACK
    }
    
    // 发送命令低八位
    if (I2C_Write_Byte(bus, (uint8_t)(cmd & 0xFF)) != 0) {
        I2C_Stop(bus);
        return 1; // NACK
    }
    
    I2C_Stop(bus);
    return 0; // Success
}

uint8_t SHT30_Init(I2C_Bus_t* bus)
{
    // 发送软复位命令
    if(SHT30_Send_Cmd(bus, SHT30_CMD_SOFT_RESET) != 0) {
        return 1; // 初始化失败
    }
    SHT30_Delay(50000); // 等待复位完成
    return 0;
}

uint8_t SHT30_Read_Humiture(I2C_Bus_t* bus, float* temperature, float* humidity)
{
    uint8_t data[6];
    uint8_t result = 1; // 默认结果为失败

    // --- 进入临界区，防止RTOS任务切换 ---
    taskENTER_CRITICAL();

    // 1. 发送测量命令
    if(SHT30_Send_Cmd(bus, SHT30_CMD_MEAS_HIGH_REP) != 0)
    {
        // 如果失败，直接退出临界区并返回
        taskEXIT_CRITICAL();
        return 1;
    }
    
    // --- 退出临界区，因为我们需要一个较长的延时，此时可以允许任务切换 ---
    taskEXIT_CRITICAL();
    
    // 2. 使用RTOS的延时函数等待传感器测量完成 (SHT30高精度测量最多需要15.5ms)
    // 我们延时20ms，确保足够
    vTaskDelay(pdMS_TO_TICKS(20));

    // --- 再次进入临界区，准备读取数据 ---
    taskENTER_CRITICAL();

    // 3. 读取6个字节的数据
    I2C_Start(bus);
    if(I2C_Write_Byte(bus, (SHT30_ADDRESS << 1) | 1) != 0) // 发送设备地址 + Read
    {
        I2C_Stop(bus);
        taskEXIT_CRITICAL();
        return 1; // NACK
    }

    data[0] = I2C_Read_Byte(bus, 1); // Temperature MSB, ACK
    data[1] = I2C_Read_Byte(bus, 1); // Temperature LSB, ACK
    data[2] = I2C_Read_Byte(bus, 1); // Temperature CRC, ACK
    data[3] = I2C_Read_Byte(bus, 1); // Humidity MSB, ACK
    data[4] = I2C_Read_Byte(bus, 1); // Humidity LSB, ACK
    data[5] = I2C_Read_Byte(bus, 0); // Humidity CRC, NACK
    
    I2C_Stop(bus);

    // --- 退出临界区 ---
    taskEXIT_CRITICAL();


    // 4. 校验数据
    if(SHT3X_CRC(data, 2) == data[2] && SHT3X_CRC(data + 3, 2) == data[5])
    {
        // 5. 计算温湿度值
        uint16_t temp_raw = (data[0] << 8) | data[1];
        uint16_t humi_raw = (data[3] << 8) | data[4];
        
        *temperature = -45.0f + 175.0f * (float)temp_raw / 65535.0f;
        *humidity    = 100.0f * (float)humi_raw / 65535.0f;
        
        result = 0; // 成功
    }
    
    return result; 
}
