"""
I2C 协议解码器
支持: START, STOP, 地址识别, 数据传输, ACK/NACK
"""

import numpy as np


class I2CDecoder:
    """I2C协议解码器"""
    
    # 常见I2C设备地址映射
    DEVICE_MAP = {
        0x3C: "OLED Display (SSD1306)",
        0x3D: "OLED Display (SSD1306)",
        0x44: "SHT30 Temp/Humidity Sensor",
        0x45: "SHT31 Temp/Humidity Sensor",
        0x48: "ADS1115 ADC / TMP102 Temp",
        0x50: "AT24C EEPROM",
        0x51: "AT24C EEPROM",
        0x68: "MPU6050 IMU / DS1307 RTC",
        0x69: "MPU6050 IMU (Alt)",
        0x76: "BMP280 Pressure Sensor",
        0x77: "BMP280 Pressure Sensor (Alt)",
        0xA0: "AT24C EEPROM (8-bit)",
    }
    
    def __init__(self):
        self.transactions = []
        
    def decode(self, df):
        """
        解码I2C数据
        
        Args:
            df: DataFrame with columns: Time, SCL, SDA
            
        Returns:
            list of transaction dicts
        """
        if 'SCL' not in df.columns or 'SDA' not in df.columns:
            return []
        
        scl = df['SCL'].values
        sda = df['SDA'].values
        time = df['Time'].values if 'Time' in df.columns else np.arange(len(df))
        
        transactions = []
        current_transaction = None
        current_byte = 0
        bit_count = 0
        in_transaction = False
        
        for i in range(1, len(df)):
            scl_prev, scl_curr = scl[i-1], scl[i]
            sda_prev, sda_curr = sda[i-1], sda[i]
            
            # 检测START条件: SCL为高时，SDA从高到低
            if scl_prev == 1 and scl_curr == 1:
                if sda_prev == 1 and sda_curr == 0:
                    # START detected
                    if current_transaction and not in_transaction:
                        # 重复START
                        pass
                    
                    current_transaction = {
                        'protocol': 'I2C',
                        'start_time': float(time[i]),
                        'stop_time': None,
                        'address_7bit': None,
                        'address_10bit': None,
                        'device_name': 'Unknown',
                        'operation': 'Unknown',
                        'address_ack': None,
                        'data_bytes': [],
                        'raw_data': []
                    }
                    in_transaction = True
                    bit_count = 0
                    current_byte = 0
                    continue
                
                # 检测STOP条件: SCL为高时，SDA从低到高
                elif sda_prev == 0 and sda_curr == 1:
                    # STOP detected
                    if current_transaction:
                        current_transaction['stop_time'] = float(time[i])
                        
                        # 解析第一个字节作为地址
                        if current_transaction['raw_data']:
                            addr_byte = current_transaction['raw_data'][0]
                            addr_7bit = addr_byte['value'] >> 1
                            rw_bit = addr_byte['value'] & 0x01
                            
                            current_transaction['address_7bit'] = addr_7bit
                            current_transaction['operation'] = 'Read' if rw_bit else 'Write'
                            current_transaction['address_ack'] = addr_byte['ack']
                            current_transaction['device_name'] = self.DEVICE_MAP.get(
                                addr_7bit, f"Unknown (0x{addr_7bit:02X})"
                            )
                            
                            # 数据字节是除第一个字节外的所有字节
                            current_transaction['data_bytes'] = current_transaction['raw_data'][1:]
                        
                        transactions.append(current_transaction)
                        current_transaction = None
                        in_transaction = False
                    continue
            
            if not in_transaction:
                continue
            
            # 在SCL上升沿采样SDA (数据位)
            if scl_prev == 0 and scl_curr == 1:
                if bit_count < 8:
                    # 数据位
                    current_byte = (current_byte << 1) | int(sda_curr)
                    bit_count += 1
                elif bit_count == 8:
                    # ACK/NACK位
                    ack = (sda_curr == 0)
                    
                    if current_transaction:
                        current_transaction['raw_data'].append({
                            'value': current_byte,
                            'ack': ack,
                            'time': float(time[i])
                        })
                    
                    bit_count = 0
                    current_byte = 0
        
        # 处理未正常结束的事务
        if current_transaction:
            current_transaction['stop_time'] = float(time[-1])
            transactions.append(current_transaction)
        
        return transactions
    
    def format_transaction(self, trans):
        """格式化单个事务为可读字符串"""
        lines = []
        lines.append(f"I2C Transaction @ {trans['start_time']:.6f}s")
        lines.append(f"  Device: {trans['device_name']}")
        lines.append(f"  Address: 0x{trans['address_7bit']:02X}")
        lines.append(f"  Operation: {trans['operation']}")
        lines.append(f"  Address ACK: {'Yes' if trans['address_ack'] else 'No'}")
        
        if trans['data_bytes']:
            data_str = ", ".join([
                f"0x{b['value']:02X}({'ACK' if b['ack'] else 'NACK'})"
                for b in trans['data_bytes']
            ])
            lines.append(f"  Data: {data_str}")
        
        return "\n".join(lines)