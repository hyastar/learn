"""
FSMC (Flexible Static Memory Controller) 协议解码器
支持: 并行数据总线, 读写操作识别
"""

import numpy as np


class FSMCDecoder:
    """FSMC协议解码器"""
    
    def __init__(self):
        pass
        
    def decode(self, df):
        """
        解码FSMC数据
        
        Args:
            df: DataFrame with columns: Time, NE, NWE, NOE, D0-D15
            
        Returns:
            list of transaction dicts
        """
        # 检查必需的控制信号
        if 'NE' not in df.columns:
            return []
        
        ne = df['NE'].values  # Chip Enable (低电平有效)
        nwe = df['NWE'].values if 'NWE' in df.columns else np.ones_like(ne)  # Write Enable
        noe = df['NOE'].values if 'NOE' in df.columns else np.ones_like(ne)  # Output Enable (Read)
        time = df['Time'].values if 'Time' in df.columns else np.arange(len(df))
        
        # 获取数据线
        data_cols = [col for col in df.columns if col.startswith('D') and col[1:].isdigit()]
        data_cols.sort(key=lambda x: int(x[1:]))
        
        if not data_cols:
            return []
        
        num_data_bits = len(data_cols)
        
        transactions = []
        
        for i in range(1, len(df)):
            ne_prev, ne_curr = ne[i-1], ne[i]
            nwe_prev, nwe_curr = nwe[i-1], nwe[i]
            noe_prev, noe_curr = noe[i-1], noe[i]
            
            # 只在NE有效时处理
            if ne_curr != 0:
                continue
            
            # 检测写操作 (NWE下降沿)
            if nwe_prev == 1 and nwe_curr == 0:
                # 读取数据总线
                data_value = 0
                for bit_idx, col in enumerate(data_cols):
                    data_value |= (int(df[col].values[i]) << bit_idx)
                
                transactions.append({
                    'protocol': 'FSMC',
                    'start_time': float(time[i]),
                    'operation': 'WRITE',
                    'data': data_value,
                    'data_width': num_data_bits
                })
            
            # 检测读操作 (NOE下降沿)
            elif noe_prev == 1 and noe_curr == 0:
                # 读取数据总线
                data_value = 0
                for bit_idx, col in enumerate(data_cols):
                    data_value |= (int(df[col].values[i]) << bit_idx)
                
                transactions.append({
                    'protocol': 'FSMC',
                    'start_time': float(time[i]),
                    'operation': 'READ',
                    'data': data_value,
                    'data_width': num_data_bits
                })
        
        return transactions