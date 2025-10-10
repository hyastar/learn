"""
SPI 协议解码器
支持: 标准SPI (CPOL=0/1, CPHA=0/1), 片选检测, 全双工通信
"""

import numpy as np


class SPIDecoder:
    """SPI协议解码器"""
    
    def __init__(self, cpol=0, cpha=0):
        """
        Args:
            cpol: Clock Polarity (0 or 1)
            cpha: Clock Phase (0 or 1)
        """
        self.cpol = cpol
        self.cpha = cpha
        
    def decode(self, df):
        """
        解码SPI数据
        
        Args:
            df: DataFrame with columns: Time, SCLK, MOSI, [MISO], [CS]
            
        Returns:
            list of transaction dicts
        """
        if 'SCLK' not in df.columns or 'MOSI' not in df.columns:
            return []
        
        sclk = df['SCLK'].values
        mosi = df['MOSI'].values
        miso = df['MISO'].values if 'MISO' in df.columns else np.zeros_like(sclk)
        cs = df['CS'].values if 'CS' in df.columns else np.ones_like(sclk)
        time = df['Time'].values if 'Time' in df.columns else np.arange(len(df))
        
        transactions = []
        current_transaction = None
        mosi_byte = 0
        miso_byte = 0
        bit_count = 0
        
        # 确定采样边沿
        if self.cpha == 0:
            # CPHA=0: 第一个时钟边沿采样
            sample_edge = (1 if self.cpol == 0 else 0)
        else:
            # CPHA=1: 第二个时钟边沿采样
            sample_edge = (0 if self.cpol == 0 else 1)
        
        for i in range(1, len(df)):
            cs_prev, cs_curr = cs[i-1], cs[i]
            sclk_prev, sclk_curr = sclk[i-1], sclk[i]
            
            # 检测CS下降沿 (传输开始)
            if cs_prev == 1 and cs_curr == 0:
                current_transaction = {
                    'protocol': 'SPI',
                    'start_time': float(time[i]),
                    'stop_time': None,
                    'mosi_bytes': [],
                    'miso_bytes': [],
                    'byte_count': 0
                }
                bit_count = 0
                mosi_byte = 0
                miso_byte = 0
                continue
            
            # 检测CS上升沿 (传输结束)
            if cs_prev == 0 and cs_curr == 1:
                if current_transaction:
                    # 处理最后一个不完整的字节
                    if bit_count > 0:
                        current_transaction['mosi_bytes'].append({
                            'value': mosi_byte,
                            'bits': bit_count
                        })
                        current_transaction['miso_bytes'].append({
                            'value': miso_byte,
                            'bits': bit_count
                        })
                    
                    current_transaction['stop_time'] = float(time[i])
                    current_transaction['byte_count'] = len(current_transaction['mosi_bytes'])
                    transactions.append(current_transaction)
                    current_transaction = None
                continue
            
            # 只在CS为低时处理数据
            if cs_curr != 0:
                continue
            
            # 检测采样边沿
            if self.cpol == 0:
                # CPOL=0: 空闲时为低
                if sclk_prev == 0 and sclk_curr == 1:
                    edge_type = 1  # 上升沿
                elif sclk_prev == 1 and sclk_curr == 0:
                    edge_type = 0  # 下降沿
                else:
                    continue
            else:
                # CPOL=1: 空闲时为高
                if sclk_prev == 1 and sclk_curr == 0:
                    edge_type = 1  # 下降沿
                elif sclk_prev == 0 and sclk_curr == 1:
                    edge_type = 0  # 上升沿
                else:
                    continue
            
            # 在采样边沿读取数据
            if edge_type == sample_edge:
                mosi_byte = (mosi_byte << 1) | int(mosi[i])
                miso_byte = (miso_byte << 1) | int(miso[i])
                bit_count += 1
                
                # 一个字节完成
                if bit_count == 8:
                    if current_transaction:
                        current_transaction['mosi_bytes'].append({
                            'value': mosi_byte,
                            'bits': 8,
                            'time': float(time[i])
                        })
                        current_transaction['miso_bytes'].append({
                            'value': miso_byte,
                            'bits': 8,
                            'time': float(time[i])
                        })
                    
                    bit_count = 0
                    mosi_byte = 0
                    miso_byte = 0
        
        # 处理未正常结束的事务
        if current_transaction:
            current_transaction['stop_time'] = float(time[-1])
            current_transaction['byte_count'] = len(current_transaction['mosi_bytes'])
            transactions.append(current_transaction)
        
        return transactions