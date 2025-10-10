#!/usr/bin/env python3
"""
多协议逻辑分析仪数据解析器
支持自动识别并解析: I2C, SPI, UART, USART, QSPI, SDIO, FSMC, FMC
"""

import os
import sys
import pandas as pd
from pathlib import Path

# 导入解码器
from decoders.i2c_decoder import I2CDecoder
from decoders.spi_decoder import SPIDecoder
from decoders.uart_decoder import UARTDecoder
from decoders.qspi_decoder import QSPIDecoder
from decoders.sdio_decoder import SDIODecoder
from decoders.fsmc_decoder import FSMCDecoder
from decoders.fmc_decoder import FMCDecoder

# 导入导出器
from exporters.json_exporter import export_json
from exporters.html_exporter import export_html

# 导入工具
from utils.signal_analyzer import SignalAnalyzer
from utils.channel_mapper import ChannelMapper


class ProtocolAnalyzer:
    """主分析器类"""
    
    def __init__(self, data_dir="data", output_dir="output"):
        self.data_dir = Path(data_dir)
        self.output_dir = Path(output_dir)
        self.output_dir.mkdir(exist_ok=True)
        
        # 注册所有解码器
        self.decoders = {
            'I2C': I2CDecoder(),
            'SPI': SPIDecoder(),
            'UART': UARTDecoder(),
            'USART': UARTDecoder(),  # USART使用相同的UART解码器
            'QSPI': QSPIDecoder(),
            'SDIO': SDIODecoder(),
            'FSMC': FSMCDecoder(),
            'FMC': FMCDecoder()
        }
        
    def find_csv_files(self):
        """查找data目录下的所有CSV文件"""
        csv_files = list(self.data_dir.glob("*.csv"))
        if not csv_files:
            print(f"❌ 错误: 在 {self.data_dir} 目录下未找到CSV文件")
            print(f"   请将 Saleae Logic 导出的 CSV 文件放入 {self.data_dir}/ 目录")
            return None
        return csv_files[0]  # 返回第一个CSV文件
    
    def load_data(self, csv_path):
        """加载并预处理CSV数据"""
        print(f"📥 加载数据文件: {csv_path.name}")
        
        try:
            df = pd.read_csv(csv_path)
            
            # 标准化列名
            df.columns = [col.strip() for col in df.columns]
            
            # 检测时间列
            time_col = None
            for col in df.columns:
                if 'time' in col.lower():
                    time_col = col
                    break
            
            if time_col:
                df.rename(columns={time_col: 'Time'}, inplace=True)
            
            print(f"✅ 数据加载成功: {len(df)} 个采样点")
            print(f"📊 检测到通道: {[col for col in df.columns if col != 'Time']}")
            
            return df
            
        except Exception as e:
            print(f"❌ 读取CSV文件失败: {e}")
            return None
    
    def analyze(self):
        """主分析流程"""
        print("=" * 60)
        print("🔍 Saleae Logic 多协议自动分析器")
        print("=" * 60)
        
        # 1. 查找CSV文件
        csv_file = self.find_csv_files()
        if csv_file is None:
            return
        
        # 2. 加载数据
        df = self.load_data(csv_file)
        if df is None:
            return
        
        # 3. 分析信号特征并识别协议
        print("\n🔎 分析信号特征...")
        analyzer = SignalAnalyzer(df)
        detected_protocols = analyzer.detect_protocols()
        
        if not detected_protocols:
            print("❌ 未能识别出任何已知协议")
            return
        
        print(f"\n✨ 检测到协议: {', '.join([p['protocol'] for p in detected_protocols])}")
        
        # 4. 解码所有识别出的协议
        all_transactions = []
        
        for proto_info in detected_protocols:
            protocol = proto_info['protocol']
            channels = proto_info['channels']
            
            print(f"\n📘 解码 {protocol} 协议...")
            print(f"   使用通道: {list(channels.values())}")
            
            try:
                # 创建通道映射器
                mapper = ChannelMapper(df, channels)
                mapped_df = mapper.get_mapped_dataframe()
                
                # 调用对应的解码器
                if protocol in self.decoders:
                    decoder = self.decoders[protocol]
                    transactions = decoder.decode(mapped_df)
                    
                    if transactions:
                        all_transactions.extend(transactions)
                        print(f"   ✅ 解码完成: {len(transactions)} 个事务")
                    else:
                        print(f"   ⚠️  未检测到有效事务")
                else:
                    print(f"   ⚠️  暂不支持 {protocol} 协议解码")
                    
            except Exception as e:
                print(f"   ❌ 解码失败: {e}")
                import traceback
                traceback.print_exc()
        
        # 5. 导出结果
        if all_transactions:
            print(f"\n📤 导出 {len(all_transactions)} 个事务...")
            
            json_path = self.output_dir / "analysis.json"
            html_path = self.output_dir / "analysis.html"
            
            export_json(all_transactions, json_path)
            export_html(all_transactions, html_path)
            
            print("\n" + "=" * 60)
            print("✅ 分析完成！")
            print("=" * 60)
            print(f"🧠 JSON 输出 (AI/程序可读): {json_path}")
            print(f"📊 HTML 输出 (人类可读):     {html_path}")
            print("=" * 60)
        else:
            print("\n⚠️  未解析出任何有效事务")


def main():
    """主函数"""
    analyzer = ProtocolAnalyzer()
    analyzer.analyze()


if __name__ == "__main__":
    main()