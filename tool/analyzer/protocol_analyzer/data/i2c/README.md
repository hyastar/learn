# 📁 数据目录说明

## Saleae Logic CSV 导出格式

将 Saleae Logic 导出的 CSV 文件放在此目录下。

### 导出步骤

1. 在 Saleae Logic 软件中完成数据采集
2. 点击菜单: **Options** → **Export Data**
3. 选择格式: **CSV (Comma Separated Values)**
4. 保存文件到此目录

### CSV 格式示例

#### I2C 示例 (2通道)
```csv
Time [s],Channel 0,Channel 1
0.000000,1,1
0.000001,1,1
0.000002,0,1
0.000003,0,0
...
```

#### SPI 示例 (4通道)
```csv
Time [s],Channel 0,Channel 1,Channel 2,Channel 3
0.000000,0,0,0,1
0.000001,1,0,0,1
0.000002,0,1,0,0
...
```

### 通道命名规范

程序会自动识别以下命名:

**I2C:**
- Channel 0 / SCL → 时钟线
- Channel 1 / SDA → 数据线

**SPI:**
- Channel 0 / SCLK → 时钟
- Channel 1 / MOSI → 主出从入
- Channel 2 / MISO → 主入从出
- Channel 3 / CS / NSS → 片选

**UART:**
- Channel 0 / RX → 接收
- Channel 1 / TX → 发送

**QSPI:**
- Channel 0 / CLK → 时钟
- Channel 1-4 / IO0-IO3 → 数据线
- Channel 5 / CS → 片选

**SDIO:**
- Channel 0 / CLK → 时钟
- Channel 1 / CMD → 命令线
- Channel 2-5 / DAT0-DAT3 → 数据线

**FSMC/FMC:**
- NE / NCE → 片选
- NWE → 写使能
- NOE → 读使能
- D0-D15/D31 → 数据总线
- A0-A23 → 地址总线 (可选)

### 注意事项

⚠️ **重要**: 
- CSV 必须包含时间列 (Time [s] 或 Time)
- 数据列应为 0 或 1 (逻辑电平)
- 列名可以是 "Channel 0", "Channel 1" 或协议特定名称
- 程序会自动检测协议类型，无需手动配置

### 文件大小限制

- 建议单个CSV文件 < 500MB
- 如果文件太大，考虑在 Saleae 中缩短采集时间或降低采样率

### 测试数据

如果需要测试程序，可以创建一个简单的I2C测试文件:

```csv
Time [s],Channel 0,Channel 1
0.0,1,1
0.00001,1,0
0.00002,0,0
0.00003,0,0
0.00004,0,1
0.00005,1,1
```

将此内容保存为 `test.csv` 放在此目录即可测试。