"""
信号分析器 - 自动识别协议类型
支持: I2C, SPI, UART, QSPI, SDIO, FSMC, FMC
"""

import numpy as np
import pandas as pd
from collections import Counter


class SignalAnalyzer:
    """信号特征分析与协议识别"""
    
    def __init__(self, df):
        self.df = df
        self.channels = [col for col in df.columns if col != 'Time']
        self.num_channels = len(self.channels)
        
    def detect_protocols(self):
        """主检测函数 - 返回所有可能的协议"""
        results = []
        
        # 按通道数量进行初步筛选
        if self.num_channels >= 2:
            # 检测I2C (2线: SCL, SDA)
            i2c_result = self._detect_i2c()
            if i2c_result:
                results.append(i2c_result)
                
        if self.num_channels >= 2:
            # 检测UART/USART (1-2线: RX, TX)
            uart_result = self._detect_uart()
            if uart_result:
                results.append(uart_result)
        
        if self.num_channels >= 3:
            # 检测SPI (3-4线: SCLK, MOSI, MISO, CS)
            spi_result = self._detect_spi()
            if spi_result:
                results.append(spi_result)
        
        if self.num_channels >= 6:
            # 检测QSPI (6线: CLK, IO0-3, CS)
            qspi_result = self._detect_qspi()
            if qspi_result:
                results.append(qspi_result)
        
        if self.num_channels >= 4:
            # 检测SDIO (4-6线: CLK, CMD, DAT0-3)
            sdio_result = self._detect_sdio()
            if sdio_result:
                results.append(sdio_result)
        
        if self.num_channels >= 4:
            # 检测FSMC/FMC (多线: 地址、数据、控制线)
            fsmc_result = self._detect_fsmc()
            if fsmc_result:
                results.append(fsmc_result)
        
        return results
    
    def _detect_i2c(self):
        """检测I2C协议"""
        # I2C特征: 2条线，有明显的时钟同步特征
        if self.num_channels < 2:
            return None
        
        for i in range(len(self.channels)):
            for j in range(i + 1, len(self.channels)):
                ch1, ch2 = self.channels[i], self.channels[j]
                
                # 计算信号特征
                sig1 = self.df[ch1].values
                sig2 = self.df[ch2].values
                
                # I2C特征检测
                if self._is_clock_signal(sig1) and self._is_data_signal(sig2):
                    return {
                        'protocol': 'I2C',
                        'channels': {'SCL': ch1, 'SDA': ch2},
                        'confidence': 0.9
                    }
                elif self._is_clock_signal(sig2) and self._is_data_signal(sig1):
                    return {
                        'protocol': 'I2C',
                        'channels': {'SCL': ch2, 'SDA': ch1},
                        'confidence': 0.9
                    }
        
        return None
    
    def _detect_spi(self):
        """检测SPI协议"""
        if self.num_channels < 3:
            return None
        
        # SPI特征: 需要时钟线 + 至少1条数据线 + 可选CS
        clock_candidates = []
        data_candidates = []
        cs_candidates = []
        
        for ch in self.channels:
            sig = self.df[ch].values
            
            if self._is_clock_signal(sig):
                clock_candidates.append(ch)
            elif self._is_chip_select(sig):
                cs_candidates.append(ch)
            else:
                data_candidates.append(ch)
        
        if clock_candidates and len(data_candidates) >= 1:
            result = {
                'protocol': 'SPI',
                'channels': {
                    'SCLK': clock_candidates[0],
                },
                'confidence': 0.85
            }
            
            # 分配MOSI/MISO
            if len(data_candidates) >= 1:
                result['channels']['MOSI'] = data_candidates[0]
            if len(data_candidates) >= 2:
                result['channels']['MISO'] = data_candidates[1]
            if cs_candidates:
                result['channels']['CS'] = cs_candidates[0]
            
            return result
        
        return None
    
    def _detect_uart(self):
        """检测UART/USART协议"""
        if self.num_channels < 1:
            return None
        
        # UART特征: 异步串行，有起始位和停止位
        uart_candidates = []
        
        for ch in self.channels:
            sig = self.df[ch].values
            
            # 检查是否有UART特征
            if self._is_uart_signal(sig):
                uart_candidates.append(ch)
        
        if uart_candidates:
            result = {
                'protocol': 'UART',
                'channels': {},
                'confidence': 0.75
            }
            
            if len(uart_candidates) >= 1:
                result['channels']['RX'] = uart_candidates[0]
            if len(uart_candidates) >= 2:
                result['channels']['TX'] = uart_candidates[1]
            
            return result
        
        return None
    
    def _detect_qspi(self):
        """检测QSPI协议"""
        if self.num_channels < 6:
            return None
        
        # QSPI特征: 1条时钟 + 4条数据线(IO0-3) + 1条CS
        clock_candidates = []
        data_candidates = []
        cs_candidates = []
        
        for ch in self.channels:
            sig = self.df[ch].values
            
            if self._is_clock_signal(sig):
                clock_candidates.append(ch)
            elif self._is_chip_select(sig):
                cs_candidates.append(ch)
            else:
                data_candidates.append(ch)
        
        if clock_candidates and len(data_candidates) >= 4 and cs_candidates:
            return {
                'protocol': 'QSPI',
                'channels': {
                    'CLK': clock_candidates[0],
                    'IO0': data_candidates[0],
                    'IO1': data_candidates[1],
                    'IO2': data_candidates[2],
                    'IO3': data_candidates[3],
                    'CS': cs_candidates[0]
                },
                'confidence': 0.8
            }
        
        return None
    
    def _detect_sdio(self):
        """检测SDIO协议"""
        if self.num_channels < 4:
            return None
        
        # SDIO特征: 1条时钟 + 1条CMD + 1-4条数据线
        clock_candidates = []
        cmd_candidates = []
        data_candidates = []
        
        for ch in self.channels:
            sig = self.df[ch].values
            
            if self._is_clock_signal(sig):
                clock_candidates.append(ch)
            else:
                data_candidates.append(ch)
        
        if clock_candidates and len(data_candidates) >= 2:
            result = {
                'protocol': 'SDIO',
                'channels': {
                    'CLK': clock_candidates[0],
                    'CMD': data_candidates[0],
                },
                'confidence': 0.7
            }
            
            # 添加数据线
            for i in range(1, min(5, len(data_candidates))):
                result['channels'][f'DAT{i-1}'] = data_candidates[i]
            
            return result
        
        return None
    
    def _detect_fsmc(self):
        """检测FSMC/FMC协议"""
        if self.num_channels < 4:
            return None
        
        # FSMC特征: 多条并行数据线 + 控制线
        # 这是一个简化的检测，实际FSMC可能需要更复杂的分析
        
        control_candidates = []
        data_candidates = []
        
        for ch in self.channels:
            sig = self.df[ch].values
            
            # 控制信号通常变化较少
            if self._is_control_signal(sig):
                control_candidates.append(ch)
            else:
                data_candidates.append(ch)
        
        if len(control_candidates) >= 2 and len(data_candidates) >= 2:
            result = {
                'protocol': 'FSMC',
                'channels': {},
                'confidence': 0.6
            }
            
            # 分配控制线
            if len(control_candidates) >= 1:
                result['channels']['NE'] = control_candidates[0]
            if len(control_candidates) >= 2:
                result['channels']['NWE'] = control_candidates[1]
            if len(control_candidates) >= 3:
                result['channels']['NOE'] = control_candidates[2]
            
            # 分配数据线
            for i, ch in enumerate(data_candidates[:16]):
                result['channels'][f'D{i}'] = ch
            
            return result
        
        return None
    
    # ========== 信号特征判断函数 ==========
    
    def _is_clock_signal(self, signal):
        """判断是否为时钟信号"""
        # 时钟信号特征: 周期性、占空比接近50%、边沿密集
        if len(signal) < 10:
            return False
        
        # 计算跳变次数
        transitions = np.sum(np.abs(np.diff(signal)) > 0)
        transition_rate = transitions / len(signal)
        
        # 时钟信号跳变频繁 (>5%)
        if transition_rate < 0.05:
            return False
        
        # 计算占空比
        high_ratio = np.mean(signal)
        
        # 占空比在30%-70%之间认为是时钟
        return 0.3 <= high_ratio <= 0.7
    
    def _is_data_signal(self, signal):
        """判断是否为数据信号"""
        # 数据信号特征: 有高有低，但不像时钟那么规律
        if len(signal) < 10:
            return False
        
        transitions = np.sum(np.abs(np.diff(signal)) > 0)
        transition_rate = transitions / len(signal)
        
        # 数据线跳变率通常低于时钟
        return 0.01 <= transition_rate <= 0.4
    
    def _is_chip_select(self, signal):
        """判断是否为片选信号"""
        # CS信号特征: 大部分时间为高电平，偶尔拉低
        if len(signal) < 10:
            return False
        
        high_ratio = np.mean(signal)
        transitions = np.sum(np.abs(np.diff(signal)) > 0)
        
        # CS大部分时间为高，跳变次数少
        return high_ratio > 0.8 and transitions < len(signal) * 0.1
    
    def _is_uart_signal(self, signal):
        """判断是否为UART信号"""
        # UART特征: 空闲时为高电平，有突发式的数据包
        if len(signal) < 100:
            return False
        
        high_ratio = np.mean(signal)
        transitions = np.sum(np.abs(np.diff(signal)) > 0)
        transition_rate = transitions / len(signal)
        
        # UART空闲时为高，有适度跳变
        return high_ratio > 0.5 and 0.02 <= transition_rate <= 0.3
    
    def _is_control_signal(self, signal):
        """判断是否为控制信号"""
        # 控制信号特征: 变化较少，维持某个状态较长时间
        if len(signal) < 10:
            return False
        
        transitions = np.sum(np.abs(np.diff(signal)) > 0)
        transition_rate = transitions / len(signal)
        
        # 控制信号跳变率很低
        return transition_rate < 0.05