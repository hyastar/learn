# 🔍 Saleae Logic 多协议自动分析器

一个功能强大的逻辑分析仪数据解析框架，支持自动识别和解码多种通信协议。

## ✨ 特性

- 🤖 **自动协议识别** - 无需手动指定协议类型
- 🔌 **多协议支持** - I2C, SPI, UART/USART, QSPI, SDIO, FSMC, FMC
- 📊 **双格式输出** - JSON (AI/程序可读) + HTML (人类可读)
- 🎨 **精美报告** - 现代化交互式HTML界面
- 🚀 **即插即用** - 只需替换CSV文件即可运行

## 📦 支持的协议

| 协议 | 说明 | 自动识别 |
|------|------|---------|
| **I2C** | 两线串行通信 (SCL/SDA) | ✅ |
| **SPI** | 高速同步串行 (SCLK/MOSI/MISO/CS) | ✅ |
| **UART/USART** | 异步串行通信 (RX/TX) | ✅ |
| **QSPI** | 四线SPI (CLK/IO0-3/CS) | ✅ |
| **SDIO** | SD卡接口 (CLK/CMD/DAT0-3) | ✅ |
| **FSMC** | 并行存储控制器 (NE/NWE/NOE/D0-15) | ✅ |
| **FMC** | 灵活存储控制器 (NE/NWE/NOE/D0-31) | ✅ |

## 🗂️ 项目结构

```
protocol_analyzer/
│
├── analyzer.py              # 主程序入口
├── requirements.txt         # Python依赖
├── README.md               # 使用说明
│
├── data/                   # 数据目录（放置CSV文件）
│   └── [your_capture.csv]  # Saleae导出的CSV
│
├── output/                 # 输出目录
│   ├── analysis.json       # JSON格式结果
│   └── analysis.html       # HTML格式报告
│
├── decoders/               # 协议解码器
│   ├── __init__.py
│   ├── i2c_decoder.py
│   ├── spi_decoder.py
│   ├── uart_decoder.py
│   ├── qspi_decoder.py
│   ├── sdio_decoder.py
│   ├── fsmc_decoder.py
│   └── fmc_decoder.py
│
├── exporters/              # 导出模块
│   ├── __init__.py
│   ├── json_exporter.py
│   └── html_exporter.py
│
└── utils/                  # 工具模块
    ├── __init__.py
    ├── signal_analyzer.py  # 协议自动识别
    └── channel_mapper.py   # 通道映射
```

## 🚀 快速开始

### 1. 安装依赖

```bash
pip install -r requirements.txt
```

### 2. 导出Saleae数据

在Saleae Logic软件中:
1. 完成数据采集
2. 点击 **Options** → **Export Data**
3. 选择 **CSV** 格式
4. 保存到 `data/` 目录

### 3. 运行分析

```bash
python analyzer.py
```

程序将自动:
- 📥 加载 `data/` 目录下的CSV文件
- 🔎 分析信号特征并识别协议
- 🧠 解码所有事务
- 📤 生成JSON和HTML报告

### 4. 查看结果

- **JSON输出**: `output/analysis.json` - 用于程序处理或AI分析
- **HTML报告**: `output/analysis.html` - 在浏览器中打开查看精美报告

## 📋 使用示例

### I2C 示例
```bash
# 假设你采集了OLED显示屏的I2C通信
# 只需将CSV放入data/目录，运行analyzer.py
# 输出将包含:
# - 设备地址识别 (例如: 0x3C - OLED Display)
# - 读/写操作
# - 每个字节的ACK/NACK状态
```

### SPI 示例
```bash
# 采集Flash芯片的SPI通信
# 自动解析:
# - MOSI数据流 (主机发送)
# - MISO数据流 (从机返回)
# - 片选时序
```

### 混合协议
```bash
# 如果你同时采集了I2C和UART:
# 通道0-1: I2C (SCL/SDA)
# 通道2-3: UART (RX/TX)
# 程序会自动识别并分别解码
```

## ⚙️ 高级配置

### 自定义I2C设备地址

编辑 `decoders/i2c_decoder.py`:

```python
DEVICE_MAP = {
    0x3C: "OLED Display (SSD1306)",
    0x68: "MPU6050 IMU",
    0xYY: "Your Custom Device",  # 添加你的设备
}
```

### 调整SPI参数

编辑 `analyzer.py` 中的解码器初始化:

```python
spi_decoder = SPIDecoder(cpol=0, cpha=0)  # 调整时钟极性和相位
```

### 指定UART波特率

```python
uart_decoder = UARTDecoder(baud_rate=115200)  # 设置固定波特率
```

## 📊 输出格式

### JSON 结构

```json
{
  "statistics": {
    "total_transactions": 42,
    "by_protocol": {
      "I2C": 15,
      "SPI": 27
    }
  },
  "transactions": [
    {
      "protocol": "I2C",
      "start_time": 0.001234,
      "device_name": "OLED Display",
      "address_7bit": 60,
      "operation": "Write",
      "data_bytes": [...]
    }
  ]
}
```

### HTML 报告特性

- 📈 协议统计仪表盘
- 🎨 按协议分组的彩色表格
- 🔍 十六进制数据高亮显示
- ✅ ACK/NACK状态可视化
- 📱 响应式设计，支持移动端

## 🛠️ 故障排除

### CSV文件未找到
```
❌ 错误: 在 data 目录下未找到CSV文件
```
**解决**: 确保CSV文件放在 `data/` 目录下

### 未识别协议
```
❌ 未能识别出任何已知协议
```
**解决**:
1. 检查CSV列名是否正确
2. 确认信号质量良好
3. 尝试手动指定协议类型

### 依赖缺失
```
ModuleNotFoundError: No module named 'pandas'
```
**解决**: 运行 `pip install -r requirements.txt`

## 🔧 扩展开发

### 添加新协议

1. 在 `decoders/` 创建新解码器:

```python
# decoders/can_decoder.py
class CANDecoder:
    def decode(self, df):
        # 实现CAN协议解码逻辑
        return transactions
```

2. 在 `utils/signal_analyzer.py` 添加识别逻辑:

```python
def _detect_can(self):
    # 实现CAN协议特征检测
    pass
```

3. 在 `analyzer.py` 注册解码器:

```python
self.decoders['CAN'] = CANDecoder()
```

## 📝 常见I2C设备地址

| 地址 | 设备 |
|------|------|
| 0x3C/0x3D | OLED显示屏 (SSD1306) |
| 0x44/0x45 | 温湿度传感器 (SHT30/31) |
| 0x48 | ADC (ADS1115) |
| 0x50-0x57 | EEPROM (AT24C系列) |
| 0x68/0x69 | IMU (MPU6050) / RTC (DS1307) |
| 0x76/0x77 | 气压传感器 (BMP280) |

## 🤝 贡献

欢迎提交Issue和Pull Request！

## 📄 许可

MIT License - 可自由使用和修改

## 🙏 致谢

- Saleae Logic - 优秀的逻辑分析仪软件
- Python生态系统 - pandas, numpy, jinja2

---

**作者**: Protocol Analyzer Team  
**版本**: 2.0  
**更新**: 2025-10