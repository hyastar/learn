#include "bsp_i2c.h"

//============ 内部宏定义和静态函数 ============//

// 内部使用的延时函数，用于控制I2C速度
// 注意：这是一个简单的软件延时，不精确，具体值需要根据你的系统时钟和所需I2C速率进行调整
// 对于100KHz的I2C，在72MHz主频下，延时值大约在30-50之间
static void I2C_Delay(void) {
    uint8_t i = 35; // 可调整此值
    while (i--);
}

// 通过BSRR和BRR寄存器快速操作GPIO
#define I2C_SDA_H(bus)      (bus)->SDA_Port->BSRR = (bus)->SDA_Pin
#define I2C_SDA_L(bus)      (bus)->SDA_Port->BRR  = (bus)->SDA_Pin
#define I2C_SCL_H(bus)      (bus)->SCL_Port->BSRR = (bus)->SCL_Pin
#define I2C_SCL_L(bus)      (bus)->SCL_Port->BRR  = (bus)->SCL_Pin

// 通过IDR寄存器读取SDA电平
#define I2C_SDA_Read(bus)   (((bus)->SDA_Port->IDR & (bus)->SDA_Pin) != 0)


// 内部函数：将指定的GPIO引脚配置为开漏输出模式 (纯寄存器操作)
static void Config_Pin_As_OpenDrain(GPIO_TypeDef* Port, uint16_t Pin) {
    uint32_t pinpos = 0;
    uint32_t tmpreg = 0;

    for (pinpos = 0; pinpos < 16; pinpos++) {
        if ((Pin >> pinpos) & 0x01) break;
    }

    if (pinpos < 8) {
        tmpreg = Port->CRL;
        tmpreg &= ~((0x0F) << (pinpos * 4));
        tmpreg |= (0x7) << (pinpos * 4); // CNF=01, MODE=11 -> 50MHz开漏输出
        Port->CRL = tmpreg;
    } else {
        tmpreg = Port->CRH;
        tmpreg &= ~((0x0F) << ((pinpos - 8) * 4));
        tmpreg |= (0x7) << ((pinpos - 8) * 4); // CNF=01, MODE=11 -> 50MHz开漏输出
        Port->CRH = tmpreg;
    }
}

// 内部函数：将指定的GPIO引脚配置为浮空输入模式 (纯寄存器操作)
static void Config_Pin_As_Input(GPIO_TypeDef* Port, uint16_t Pin) {
    uint32_t pinpos = 0;
    uint32_t tmpreg = 0;

    for (pinpos = 0; pinpos < 16; pinpos++) {
        if ((Pin >> pinpos) & 0x01) break;
    }

    if (pinpos < 8) {
        tmpreg = Port->CRL;
        tmpreg &= ~((0x0F) << (pinpos * 4));
        tmpreg |= (0x4) << (pinpos * 4); // CNF=01, MODE=00 -> 浮空输入
        Port->CRL = tmpreg;
    } else {
        tmpreg = Port->CRH;
        tmpreg &= ~((0x0F) << ((pinpos - 8) * 4));
        tmpreg |= (0x4) << ((pinpos - 8) * 4); // CNF=01, MODE=00 -> 浮空输入
        Port->CRH = tmpreg;
    }
}

// 内部函数：等待并检查ACK信号
static uint8_t I2C_Wait_Ack(I2C_Bus_t *bus) {
    uint8_t ack_val;
    
    I2C_SDA_H(bus); // 主机释放SDA
    Config_Pin_As_Input(bus->SDA_Port, bus->SDA_Pin); // 设置SDA为输入模式以读取从机信号
    I2C_Delay();
    I2C_SCL_H(bus);
    I2C_Delay();

    ack_val = I2C_SDA_Read(bus); // 读取ACK信号

    I2C_SCL_L(bus);
    I2C_Delay();
    Config_Pin_As_OpenDrain(bus->SDA_Port, bus->SDA_Pin); // 将SDA恢复为输出模式
    
    return ack_val; // 0 表示ACK, 1 表示NACK
}

// 内部函数：主机发送ACK信号
static void I2C_Ack(I2C_Bus_t *bus) {
    I2C_SCL_L(bus);
    I2C_SDA_L(bus); // 拉低SDA表示ACK
    I2C_Delay();
    I2C_SCL_H(bus);
    I2C_Delay();
    I2C_SCL_L(bus);
    I2C_SDA_H(bus); // 释放SDA
}

// 内部函数：主机发送NACK信号
static void I2C_NAck(I2C_Bus_t *bus) {
    I2C_SCL_L(bus);
    I2C_SDA_H(bus); // 保持SDA高电平表示NACK
    I2C_Delay();
    I2C_SCL_H(bus);
    I2C_Delay();
    I2C_SCL_L(bus);
}


//============ 公共API函数实现 ============//

void I2C_Init(I2C_Bus_t *bus) {
    // 假设对应GPIO端口的时钟已经在外部使能
    // e.g., RCC->APB2ENR |= RCC_APB2ENR_IOPB;
    
    Config_Pin_As_OpenDrain(bus->SDA_Port, bus->SDA_Pin);
    Config_Pin_As_OpenDrain(bus->SCL_Port, bus->SCL_Pin);

    // 确保总线空闲
    I2C_Stop(bus);
}

void I2C_Start(I2C_Bus_t *bus) {
    // 确保SDA和SCL都是高电平 (总线空闲)
    I2C_SDA_H(bus);
    I2C_SCL_H(bus);
    I2C_Delay();
    // SCL为高时，SDA从高变低
    I2C_SDA_L(bus);
    I2C_Delay();
    // 钳住总线，准备发送数据
    I2C_SCL_L(bus); 
}

void I2C_Stop(I2C_Bus_t *bus) {
    I2C_SCL_L(bus);
    I2C_SDA_L(bus);
    I2C_Delay();
    // SCL为高时，SDA从低变高
    I2C_SCL_H(bus);
    I2C_Delay();
    I2C_SDA_H(bus);
    I2C_Delay();
}

uint8_t I2C_Write_Byte(I2C_Bus_t *bus, uint8_t data) {
    uint8_t i;
    for (i = 0; i < 8; i++) {
        I2C_SCL_L(bus);
        I2C_Delay();
        if (data & 0x80) {
            I2C_SDA_H(bus);
        } else {
            I2C_SDA_L(bus);
        }
        data <<= 1;
        I2C_Delay();
        I2C_SCL_H(bus);
        I2C_Delay();
    }
    I2C_SCL_L(bus);
    return I2C_Wait_Ack(bus);
}

uint8_t I2C_Read_Byte(I2C_Bus_t *bus, uint8_t ack) {
    uint8_t i, receive = 0;

    I2C_SDA_H(bus); // 释放SDA，准备接收
    Config_Pin_As_Input(bus->SDA_Port, bus->SDA_Pin);

    for (i = 0; i < 8; i++) {
        I2C_SCL_L(bus);
        I2C_Delay();
        I2C_SCL_H(bus);
        
        receive <<= 1;
        if (I2C_SDA_Read(bus)) {
            receive |= 1;
        }
        I2C_Delay();
    }
    
    Config_Pin_As_OpenDrain(bus->SDA_Port, bus->SDA_Pin); // 将SDA恢复为输出模式

    if (ack) {
        I2C_Ack(bus);
    } else {
        I2C_NAck(bus);
    }

    return receive;
}
