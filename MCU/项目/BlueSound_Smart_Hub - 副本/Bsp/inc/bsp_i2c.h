#ifndef __BSP_I2C_H
#define __BSP_I2C_H

#include "stm32f10x.h"

// 定义一个I2C总线结构体，用于描述SDA和SCL所用的GPIO引脚
typedef struct {
    GPIO_TypeDef* SDA_Port;
    uint16_t      SDA_Pin;
    GPIO_TypeDef* SCL_Port;
    uint16_t      SCL_Pin;
} I2C_Bus_t;


//============ 公共API函数声明 ============//

/**
 * @brief 初始化一条I2C总线所使用的GPIO引脚
 * @param bus 指向要操作的I2C总线对象
 */
void I2C_Init(I2C_Bus_t *bus);

/**
 * @brief 在指定的I2C总线上产生START信号
 * @param bus 指向要操作的I2C总线对象
 */
void I2C_Start(I2C_Bus_t *bus);

/**
 * @brief 在指定的I2C总线上产生STOP信号
 * @param bus 指向要操作的I2C总线对象
 */
void I2C_Stop(I2C_Bus_t *bus);

/**
 * @brief 在指定的I2C总线上写一个字节
 * @param bus 指向要操作的I2C总线对象
 * @param data 要写入的8位数据
 * @return 0: 收到ACK, 1: 收到NACK
 */
uint8_t I2C_Write_Byte(I2C_Bus_t *bus, uint8_t data);

/**
 * @brief 在指定的I2C总线上读一个字节
 * @param bus 指向要操作的I2C总线对象
 * @param ack 0: 发送NACK, 1: 发送ACK
 * @return 读取到的8位数据
 */
uint8_t I2C_Read_Byte(I2C_Bus_t *bus, uint8_t ack);



#endif // __BSP_I2C_H
