# 📂 完整项目结构

```
protocol_analyzer/
│
├── 📄 analyzer.py                    # 主程序入口 (核心)
├── 📄 requirements.txt               # Python依赖清单
├── 📄 README.md                      # 项目说明文档
├── 📄 PROJECT_STRUCTURE.md          # 本文件
├── 📄 setup.sh                      # Linux/Mac 安装脚本
├── 📄 setup.bat                     # Windows 安装脚本
│
├── 📁 data/                         # 数据输入目录
│   ├── 📄 README.md                 # CSV格式说明
│   └── 📄 [your_capture.csv]       # 放置Saleae导出的CSV
│
├── 📁 output/                       # 分析结果输出目录
│   ├── 📄 analysis.json             # JSON格式输出 (自动生成)
│   └── 📄 analysis.html             # HTML报告 (自动生成)
│
├── 📁 decoders/                     # 协议解码器模块
│   ├── 📄 __init__.py               # 包初始化
│   ├── 📄 i2c_decoder.py            # I2C协议解码器 ✅
│   ├── 📄 spi_decoder.py            # SPI协议解码器 ✅
│   ├── 📄 uart_decoder.py           # UART/USART解码器 ✅
│   ├── 📄 qspi_decoder.py           # QSPI协议解码器 ✅
│   ├── 📄 sdio_decoder.py           # SDIO协议解码器 ✅
│   ├── 📄 fsmc_decoder.py           # FSMC协议解码器 ✅
│   └── 📄 fmc_decoder.py            # FMC协议解码器 ✅
│
├── 📁 exporters/                    # 导出模块
│   ├── 📄 __init__.py               # 包初始化
│   ├── 📄 json_exporter.py          # JSON导出器 (AI可读)
│   └── 📄 html_exporter.py          # HTML导出器 (人类可读)
│
└── 📁 utils/                        # 工具模块
    ├── 📄 __init__.py               # 包初始化
    ├── 📄 signal_analyzer.py        # 信号分析与协议识别 🧠
    └── 📄 channel_mapper.py         # 通道映射工具
```

## 🗂️ 文件说明

### 核心文件

#### `analyzer.py` ⭐
- **功能**: 主程序入口
- **职责**:
  - 加载CSV数据
  - 调用信号分析器识别协议
  - 调度对应的解码器
  - 导出JSON和HTML结果
- **运行**: `python analyzer.py`

#### `requirements.txt`
- **内容**:
  ```
  pandas>=1.5.0
  numpy>=1.23.0
  jinja2>=3.1.0
  ```

### 解码器模块 (`decoders/`)

每个解码器都实现相同的接口:

```python
class XxxDecoder:
    def decode(self, df: pd.DataFrame) -> List[Dict]:
        """
        解码协议数据
        
        Args:
            df: 包含Time和信号列的DataFrame
            
        Returns:
            事务列表，每个事务是一个字典
        """
        pass
```

#### `i2c_decoder.py` 📘
- **检测**: START/STOP条件
- **解析**: 7位地址, R/W位, 数据字节, ACK/NACK
- **设备识别**: 内置常见I2C设备地址库

#### `spi_decoder.py` 📙
- **检测**: CS片选信号
- **解析**: MOSI/MISO数据流
- **支持**: CPOL/CPHA配置

#### `uart_decoder.py` 📗
- **特性**: 自动波特率检测
- **解析**: 起始位, 数据位, 停止位, 奇偶校验
- **输出**: HEX值和ASCII字符

#### `qspi_decoder.py` 📕
- **模式**: 1/2/4线自动切换
- **阶段**: 命令/地址/数据识别
- **命令库**: 常见Flash命令表

#### `sdio_decoder.py` 📓
- **解析**: CMD命令帧, DAT数据块
- **命令识别**: SD卡标准命令
- **CRC校验**: 帧完整性检查

#### `fsmc_decoder.py` / `fmc_decoder.py` 📔
- **总线宽度**: 8/16/32位自动检测
- **操作类型**: 读/写识别
- **地址**: 可选地址总线解析

### 工具模块 (`utils/`)

#### `signal_analyzer.py` 🧠
**最核心的自动识别模块**

- **功能**: 自动分析信号特征并识别协议类型
- **策略**:
  - 时钟信号检测 (周期性、占空比)
  - 数据信号检测 (跳变率、模式)
  - 片选信号检测 (高电平空闲)
  - UART特征检测 (异步、突发)
  - 控制信号检测 (低跳变率)

- **识别流程**:
  ```
  通道数量判断 → 信号特征分析 → 协议匹配 → 通道映射
  ```

#### `channel_mapper.py`
- **功能**: 物理通道到逻辑信号映射
- **示例**:
  ```
  Channel 0 → SCL (I2C)
  Channel 1 → SDA (I2C)
  ```

### 导出模块 (`exporters/`)

#### `json_exporter.py`
- **格式**: 结构化JSON
- **用途**: AI分析、程序处理
- **内容**: 
  - 统计信息
  - 按协议分组的事务
  - 完整事务列表

#### `