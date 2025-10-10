# ⚡ 快速开始指南

## 🚀 30秒上手

```bash
# 1. 安装依赖
pip install -r requirements.txt

# 2. 放入CSV文件
# 将 Saleae 导出的 CSV 放入 data/ 目录

# 3. 运行分析
python analyzer.py

# 4. 查看结果
# output/analysis.html  (浏览器打开)
# output/analysis.json  (程序处理)
```

## 📋 命令速查

| 操作 | 命令 |
|------|------|
| 安装 (Windows) | `setup.bat` |
| 安装 (Linux/Mac) | `bash setup.sh` |
| 运行分析 | `python analyzer.py` |
| 查看帮助 | `python analyzer.py --help` |

## 🔧 Saleae 导出设置

1. **打开** Saleae Logic
2. **采集** 数据 (点击Start)
3. **导出** Options → Export Data
4. **格式** 选择 CSV
5. **保存** 到 `data/` 目录

### 推荐采样率

| 协议 | 最低采样率 | 推荐采样率 |
|------|-----------|-----------|
| I2C (100kHz) | 400kHz | 1MHz |
| I2C (400kHz) | 1.6MHz | 4MHz |
| SPI (1MHz) | 4MHz | 10MHz |
| UART (115200) | 460kHz | 1MHz |
| QSPI (10MHz) | 40MHz | 100MHz |

## 📊 支持的协议

| 协议 | 通道数 | 状态 | 示例应用 |
|------|-------|------|---------|
| **I2C** | 2 | ✅ | 传感器、EEPROM、RTC |
| **SPI** | 3-4 | ✅ | Flash、ADC、显示屏 |
| **UART** | 1-2 | ✅ | 串口通信、GPS |
| **QSPI** | 6 | ✅ | 高速Flash |
| **SDIO** | 4-6 | ✅ | SD卡、WiFi模块 |
| **FSMC** | 4+ | ✅ | 并行LCD、SRAM |
| **FMC** | 4+ | ✅ | DDR、NOR Flash |

## 🎯 常用场景

### 场景1: 调试I2C传感器
```bash
# 1. 连接逻辑分析仪
#    CH0 → SCL
#    CH1 → SDA

# 2. 采集数据并导出 CSV

# 3. 运行分析
python analyzer.py

# 4. 查看结果
#    - 确认设备地址
#    - 检查ACK状态
#    - 分析数据内容
```

### 场景2: 分析SPI Flash通信
```bash
# 1. 连接
#    CH0 → SCLK
#    CH1 → MOSI
#    CH2 → MISO
#    CH3 → CS

# 2. 导出CSV

# 3. 运行
python analyzer.py

# 4. 查看
#    - 识别Flash命令
#    - 检查读写数据
#    - 验证时序
```

### 场景3: 混合协议分析
```bash
# 假设同时采集 I2C + UART
#    CH0-1 → I2C (SCL/SDA)
#    CH2-3 → UART (RX/TX)

# 程序会自动识别两种协议并分别解码！
```

## 📁 文件结构速查

```
protocol_analyzer/
├── analyzer.py          ← 运行这个
├── data/
│   └── *.csv           ← 放CSV这里
└── output/
    ├── analysis.json   ← JSON结果
    └── analysis.html   ← HTML报告
```

## 🎨 输出示例

### JSON 输出
```json
{
  "statistics": {
    "total_transactions": 15,
    "by_protocol": {
      "I2C": 15
    }
  },
  "transactions": [
    {
      "protocol": "I2C",
      "start_time": 0.001234,
      "device_name": "OLED Display (SSD1306)",
      "address_7bit": 60,
      "operation": "Write",
      "data_bytes": [
        {"value": 0, "ack": true},
        {"value": 16, "ack": true}
      ]
    }
  ]
}
```

### HTML 报告特性
- 🎨 深色现代主题
- 📊 协议分组显示
- 🔍 数据高亮
- ✅ ACK/NACK 状态
- 📱 响应式设计

## 🔍 常见I2C设备地址

| 地址 | 设备 |
|------|------|
| `0x3C` | OLED (SSD1306) |
| `0x44` | SHT30 温湿度 |
| `0x48` | ADS1115 ADC |
| `0x50` | AT24C EEPROM |
| `0x68` | MPU6050 / DS1307 |
| `0x76` | BMP280 气压 |

## ⚠️ 故障排除

| 问题 | 解决方案 |
|------|---------|
| **CSV未找到** | 确认文件在 `data/` 目录 |
| **协议未识别** | 检查信号质量和采样率 |
| **数据错误** | 验证协议参数设置 |
| **依赖缺失** | 运行 `pip install -r requirements.txt` |
| **HTML打开失败** | 尝试不同浏览器 |

## 💻 系统要求

- **Python**: 3.7 或更高
- **内存**: 最低 512MB (推荐 2GB+)
- **存储**: 100MB (不含数据文件)
- **操作系统**: Windows / Linux / macOS

## 🔧 配置选项

### 自定义I2C设备
编辑 `decoders/i2c_decoder.py`:
```python
DEVICE_MAP = {
    0x3C: "OLED Display",
    0xYY: "Your Device",  # 添加自定义设备
}
```

### 设置UART波特率
编辑 `analyzer.py`:
```python
uart_decoder = UARTDecoder(baud_rate=115200)  # 指定波特率
```

### 配置SPI模式
```python
spi_decoder = SPIDecoder(cpol=0, cpha=0)  # Mode 0
```

## 📞 获取帮助

1. **查看文档**: `README.md`
2. **项目结构**: `PROJECT_STRUCTURE.md`
3. **GitHub Issues**: 提交问题
4. **示例数据**: 使用 `setup.bat/sh` 生成测试数据

## 🎓 学习路径

1. ✅ **快速开始** (本文档)
2. 📖 **详细说明** (README.md)
3. 🏗️ **架构理解** (PROJECT_STRUCTURE.md)
4. 🔧 **自定义扩展** (添加新协议)

## ⌨️ 常用技巧

### 批量处理
```bash
# 处理多个CSV文件
for file in data/*.csv; do
    python analyzer.py "$file"
done
```

### 查看JSON
```bash
# Linux/Mac
cat output/analysis.json | jq .

# Windows
type output\analysis.json | jq .
```

### 快速测试
```bash
# 生成测试数据
python setup.sh  # 选择 Y 创建测试数据

# 立即分析
python analyzer.py
```

## 🎉 完成！

现在你可以开始使用了！

记住这3步:
1. **放入CSV** → `data/`
2. **运行分析** → `python analyzer.py`
3. **查看报告** → `output/analysis.html`

---

**祝你使用愉快！** 🚀

如有问题，请查看完整文档或提交Issue。