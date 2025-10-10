import React, { useState, useEffect, useRef } from 'react';
import { Bluetooth, Cpu, LineChart, Wifi, ThermometerSun, Gauge, Lightbulb, LightbulbOff, Zap, Wind, Droplets, Compass, Activity, Radio, Database, Camera, Volume2, Flame, Settings, FileText, Heart, MessageCircle, Sparkles, TrendingUp, BarChart3, Clock, MapPin, Navigation } from 'lucide-react';
import { LineChart as RechartsLine, Line, XAxis, YAxis, CartesianGrid, Tooltip, ResponsiveContainer, AreaChart, Area, RadarChart, PolarGrid, PolarAngleAxis, PolarRadiusAxis, Radar } from 'recharts';

// 3D姿态显示组件 - 优化版
function Cube3D({ roll, pitch, yaw }) {
  const canvasRef = useRef(null);

  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    
    const ctx = canvas.getContext('2d');
    const width = canvas.width;
    const height = canvas.height;
    const centerX = width / 2;
    const centerY = height / 2;

    // 渐变背景
    const bgGradient = ctx.createLinearGradient(0, 0, 0, height);
    bgGradient.addColorStop(0, '#0ea5e9');
    bgGradient.addColorStop(0.5, '#38bdf8');
    bgGradient.addColorStop(1, '#7dd3fc');
    ctx.fillStyle = bgGradient;
    ctx.fillRect(0, 0, width, height);

    // 云朵装饰
    ctx.fillStyle = 'rgba(255, 255, 255, 0.3)';
    ctx.beginPath();
    ctx.arc(80, 40, 20, 0, Math.PI * 2);
    ctx.arc(100, 35, 25, 0, Math.PI * 2);
    ctx.arc(120, 40, 20, 0, Math.PI * 2);
    ctx.fill();

    ctx.beginPath();
    ctx.arc(280, 60, 18, 0, Math.PI * 2);
    ctx.arc(295, 58, 22, 0, Math.PI * 2);
    ctx.arc(310, 62, 16, 0, Math.PI * 2);
    ctx.fill();

    // 地平线
    const horizonY = centerY + pitch * 1.2;
    const groundGradient = ctx.createLinearGradient(0, horizonY, 0, height);
    groundGradient.addColorStop(0, '#84cc16');
    groundGradient.addColorStop(1, '#65a30d');
    ctx.fillStyle = groundGradient;
    ctx.fillRect(0, horizonY, width, height - horizonY);
    
    // 地平线线条
    ctx.strokeStyle = '#fbbf24';
    ctx.lineWidth = 3;
    ctx.setLineDash([15, 8]);
    ctx.beginPath();
    ctx.moveTo(0, horizonY);
    ctx.lineTo(width, horizonY);
    ctx.stroke();
    ctx.setLineDash([]);

    // 飞机阴影
    ctx.save();
    ctx.translate(centerX + 10, centerY + 15);
    ctx.rotate(roll * Math.PI / 180);
    ctx.fillStyle = 'rgba(0, 0, 0, 0.15)';
    ctx.beginPath();
    ctx.ellipse(0, 0, 80, 50, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();

    // 飞机主体
    ctx.save();
    ctx.translate(centerX, centerY);
    ctx.rotate(roll * Math.PI / 180);

    // 机身主体 - 渐变效果
    const bodyGradient = ctx.createLinearGradient(-20, -40, 20, 40);
    bodyGradient.addColorStop(0, '#f1f5f9');
    bodyGradient.addColorStop(0.5, '#e2e8f0');
    bodyGradient.addColorStop(1, '#cbd5e1');
    ctx.fillStyle = bodyGradient;
    ctx.strokeStyle = '#64748b';
    ctx.lineWidth = 2.5;
    ctx.beginPath();
    ctx.ellipse(0, 0, 18, 45, 0, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();

    // 左翼 - 红色系
    const leftWingGradient = ctx.createLinearGradient(-20, 0, -70, 0);
    leftWingGradient.addColorStop(0, '#ef4444');
    leftWingGradient.addColorStop(1, '#dc2626');
    ctx.fillStyle = leftWingGradient;
    ctx.strokeStyle = '#991b1b';
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.moveTo(-18, 0);
    ctx.lineTo(-75, -12);
    ctx.lineTo(-75, -8);
    ctx.lineTo(-65, 12);
    ctx.closePath();
    ctx.fill();
    ctx.stroke();

    // 右翼 - 蓝色系
    const rightWingGradient = ctx.createLinearGradient(20, 0, 70, 0);
    rightWingGradient.addColorStop(0, '#3b82f6');
    rightWingGradient.addColorStop(1, '#2563eb');
    ctx.fillStyle = rightWingGradient;
    ctx.strokeStyle = '#1e3a8a';
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.moveTo(18, 0);
    ctx.lineTo(75, -12);
    ctx.lineTo(75, -8);
    ctx.lineTo(65, 12);
    ctx.closePath();
    ctx.fill();
    ctx.stroke();

    // 尾翼
    ctx.fillStyle = '#fbbf24';
    ctx.strokeStyle = '#d97706';
    ctx.beginPath();
    ctx.moveTo(-10, 40);
    ctx.lineTo(10, 40);
    ctx.lineTo(0, 55);
    ctx.closePath();
    ctx.fill();
    ctx.stroke();

    // 垂直尾翼
    ctx.fillStyle = '#f59e0b';
    ctx.beginPath();
    ctx.moveTo(-2, 38);
    ctx.lineTo(2, 38);
    ctx.lineTo(2, 50);
    ctx.lineTo(-2, 50);
    ctx.closePath();
    ctx.fill();

    // 机头
    ctx.fillStyle = '#475569';
    ctx.beginPath();
    ctx.arc(0, -40, 6, 0, Math.PI * 2);
    ctx.fill();

    // 驾驶舱窗户
    ctx.fillStyle = '#60a5fa';
    ctx.beginPath();
    ctx.arc(0, -25, 5, 0, Math.PI * 2);
    ctx.fill();

    ctx.restore();

    // 十字准心
    ctx.strokeStyle = 'rgba(255, 255, 255, 0.9)';
    ctx.lineWidth = 3;
    ctx.beginPath();
    ctx.moveTo(centerX - 40, centerY);
    ctx.lineTo(centerX - 12, centerY);
    ctx.moveTo(centerX + 12, centerY);
    ctx.lineTo(centerX + 40, centerY);
    ctx.moveTo(centerX, centerY - 40);
    ctx.lineTo(centerX, centerY - 12);
    ctx.moveTo(centerX, centerY + 12);
    ctx.lineTo(centerX, centerY + 40);
    ctx.stroke();

    // 数据面板 - 玻璃态效果
    ctx.fillStyle = 'rgba(15, 23, 42, 0.85)';
    ctx.fillRect(10, 10, 160, 105);
    
    // 面板边框
    const borderGradient = ctx.createLinearGradient(10, 10, 170, 115);
    borderGradient.addColorStop(0, '#f59e0b');
    borderGradient.addColorStop(1, '#ef4444');
    ctx.strokeStyle = borderGradient;
    ctx.lineWidth = 2;
    ctx.strokeRect(10, 10, 160, 105);

    const labels = ['ROLL', 'PITCH', 'YAW'];
    const values = [roll, pitch, yaw];
    const colors = ['#ef4444', '#22c55e', '#3b82f6'];
    const icons = ['↔', '↕', '↻'];

    for (let i = 0; i < 3; i++) {
      const y = 35 + i * 28;
      
      // 图标
      ctx.fillStyle = colors[i];
      ctx.font = 'bold 16px Arial';
      ctx.textAlign = 'left';
      ctx.fillText(icons[i], 20, y);
      
      // 标签
      ctx.font = 'bold 12px Arial';
      ctx.fillText(labels[i], 42, y);
      
      // 数值
      ctx.font = 'bold 16px monospace';
      ctx.textAlign = 'right';
      ctx.fillText(values[i].toFixed(1) + '°', 158, y);
      
      // 进度条背景
      ctx.fillStyle = 'rgba(255, 255, 255, 0.1)';
      ctx.fillRect(42, y + 5, 110, 4);
      
      // 进度条
      const percent = Math.abs(values[i]) / 90;
      ctx.fillStyle = colors[i];
      ctx.fillRect(42, y + 5, 110 * Math.min(percent, 1), 4);
    }

    // 状态指示器
    ctx.fillStyle = 'rgba(15, 23, 42, 0.85)';
    ctx.fillRect(width - 80, centerY - 60, 70, 120);
    ctx.strokeStyle = '#22c55e';
    ctx.lineWidth = 2;
    ctx.strokeRect(width - 80, centerY - 60, 70, 120);
    
    ctx.fillStyle = '#22c55e';
    ctx.font = 'bold 18px Arial';
    ctx.textAlign = 'center';
    ctx.fillText('STABLE', width - 45, centerY - 30);
    
    // 状态灯
    const statusGradient = ctx.createRadialGradient(width - 45, centerY, 0, width - 45, centerY, 8);
    statusGradient.addColorStop(0, '#4ade80');
    statusGradient.addColorStop(1, '#22c55e');
    ctx.fillStyle = statusGradient;
    ctx.beginPath();
    ctx.arc(width - 45, centerY, 8, 0, Math.PI * 2);
    ctx.fill();
    
    // 指示文字
    ctx.fillStyle = '#94a3b8';
    ctx.font = '10px Arial';
    ctx.fillText('SYSTEM', width - 45, centerY + 25);
    ctx.fillText('OK', width - 45, centerY + 38);

  }, [roll, pitch, yaw]);

  return (
    <canvas 
      ref={canvasRef} 
      width={400} 
      height={340}
      className="w-full rounded-2xl shadow-lg"
      style={{ maxWidth: '100%', height: 'auto' }}
    />
  );
}

// 加藤惠对话组件
function KateDialog({ message, onDismiss }) {
  return (
    <div className="fixed top-20 left-1/2 transform -translate-x-1/2 z-50 animate-slide-down">
      <div className="bg-white rounded-3xl shadow-2xl p-4 max-w-sm border-2 border-pink-200 relative">
        <div className="absolute -top-2 -left-2 w-8 h-8 bg-pink-400 rounded-full flex items-center justify-center text-white text-xs">
          👧
        </div>
        <div className="flex items-start space-x-3">
          <Sparkles className="text-pink-400 flex-shrink-0 mt-1" size={20} />
          <div className="flex-1">
            <p className="text-sm text-gray-700 leading-relaxed">{message}</p>
          </div>
          <button onClick={onDismiss} className="text-gray-400 hover:text-gray-600">
            ✕
          </button>
        </div>
      </div>
    </div>
  );
}

export default function STM32App() {
  const [activeTab, setActiveTab] = useState(0);
  const [led0, setLed0] = useState(false);
  const [led1, setLed1] = useState(false);
  const [connected, setConnected] = useState(false);
  const [showKateDialog, setShowKateDialog] = useState(true);
  const [kateMessage, setKateMessage] = useState("欢迎回来，今天也要好好工作哦~");
  
  const [logs, setLogs] = useState([
    { time: '10:23:15', type: 'info', message: '系统启动成功' },
    { time: '10:23:18', type: 'success', message: '传感器初始化完成' },
    { time: '10:23:20', type: 'warning', message: '温度传感器数值偏高' },
  ]);

  const [sensorData, setSensorData] = useState({
    temperature: 24.5,
    humidity: 65,
    pressure: 1013.25,
    altitude: 120,
    accelX: 0.12,
    accelY: -0.05,
    accelZ: 9.81,
    gyroX: 0.5,
    gyroY: -0.3,
    gyroZ: 0.1,
    motorSpeed: 1250,
    stepperAngle: 0,
    servoAngle: 90,
    light: 450,
    gasLevel: 120,
    soundLevel: 55,
    gpsLat: 34.0522,
    gpsLng: -118.2437,
    gpsSats: 12
  });

  const [historyData, setHistoryData] = useState([]);

  const kateGreetings = [
    "传感器数据看起来很稳定呢",
    "温度有点高了，要注意散热哦",
    "今天的数据更新很快呢",
    "蓝牙连接很稳定，继续保持~",
    "要不要试试调整电机速度？",
    "MPU6050的姿态数据真有趣",
    "这个GPS定位还挺准确的",
    "光照传感器显示现在很明亮呢"
  ];

  useEffect(() => {
    const interval = setInterval(() => {
      setSensorData(prev => ({
        ...prev,
        temperature: 24 + Math.random() * 2,
        humidity: 64 + Math.random() * 6,
        pressure: 1013 + Math.random() * 0.5,
        altitude: 118 + Math.random() * 4,
        accelX: -0.2 + Math.random() * 0.4,
        accelY: -0.2 + Math.random() * 0.4,
        accelZ: 9.7 + Math.random() * 0.2,
        gyroX: -1 + Math.random() * 2,
        gyroY: -1 + Math.random() * 2,
        gyroZ: -1 + Math.random() * 2,
        motorSpeed: 1200 + Math.random() * 200,
        light: 400 + Math.random() * 100,
        gasLevel: 100 + Math.random() * 60,
        soundLevel: 50 + Math.random() * 20
      }));
    }, 2000);

    return () => clearInterval(interval);
  }, []);

  useEffect(() => {
    setHistoryData(prev => {
      const newData = [...prev, {
        time: new Date().toLocaleTimeString('zh-CN', { hour: '2-digit', minute: '2-digit' }),
        temperature: sensorData.temperature,
        humidity: sensorData.humidity,
        pressure: sensorData.pressure,
        motorSpeed: sensorData.motorSpeed
      }];
      return newData.slice(-15);
    });
  }, [sensorData]);

  useEffect(() => {
    const kateInterval = setInterval(() => {
      if (Math.random() > 0.3) {
        const newMessage = kateGreetings[Math.floor(Math.random() * kateGreetings.length)];
        setKateMessage(newMessage);
        setShowKateDialog(true);
        setTimeout(() => setShowKateDialog(false), 5000);
      }
    }, 30000);

    return () => clearInterval(kateInterval);
  }, []);

  const bluetoothDevices = [
    { name: 'STM32_Main_001', signal: -45, id: '1' },
    { name: 'STM32_Sensor_002', signal: -62, id: '2' },
    { name: 'HC-05_Module', signal: -78, id: '3' }
  ];

  const radarData = [
    { subject: '温度', value: (sensorData.temperature / 35) * 100 },
    { subject: '湿度', value: sensorData.humidity },
    { subject: '气压', value: ((sensorData.pressure - 1000) / 30) * 100 },
    { subject: '光照', value: (sensorData.light / 1000) * 100 },
    { subject: '声音', value: (sensorData.soundLevel / 100) * 100 }
  ];

  return (
    <div className="h-screen flex flex-col bg-gradient-to-br from-slate-50 to-blue-50">
      {showKateDialog && (
        <KateDialog 
          message={kateMessage} 
          onDismiss={() => setShowKateDialog(false)} 
        />
      )}

      <div className="flex-1 overflow-hidden">
        {activeTab === 0 && (
          <div className="h-full overflow-y-auto pb-20">
            {/* 加藤惠卡片 */}
            <div className="bg-gradient-to-br from-pink-400 via-purple-400 to-indigo-400 m-4 rounded-3xl shadow-2xl overflow-hidden">
              <div className="p-6">
                <div className="flex items-start space-x-4">
                  <div className="relative">
                    <div className="w-24 h-24 bg-white rounded-full flex items-center justify-center border-4 border-white shadow-xl">
                      <div className="text-5xl">👧</div>
                    </div>
                    <div className="absolute -bottom-1 -right-1 w-8 h-8 bg-green-400 rounded-full border-4 border-white flex items-center justify-center">
                      <Heart className="text-white" size={14} fill="white" />
                    </div>
                  </div>
                  <div className="flex-1">
                    <h2 className="text-white font-bold text-2xl mb-1">加藤 惠</h2>
                    <p className="text-pink-100 text-sm mb-2">AI 智能助手 · STM32 监控系统</p>
                    <div className="flex space-x-2">
                      <div className={`px-3 py-1 rounded-full ${connected ? 'bg-green-400' : 'bg-gray-400'} text-white text-xs font-bold flex items-center space-x-1`}>
                        <div className={`w-2 h-2 rounded-full ${connected ? 'bg-white animate-pulse' : 'bg-gray-200'}`}></div>
                        <span>{connected ? '在线' : '离线'}</span>
                      </div>
                      <div className="px-3 py-1 rounded-full bg-white/30 text-white text-xs font-bold">
                        活跃中
                      </div>
                    </div>
                  </div>
                </div>
              </div>
              
              <div className="bg-white/95 backdrop-blur-sm p-5 rounded-t-3xl">
                <div className="flex items-start space-x-3 bg-gradient-to-r from-pink-50 to-purple-50 rounded-2xl p-4 border-2 border-pink-200">
                  <MessageCircle className="text-pink-400 flex-shrink-0 mt-1" size={20} />
                  <div className="flex-1">
                    <p className="text-gray-700 text-sm leading-relaxed">
                      💭 {kateMessage}
                    </p>
                  </div>
                  <Sparkles className="text-purple-400" size={16} />
                </div>
                
                <button 
                  onClick={() => {
                    const newMsg = kateGreetings[Math.floor(Math.random() * kateGreetings.length)];
                    setKateMessage(newMsg);
                  }}
                  className="mt-3 w-full bg-gradient-to-r from-pink-500 to-purple-500 text-white py-3 rounded-xl text-sm font-medium hover:shadow-lg transition-all transform hover:scale-105 flex items-center justify-center space-x-2"
                >
                  <Sparkles size={16} />
                  <span>换个话题聊聊</span>
                </button>
              </div>
            </div>

            {/* 快速状态卡片 */}
            <div className="mx-4 mb-4 grid grid-cols-2 gap-3">
              <div className="bg-gradient-to-br from-blue-500 to-cyan-500 rounded-2xl p-4 text-white shadow-lg">
                <ThermometerSun className="mb-2" size={24} />
                <p className="text-2xl font-bold">{sensorData.temperature.toFixed(1)}°C</p>
                <p className="text-xs opacity-80">环境温度</p>
              </div>
              <div className="bg-gradient-to-br from-green-500 to-emerald-500 rounded-2xl p-4 text-white shadow-lg">
                <Droplets className="mb-2" size={24} />
                <p className="text-2xl font-bold">{sensorData.humidity.toFixed(0)}%</p>
                <p className="text-xs opacity-80">空气湿度</p>
              </div>
              <div className="bg-gradient-to-br from-orange-500 to-red-500 rounded-2xl p-4 text-white shadow-lg">
                <Zap className="mb-2" size={24} />
                <p className="text-2xl font-bold">{sensorData.motorSpeed}</p>
                <p className="text-xs opacity-80">电机转速 RPM</p>
              </div>
              <div className="bg-gradient-to-br from-purple-500 to-pink-500 rounded-2xl p-4 text-white shadow-lg">
                <Camera className="mb-2" size={24} />
                <p className="text-2xl font-bold">{sensorData.light}</p>
                <p className="text-xs opacity-80">光照强度 lux</p>
              </div>
            </div>

            {/* 蓝牙设备列表 */}
            <div className="mx-4 mb-4">
              <div className="flex items-center justify-between mb-3">
                <h3 className="text-lg font-bold text-gray-800 flex items-center">
                  <Bluetooth className="mr-2 text-blue-500" size={24} />
                  附近的蓝牙设备
                </h3>
                <button className="bg-gradient-to-r from-blue-500 to-cyan-500 text-white px-4 py-2 rounded-full text-sm hover:shadow-lg transition-all transform hover:scale-105 flex items-center space-x-1">
                  <Wifi size={14} />
                  <span>扫描</span>
                </button>
              </div>

              <div className="space-y-3">
                {bluetoothDevices.map(device => (
                  <div key={device.id} className="bg-white rounded-2xl p-4 shadow-lg hover:shadow-xl transition-all border border-gray-100">
                    <div className="flex items-center justify-between">
                      <div className="flex-1">
                        <div className="flex items-center space-x-2 mb-2">
                          <Wifi className="text-blue-500" size={20} />
                          <span className="font-semibold text-gray-800">{device.name}</span>
                        </div>
                        <div className="flex items-center space-x-2">
                          <div className="flex-1 bg-gray-200 rounded-full h-2 overflow-hidden">
                            <div 
                              className={`h-full rounded-full transition-all ${
                                device.signal > -50 ? 'bg-gradient-to-r from-green-400 to-green-500' : 
                                device.signal > -70 ? 'bg-gradient-to-r from-yellow-400 to-yellow-500' : 
                                'bg-gradient-to-r from-red-400 to-red-500'
                              }`}
                              style={{ width: `${Math.max(0, 100 + device.signal)}%` }}
                            />
                          </div>
                          <span className="text-xs text-gray-500 font-mono">{device.signal} dBm</span>
                        </div>
                      </div>
                      <button 
                        onClick={() => {
                          setConnected(!connected);
                          setShowKateDialog(true);
                          setKateMessage(connected ? "断开连接了，需要帮忙吗？" : "连接成功！一切准备就绪~");
                        }}
                        className="ml-4 bg-gradient-to-r from-blue-500 to-purple-500 text-white px-6 py-2 rounded-xl font-medium hover:shadow-lg transition-all transform hover:scale-105"
                      >
                        {connected ? '断开' : '连接'}
                      </button>
                    </div>
                  </div>
                ))}
              </div>
            </div>

            {!connected && (
              <div className="mx-4 mb-4 bg-gradient-to-r from-yellow-50 to-orange-50 border-2 border-yellow-300 rounded-2xl p-4 shadow-lg">
                <div className="flex items-start space-x-3">
                  <Zap className="text-yellow-500 flex-shrink-0" size={24} />
                  <div>
                    <p className="font-semibold text-yellow-800 mb-1">未连接到设备</p>
                    <p className="text-sm text-yellow-700">请选择一个蓝牙设备进行连接，加藤惠在等你哦~</p>
                  </div>
                </div>
              </div>
            )}
          </div>
        )}

        {activeTab === 1 && (
          <div className="h-full overflow-y-auto pb-20 bg-gradient-to-br from-blue-50 via-indigo-50 to-purple-50">
            <div className="p-4 space-y-4">
              {/* LED控制 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-blue-200">
                <div className="flex items-center justify-between mb-5">
                  <h3 className="text-xl font-bold text-gray-800 flex items-center">
                    <Lightbulb className="mr-2 text-yellow-500" size={28} />
                    LED 灯光控制
                  </h3>
                  <div className="flex items-center space-x-2">
                    <div className="w-3 h-3 bg-green-500 rounded-full animate-pulse"></div>
                    <span className="text-xs text-gray-500">实时控制</span>
                  </div>
                </div>

                <div className="grid grid-cols-2 gap-4">
                  <button
                    onClick={() => setLed0(!led0)}
                    className={`p-8 rounded-3xl transition-all transform hover:scale-105 ${
                      led0 
                        ? 'bg-gradient-to-br from-yellow-400 via-orange-400 to-red-500 shadow-2xl shadow-yellow-400/50' 
                        : 'bg-gradient-to-br from-gray-100 to-gray-200 hover:from-gray-200 hover:to-gray-300'
                    }`}
                  >
                    <div className="flex flex-col items-center space-y-3">
                      {led0 ? <Lightbulb className="text-white drop-shadow-lg" size={40} /> : <LightbulbOff className="text-gray-400" size={40} />}
                      <span className={`font-bold text-lg ${led0 ? 'text-white' : 'text-gray-600'}`}>LED 0</span>
                      <div className={`px-4 py-1 rounded-full text-sm font-bold ${led0 ? 'bg-white/30 text-white' : 'bg-gray-300 text-gray-600'}`}>
                        {led0 ? 'ON' : 'OFF'}
                      </div>
                    </div>
                  </button>

                  <button
                    onClick={() => setLed1(!led1)}
                    className={`p-8 rounded-3xl transition-all transform hover:scale-105 ${
                      led1 
                        ? 'bg-gradient-to-br from-green-400 via-emerald-400 to-teal-500 shadow-2xl shadow-green-400/50' 
                        : 'bg-gradient-to-br from-gray-100 to-gray-200 hover:from-gray-200 hover:to-gray-300'
                    }`}
                  >
                    <div className="flex flex-col items-center space-y-3">
                      {led1 ? <Lightbulb className="text-white drop-shadow-lg" size={40} /> : <LightbulbOff className="text-gray-400" size={40} />}
                      <span className={`font-bold text-lg ${led1 ? 'text-white' : 'text-gray-600'}`}>LED 1</span>
                      <div className={`px-4 py-1 rounded-full text-sm font-bold ${led1 ? 'bg-white/30 text-white' : 'bg-gray-300 text-gray-600'}`}>
                        {led1 ? 'ON' : 'OFF'}
                      </div>
                    </div>
                  </button>
                </div>
              </div>

              {/* 环境传感器 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-purple-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <ThermometerSun className="mr-2 text-purple-500" size={24} />
                  环境监测 (SHT30 + BMP280)
                </h3>
                <div className="grid grid-cols-2 gap-3">
                  <div className="bg-gradient-to-br from-red-50 to-orange-50 p-5 rounded-2xl border-2 border-red-200">
                    <div className="flex items-center justify-between mb-3">
                      <span className="text-sm font-medium text-gray-600">温度</span>
                      <ThermometerSun className="text-red-500" size={22} />
                    </div>
                    <p className="text-4xl font-bold text-red-600 mb-1">{sensorData.temperature.toFixed(1)}</p>
                    <p className="text-sm text-gray-500">摄氏度 °C</p>
                    <div className="mt-3 bg-white rounded-lg h-2 overflow-hidden">
                      <div className="bg-gradient-to-r from-red-400 to-red-600 h-full transition-all" style={{width: `${(sensorData.temperature / 40) * 100}%`}}></div>
                    </div>
                  </div>
                  
                  <div className="bg-gradient-to-br from-blue-50 to-cyan-50 p-5 rounded-2xl border-2 border-blue-200">
                    <div className="flex items-center justify-between mb-3">
                      <span className="text-sm font-medium text-gray-600">湿度</span>
                      <Droplets className="text-blue-500" size={22} />
                    </div>
                    <p className="text-4xl font-bold text-blue-600 mb-1">{sensorData.humidity.toFixed(0)}</p>
                    <p className="text-sm text-gray-500">相对湿度 %</p>
                    <div className="mt-3 bg-white rounded-lg h-2 overflow-hidden">
                      <div className="bg-gradient-to-r from-blue-400 to-blue-600 h-full transition-all" style={{width: `${sensorData.humidity}%`}}></div>
                    </div>
                  </div>

                  <div className="bg-gradient-to-br from-green-50 to-emerald-50 p-5 rounded-2xl border-2 border-green-200">
                    <div className="flex items-center justify-between mb-3">
                      <span className="text-sm font-medium text-gray-600">气压</span>
                      <Gauge className="text-green-500" size={22} />
                    </div>
                    <p className="text-3xl font-bold text-green-600 mb-1">{sensorData.pressure.toFixed(1)}</p>
                    <p className="text-sm text-gray-500">百帕 hPa</p>
                    <div className="mt-3 bg-white rounded-lg h-2 overflow-hidden">
                      <div className="bg-gradient-to-r from-green-400 to-green-600 h-full transition-all" style={{width: '75%'}}></div>
                    </div>
                  </div>

                  <div className="bg-gradient-to-br from-purple-50 to-pink-50 p-5 rounded-2xl border-2 border-purple-200">
                    <div className="flex items-center justify-between mb-3">
                      <span className="text-sm font-medium text-gray-600">海拔</span>
                      <Navigation className="text-purple-500" size={22} />
                    </div>
                    <p className="text-3xl font-bold text-purple-600 mb-1">{sensorData.altitude}</p>
                    <p className="text-sm text-gray-500">米 m</p>
                    <div className="mt-3 bg-white rounded-lg h-2 overflow-hidden">
                      <div className="bg-gradient-to-r from-purple-400 to-purple-600 h-full transition-all" style={{width: '60%'}}></div>
                    </div>
                  </div>
                </div>
              </div>

              {/* 3D姿态 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-indigo-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <Compass className="mr-2 text-indigo-500" size={24} />
                  飞行姿态 3D 可视化 (MPU6050)
                </h3>
                <div className="bg-gradient-to-br from-sky-50 to-blue-100 rounded-2xl p-3 border-2 border-indigo-100">
                  <Cube3D 
                    roll={sensorData.gyroX * 25} 
                    pitch={sensorData.gyroY * 25} 
                    yaw={sensorData.gyroZ * 25} 
                  />
                </div>
                <div className="mt-5 grid grid-cols-2 gap-3">
                  <div className="bg-gradient-to-br from-indigo-50 to-blue-50 p-4 rounded-xl border border-indigo-200">
                    <div className="flex items-center justify-between mb-2">
                      <p className="text-xs font-medium text-gray-600">加速度 (m/s²)</p>
                      <Activity className="text-indigo-500" size={16} />
                    </div>
                    <div className="space-y-2 text-sm">
                      <div className="flex justify-between items-center">
                        <span className="text-gray-500">X轴:</span>
                        <span className="font-mono text-indigo-600 font-bold bg-white px-2 py-0.5 rounded">{sensorData.accelX.toFixed(3)}</span>
                      </div>
                      <div className="flex justify-between items-center">
                        <span className="text-gray-500">Y轴:</span>
                        <span className="font-mono text-indigo-600 font-bold bg-white px-2 py-0.5 rounded">{sensorData.accelY.toFixed(3)}</span>
                      </div>
                      <div className="flex justify-between items-center">
                        <span className="text-gray-500">Z轴:</span>
                        <span className="font-mono text-indigo-600 font-bold bg-white px-2 py-0.5 rounded">{sensorData.accelZ.toFixed(2)}</span>
                      </div>
                    </div>
                  </div>
                  
                  <div className="bg-gradient-to-br from-pink-50 to-rose-50 p-4 rounded-xl border border-pink-200">
                    <div className="flex items-center justify-between mb-2">
                      <p className="text-xs font-medium text-gray-600">角速度 (°/s)</p>
                      <Compass className="text-pink-500" size={16} />
                    </div>
                    <div className="space-y-2 text-sm">
                      <div className="flex justify-between items-center">
                        <span className="text-gray-500">X轴:</span>
                        <span className="font-mono text-pink-600 font-bold bg-white px-2 py-0.5 rounded">{sensorData.gyroX.toFixed(3)}</span>
                      </div>
                      <div className="flex justify-between items-center">
                        <span className="text-gray-500">Y轴:</span>
                        <span className="font-mono text-pink-600 font-bold bg-white px-2 py-0.5 rounded">{sensorData.gyroY.toFixed(3)}</span>
                      </div>
                      <div className="flex justify-between items-center">
                        <span className="text-gray-500">Z轴:</span>
                        <span className="font-mono text-pink-600 font-bold bg-white px-2 py-0.5 rounded">{sensorData.gyroZ.toFixed(3)}</span>
                      </div>
                    </div>
                  </div>
                </div>
              </div>

              {/* 电机控制 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-orange-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <Zap className="mr-2 text-orange-500" size={24} />
                  电机控制系统
                </h3>
                
                {/* N20编码电机 */}
                <div className="bg-gradient-to-br from-orange-50 to-red-50 p-5 rounded-2xl border-2 border-orange-200 mb-4">
                  <div className="flex items-center justify-between mb-3">
                    <span className="font-semibold text-gray-800">N20 编码电机</span>
                    <div className="flex items-center space-x-1">
                      <div className="w-2 h-2 bg-green-500 rounded-full animate-pulse"></div>
                      <span className="text-xs text-gray-500">运行中</span>
                    </div>
                  </div>
                  <div className="text-center mb-4">
                    <p className="text-5xl font-bold text-orange-600">{sensorData.motorSpeed.toFixed(0)}</p>
                    <p className="text-sm text-gray-600 mt-1">转/分钟 (RPM)</p>
                  </div>
                  <div className="bg-white rounded-xl p-3">
                    <div className="flex justify-between items-center space-x-2">
                      <button className="flex-1 bg-gradient-to-r from-red-500 to-red-600 text-white px-4 py-3 rounded-lg hover:shadow-lg transition-all transform hover:scale-105 font-medium">
                        停止
                      </button>
                      <button className="flex-1 bg-gradient-to-r from-green-500 to-green-600 text-white px-4 py-3 rounded-lg hover:shadow-lg transition-all transform hover:scale-105 font-medium">
                        启动
                      </button>
                      <button className="flex-1 bg-gradient-to-r from-blue-500 to-blue-600 text-white px-4 py-3 rounded-lg hover:shadow-lg transition-all transform hover:scale-105 font-medium">
                        反转
                      </button>
                    </div>
                  </div>
                </div>

                {/* 步进电机与舵机 */}
                <div className="grid grid-cols-2 gap-3">
                  <div className="bg-gradient-to-br from-cyan-50 to-blue-50 p-4 rounded-xl border border-cyan-200">
                    <p className="text-sm font-semibold text-gray-700 mb-2">28BYJ-48 步进电机</p>
                    <p className="text-3xl font-bold text-cyan-600">{sensorData.stepperAngle}°</p>
                    <p className="text-xs text-gray-500 mt-1">当前角度</p>
                    <button className="mt-3 w-full bg-cyan-500 text-white py-2 rounded-lg text-sm hover:bg-cyan-600 transition">
                      控制
                    </button>
                  </div>
                  
                  <div className="bg-gradient-to-br from-purple-50 to-pink-50 p-4 rounded-xl border border-purple-200">
                    <p className="text-sm font-semibold text-gray-700 mb-2">FPV 舵机云台</p>
                    <p className="text-3xl font-bold text-purple-600">{sensorData.servoAngle}°</p>
                    <p className="text-xs text-gray-500 mt-1">俯仰角度</p>
                    <button className="mt-3 w-full bg-purple-500 text-white py-2 rounded-lg text-sm hover:bg-purple-600 transition">
                      调节
                    </button>
                  </div>
                </div>
              </div>

              {/* 扩展模块 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-teal-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <Activity className="mr-2 text-teal-500" size={24} />
                  扩展传感器模块
                </h3>
                <div className="grid grid-cols-2 gap-3">
                  <div className="bg-gradient-to-br from-yellow-50 to-orange-50 p-4 rounded-xl border-2 border-yellow-200">
                    <div className="flex items-center justify-between mb-2">
                      <Camera className="text-yellow-600" size={24} />
                      <span className="text-xs bg-yellow-200 text-yellow-800 px-2 py-1 rounded-full font-bold">BH1750</span>
                    </div>
                    <p className="text-3xl font-bold text-yellow-700">{sensorData.light.toFixed(0)}</p>
                    <p className="text-xs text-gray-600 mt-1">lux - 光照强度</p>
                    <div className="mt-3 bg-white rounded-lg h-2 overflow-hidden">
                      <div className="bg-gradient-to-r from-yellow-400 to-orange-500 h-full transition-all" style={{width: `${(sensorData.light / 1000) * 100}%`}}></div>
                    </div>
                  </div>

                  <div className="bg-gradient-to-br from-red-50 to-pink-50 p-4 rounded-xl border-2 border-red-200">
                    <div className="flex items-center justify-between mb-2">
                      <Flame className="text-red-600" size={24} />
                      <span className="text-xs bg-red-200 text-red-800 px-2 py-1 rounded-full font-bold">MQ-2</span>
                    </div>
                    <p className="text-3xl font-bold text-red-700">{sensorData.gasLevel.toFixed(0)}</p>
                    <p className="text-xs text-gray-600 mt-1">ppm - 气体浓度</p>
                    <div className="mt-3 bg-white rounded-lg h-2 overflow-hidden">
                      <div className="bg-gradient-to-r from-red-400 to-pink-500 h-full transition-all" style={{width: `${(sensorData.gasLevel / 500) * 100}%`}}></div>
                    </div>
                  </div>

                  <div className="bg-gradient-to-br from-purple-50 to-indigo-50 p-4 rounded-xl border-2 border-purple-200">
                    <div className="flex items-center justify-between mb-2">
                      <Volume2 className="text-purple-600" size={24} />
                      <span className="text-xs bg-purple-200 text-purple-800 px-2 py-1 rounded-full font-bold">INMP441</span>
                    </div>
                    <p className="text-3xl font-bold text-purple-700">{sensorData.soundLevel.toFixed(0)}</p>
                    <p className="text-xs text-gray-600 mt-1">dB - 声音分贝</p>
                    <div className="mt-3 bg-white rounded-lg h-2 overflow-hidden">
                      <div className="bg-gradient-to-r from-purple-400 to-indigo-500 h-full transition-all" style={{width: `${(sensorData.soundLevel / 100) * 100}%`}}></div>
                    </div>
                  </div>

                  <div className="bg-gradient-to-br from-blue-50 to-cyan-50 p-4 rounded-xl border-2 border-blue-200">
                    <div className="flex items-center justify-between mb-2">
                      <Database className="text-blue-600" size={24} />
                      <span className="text-xs bg-blue-200 text-blue-800 px-2 py-1 rounded-full font-bold">存储</span>
                    </div>
                    <p className="text-2xl font-bold text-blue-700">W25Q128</p>
                    <p className="text-xs text-gray-600 mt-1">Flash Memory</p>
                    <div className="mt-3 flex items-center space-x-2">
                      <div className="w-2 h-2 bg-green-500 rounded-full"></div>
                      <span className="text-xs text-gray-500">已就绪 · AT24C256</span>
                    </div>
                  </div>
                </div>
              </div>

              {/* GPS定位 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-green-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <MapPin className="mr-2 text-green-500" size={24} />
                  GPS 定位信息
                </h3>
                <div className="bg-gradient-to-br from-green-50 to-emerald-50 p-5 rounded-2xl border-2 border-green-200">
                  <div className="grid grid-cols-2 gap-4 mb-4">
                    <div>
                      <p className="text-xs text-gray-500 mb-1">纬度</p>
                      <p className="text-lg font-mono font-bold text-green-600">{sensorData.gpsLat.toFixed(6)}°</p>
                    </div>
                    <div>
                      <p className="text-xs text-gray-500 mb-1">经度</p>
                      <p className="text-lg font-mono font-bold text-green-600">{sensorData.gpsLng.toFixed(6)}°</p>
                    </div>
                  </div>
                  <div className="flex items-center justify-between bg-white rounded-xl p-3">
                    <div className="flex items-center space-x-2">
                      <div className="w-3 h-3 bg-green-500 rounded-full animate-pulse"></div>
                      <span className="text-sm font-medium text-gray-700">已定位</span>
                    </div>
                    <span className="text-sm text-gray-600">{sensorData.gpsSats} 颗卫星</span>
                  </div>
                </div>
              </div>
            </div>
          </div>
        )}

        {activeTab === 2 && (
          <div className="h-full overflow-y-auto pb-20 bg-gradient-to-br from-purple-50 via-pink-50 to-rose-50">
            <div className="p-4 space-y-4">
              {/* 标题卡片 */}
              <div className="bg-gradient-to-r from-purple-600 via-pink-500 to-rose-500 rounded-3xl shadow-2xl p-6 text-white">
                <div className="flex items-center justify-between">
                  <div>
                    <h2 className="text-2xl font-bold mb-1">📊 实时数据监控</h2>
                    <p className="text-purple-100 text-sm">Data Visualization Dashboard</p>
                  </div>
                  <TrendingUp size={48} className="opacity-70" />
                </div>
              </div>

              {/* 雷达图 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-purple-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <BarChart3 className="mr-2 text-purple-500" size={24} />
                  传感器综合状态
                </h3>
                <div className="h-72">
                  <ResponsiveContainer width="100%" height="100%">
                    <RadarChart data={radarData}>
                      <PolarGrid stroke="#e5e7eb" />
                      <PolarAngleAxis dataKey="subject" tick={{fontSize: 12, fill: '#6b7280'}} />
                      <PolarRadiusAxis angle={90} domain={[0, 100]} tick={{fontSize: 10}} />
                      <Radar name="传感器" dataKey="value" stroke="#a855f7" fill="#a855f7" fillOpacity={0.6} />
                    </RadarChart>
                  </ResponsiveContainer>
                </div>
              </div>

              {/* 温湿度趋势 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-red-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <ThermometerSun className="mr-2 text-red-500" size={24} />
                  温湿度变化趋势
                </h3>
                <div className="h-64">
                  <ResponsiveContainer width="100%" height="100%">
                    <RechartsLine data={historyData}>
                      <CartesianGrid strokeDasharray="3 3" stroke="#f0f0f0" />
                      <XAxis dataKey="time" tick={{fontSize: 10}} stroke="#9ca3af" />
                      <YAxis yAxisId="left" tick={{fontSize: 10}} stroke="#ef4444" />
                      <YAxis yAxisId="right" orientation="right" tick={{fontSize: 10}} stroke="#3b82f6" />
                      <Tooltip 
                        contentStyle={{background: '#fff', border: '2px solid #e5e7eb', borderRadius: '12px'}}
                        labelStyle={{fontWeight: 'bold', color: '#374151'}}
                      />
                      <Line yAxisId="left" type="monotone" dataKey="temperature" stroke="#ef4444" strokeWidth={3} dot={{fill: '#ef4444', r: 4}} name="温度 °C" />
                      <Line yAxisId="right" type="monotone" dataKey="humidity" stroke="#3b82f6" strokeWidth={3} dot={{fill: '#3b82f6', r: 4}} name="湿度 %" />
                    </RechartsLine>
                  </ResponsiveContainer>
                </div>
                <div className="grid grid-cols-2 gap-3 mt-5">
                  <div className="text-center bg-gradient-to-br from-red-50 to-orange-50 rounded-2xl p-4 border border-red-200">
                    <ThermometerSun className="mx-auto mb-2 text-red-500" size={24} />
                    <p className="text-3xl font-bold text-red-600">{sensorData.temperature.toFixed(1)}°C</p>
                    <p className="text-xs text-gray-500 mt-1">当前温度</p>
                  </div>
                  <div className="text-center bg-gradient-to-br from-blue-50 to-cyan-50 rounded-2xl p-4 border border-blue-200">
                    <Droplets className="mx-auto mb-2 text-blue-500" size={24} />
                    <p className="text-3xl font-bold text-blue-600">{sensorData.humidity.toFixed(0)}%</p>
                    <p className="text-xs text-gray-500 mt-1">当前湿度</p>
                  </div>
                </div>
              </div>

              {/* 气压海拔趋势 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-green-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <Wind className="mr-2 text-green-500" size={24} />
                  气压监测曲线
                </h3>
                <div className="h-64">
                  <ResponsiveContainer width="100%" height="100%">
                    <AreaChart data={historyData}>
                      <defs>
                        <linearGradient id="colorPressure" x1="0" y1="0" x2="0" y2="1">
                          <stop offset="5%" stopColor="#22c55e" stopOpacity={0.8}/>
                          <stop offset="95%" stopColor="#22c55e" stopOpacity={0.1}/>
                        </linearGradient>
                      </defs>
                      <CartesianGrid strokeDasharray="3 3" stroke="#f0f0f0" />
                      <XAxis dataKey="time" tick={{fontSize: 10}} stroke="#9ca3af" />
                      <YAxis tick={{fontSize: 10}} stroke="#22c55e" domain={['dataMin - 1', 'dataMax + 1']} />
                      <Tooltip 
                        contentStyle={{background: '#fff', border: '2px solid #e5e7eb', borderRadius: '12px'}}
                      />
                      <Area type="monotone" dataKey="pressure" stroke="#22c55e" strokeWidth={3} fillOpacity={1} fill="url(#colorPressure)" name="气压 hPa" />
                    </AreaChart>
                  </ResponsiveContainer>
                </div>
                <div className="mt-5 bg-gradient-to-br from-green-50 to-emerald-50 rounded-2xl p-4 border border-green-200">
                  <div className="grid grid-cols-2 gap-4">
                    <div className="text-center">
                      <Gauge className="mx-auto mb-2 text-green-500" size={24} />
                      <p className="text-2xl font-bold text-green-600">{sensorData.pressure.toFixed(2)}</p>
                      <p className="text-xs text-gray-500 mt-1">气压 (hPa)</p>
                    </div>
                    <div className="text-center">
                      <Navigation className="mx-auto mb-2 text-purple-500" size={24} />
                      <p className="text-2xl font-bold text-purple-600">{sensorData.altitude} m</p>
                      <p className="text-xs text-gray-500 mt-1">海拔高度</p>
                    </div>
                  </div>
                </div>
              </div>

              {/* 电机转速监控 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-orange-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <Zap className="mr-2 text-orange-500" size={24} />
                  电机转速实时曲线
                </h3>
                <div className="h-64">
                  <ResponsiveContainer width="100%" height="100%">
                    <RechartsLine data={historyData}>
                      <CartesianGrid strokeDasharray="3 3" stroke="#f0f0f0" />
                      <XAxis dataKey="time" tick={{fontSize: 10}} stroke="#9ca3af" />
                      <YAxis tick={{fontSize: 10}} stroke="#f97316" domain={['dataMin - 100', 'dataMax + 100']} />
                      <Tooltip 
                        contentStyle={{background: '#fff', border: '2px solid #e5e7eb', borderRadius: '12px'}}
                      />
                      <Line type="monotone" dataKey="motorSpeed" stroke="#f97316" strokeWidth={4} dot={{fill: '#f97316', r: 5}} name="转速 RPM" />
                    </RechartsLine>
                  </ResponsiveContainer>
                </div>
                <div className="mt-5 bg-gradient-to-br from-orange-50 to-red-50 rounded-2xl p-5 border border-orange-200 text-center">
                  <Zap className="mx-auto mb-2 text-orange-500" size={32} />
                  <p className="text-5xl font-bold text-orange-600">{sensorData.motorSpeed.toFixed(0)}</p>
                  <p className="text-sm text-gray-600 mt-2">当前转速 (RPM)</p>
                  <div className="mt-3 flex justify-center space-x-2">
                    <div className="w-2 h-2 bg-green-500 rounded-full animate-pulse"></div>
                    <span className="text-xs text-gray-500">运行中</span>
                  </div>
                </div>
              </div>

              {/* 扩展传感器实时数据 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-teal-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <Radio className="mr-2 text-teal-500" size={24} />
                  扩展传感器实时监控
                </h3>
                <div className="grid grid-cols-2 gap-4">
                  <div className="bg-gradient-to-br from-yellow-50 to-orange-50 p-5 rounded-2xl border-2 border-yellow-200">
                    <div className="flex items-center justify-between mb-3">
                      <Camera className="text-yellow-600" size={28} />
                      <span className="text-xs bg-yellow-200 text-yellow-800 px-3 py-1 rounded-full font-bold">光照</span>
                    </div>
                    <p className="text-4xl font-bold text-yellow-700 mb-1">{sensorData.light.toFixed(0)}</p>
                    <p className="text-xs text-gray-600 mb-3">lux (BH1750)</p>
                    <div className="bg-white rounded-xl h-3 overflow-hidden shadow-inner">
                      <div className="bg-gradient-to-r from-yellow-400 via-orange-400 to-red-500 h-full transition-all" style={{width: `${(sensorData.light / 1000) * 100}%`}}></div>
                    </div>
                    <p className="text-xs text-gray-500 mt-2 text-center">{((sensorData.light / 1000) * 100).toFixed(0)}%</p>
                  </div>

                  <div className="bg-gradient-to-br from-red-50 to-pink-50 p-5 rounded-2xl border-2 border-red-200">
                    <div className="flex items-center justify-between mb-3">
                      <Flame className="text-red-600" size={28} />
                      <span className="text-xs bg-red-200 text-red-800 px-3 py-1 rounded-full font-bold">气体</span>
                    </div>
                    <p className="text-4xl font-bold text-red-700 mb-1">{sensorData.gasLevel.toFixed(0)}</p>
                    <p className="text-xs text-gray-600 mb-3">ppm (MQ-2)</p>
                    <div className="bg-white rounded-xl h-3 overflow-hidden shadow-inner">
                      <div className="bg-gradient-to-r from-red-400 via-rose-400 to-pink-500 h-full transition-all" style={{width: `${(sensorData.gasLevel / 500) * 100}%`}}></div>
                    </div>
                    <p className="text-xs text-gray-500 mt-2 text-center">{((sensorData.gasLevel / 500) * 100).toFixed(0)}%</p>
                  </div>

                  <div className="bg-gradient-to-br from-purple-50 to-indigo-50 p-5 rounded-2xl border-2 border-purple-200">
                    <div className="flex items-center justify-between mb-3">
                      <Volume2 className="text-purple-600" size={28} />
                      <span className="text-xs bg-purple-200 text-purple-800 px-3 py-1 rounded-full font-bold">声音</span>
                    </div>
                    <p className="text-4xl font-bold text-purple-700 mb-1">{sensorData.soundLevel.toFixed(0)}</p>
                    <p className="text-xs text-gray-600 mb-3">dB (INMP441)</p>
                    <div className="bg-white rounded-xl h-3 overflow-hidden shadow-inner">
                      <div className="bg-gradient-to-r from-purple-400 via-violet-400 to-indigo-500 h-full transition-all" style={{width: `${(sensorData.soundLevel / 100) * 100}%`}}></div>
                    </div>
                    <p className="text-xs text-gray-500 mt-2 text-center">{((sensorData.soundLevel / 100) * 100).toFixed(0)}%</p>
                  </div>

                  <div className="bg-gradient-to-br from-blue-50 to-cyan-50 p-5 rounded-2xl border-2 border-blue-200">
                    <div className="flex items-center justify-between mb-3">
                      <Database className="text-blue-600" size={28} />
                      <span className="text-xs bg-blue-200 text-blue-800 px-3 py-1 rounded-full font-bold">存储</span>
                    </div>
                    <p className="text-2xl font-bold text-blue-700 mb-1">W25Q128</p>
                    <p className="text-xs text-gray-600 mb-3">Flash Memory</p>
                    <div className="flex items-center justify-between mt-3">
                      <div className="flex items-center space-x-2">
                        <div className="w-3 h-3 bg-green-500 rounded-full"></div>
                        <span className="text-xs text-gray-500">就绪</span>
                      </div>
                      <span className="text-xs font-mono text-blue-600">128 Mb</span>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
        )}

        {activeTab === 3 && (
          <div className="h-full overflow-y-auto pb-20 bg-gradient-to-br from-slate-50 via-gray-50 to-zinc-100">
            <div className="p-4 space-y-4">
              {/* 标题卡片 */}
              <div className="bg-gradient-to-r from-slate-700 via-gray-800 to-zinc-900 rounded-3xl shadow-2xl p-6 text-white">
                <div className="flex items-center justify-between">
                  <div>
                    <h2 className="text-2xl font-bold mb-1">📝 系统日志</h2>
                    <p className="text-slate-300 text-sm">System Activity Logs</p>
                  </div>
                  <FileText size={48} className="opacity-50" />
                </div>
              </div>

              {/* 日志统计卡片 */}
              <div className="grid grid-cols-2 gap-3">
                <div className="bg-gradient-to-br from-blue-500 to-cyan-500 rounded-2xl p-5 text-white shadow-lg">
                  <Database className="mb-2" size={24} />
                  <p className="text-3xl font-bold">{logs.length}</p>
                  <p className="text-xs opacity-90">总日志数</p>
                </div>
                <div className="bg-gradient-to-br from-green-500 to-emerald-500 rounded-2xl p-5 text-white shadow-lg">
                  <Activity className="mb-2" size={24} />
                  <p className="text-3xl font-bold">{logs.filter(l => l.type === 'success').length}</p>
                  <p className="text-xs opacity-90">成功记录</p>
                </div>
                <div className="bg-gradient-to-br from-yellow-500 to-orange-500 rounded-2xl p-5 text-white shadow-lg">
                  <Zap className="mb-2" size={24} />
                  <p className="text-3xl font-bold">{logs.filter(l => l.type === 'warning').length}</p>
                  <p className="text-xs opacity-90">警告信息</p>
                </div>
                <div className="bg-gradient-to-br from-red-500 to-pink-500 rounded-2xl p-5 text-white shadow-lg">
                  <Flame className="mb-2" size={24} />
                  <p className="text-3xl font-bold">{logs.filter(l => l.type === 'error').length}</p>
                  <p className="text-xs opacity-90">错误记录</p>
                </div>
              </div>

              {/* 日志列表 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-slate-200">
                <div className="flex items-center justify-between mb-5">
                  <h3 className="text-lg font-bold text-gray-800 flex items-center">
                    <Clock className="mr-2 text-slate-600" size={24} />
                    实时日志流
                  </h3>
                  <div className="flex space-x-2">
                    <button 
                      onClick={() => setLogs([])}
                      className="bg-gradient-to-r from-red-500 to-red-600 text-white px-4 py-2 rounded-xl text-xs font-medium hover:shadow-lg transition-all transform hover:scale-105"
                    >
                      清空
                    </button>
                    <button className="bg-gradient-to-r from-blue-500 to-blue-600 text-white px-4 py-2 rounded-xl text-xs font-medium hover:shadow-lg transition-all transform hover:scale-105">
                      导出
                    </button>
                  </div>
                </div>

                <div className="space-y-3 max-h-96 overflow-y-auto">
                  {logs.slice().reverse().map((log, index) => (
                    <div 
                      key={index}
                      className={`p-4 rounded-2xl border-l-4 transition-all hover:shadow-md ${
                        log.type === 'error' ? 'bg-gradient-to-r from-red-50 to-pink-50 border-red-500' :
                        log.type === 'warning' ? 'bg-gradient-to-r from-yellow-50 to-orange-50 border-yellow-500' :
                        log.type === 'success' ? 'bg-gradient-to-r from-green-50 to-emerald-50 border-green-500' :
                        'bg-gradient-to-r from-blue-50 to-cyan-50 border-blue-500'
                      }`}
                    >
                      <div className="flex items-start justify-between">
                        <div className="flex-1">
                          <div className="flex items-center space-x-2 mb-2">
                            <span className={`text-xs font-bold px-3 py-1 rounded-full ${
                              log.type === 'error' ? 'bg-red-500 text-white' :
                              log.type === 'warning' ? 'bg-yellow-500 text-white' :
                              log.type === 'success' ? 'bg-green-500 text-white' :
                              'bg-blue-500 text-white'
                            }`}>
                              {log.type.toUpperCase()}
                            </span>
                            <span className="text-xs text-gray-500 font-mono bg-white px-2 py-1 rounded">{log.time}</span>
                          </div>
                          <p className="text-sm text-gray-700 leading-relaxed">{log.message}</p>
                        </div>
                      </div>
                    </div>
                  ))}
                </div>

                {logs.length === 0 && (
                  <div className="text-center py-16 text-gray-400">
                    <Database size={64} className="mx-auto mb-4 opacity-30" />
                    <p className="text-lg font-medium">暂无日志记录</p>
                    <p className="text-sm mt-2">系统运行后日志会在这里显示</p>
                  </div>
                )}
              </div>
            </div>
          </div>
        )}

        {activeTab === 4 && (
          <div className="h-full overflow-y-auto pb-20 bg-gradient-to-br from-indigo-50 via-purple-50 to-pink-50">
            <div className="p-4 space-y-4">
              {/* 标题卡片 */}
              <div className="bg-gradient-to-r from-indigo-600 via-purple-600 to-pink-600 rounded-3xl shadow-2xl p-6 text-white">
                <div className="flex items-center justify-between">
                  <div>
                    <h2 className="text-2xl font-bold mb-1">⚙️ 系统设置</h2>
                    <p className="text-indigo-200 text-sm">System Configuration</p>
                  </div>
                  <Settings size={48} className="opacity-70" />
                </div>
              </div>

              {/* 加藤惠设置 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-pink-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <Heart className="mr-2 text-pink-500" size={24} />
                  加藤惠 AI 助手
                </h3>
                <div className="space-y-4">
                  <div className="flex items-center justify-between p-4 bg-gradient-to-r from-pink-50 to-purple-50 rounded-2xl border border-pink-200">
                    <div className="flex items-center space-x-3">
                      <div className="w-12 h-12 bg-pink-400 rounded-full flex items-center justify-center text-2xl">
                        👧
                      </div>
                      <div>
                        <p className="font-semibold text-gray-800">启用 AI 陪伴</p>
                        <p className="text-xs text-gray-500">开启智能对话和提醒功能</p>
                      </div>
                    </div>
                    <button className="w-14 h-7 rounded-full bg-pink-500 relative">
                      <div className="w-6 h-6 bg-white rounded-full absolute top-0.5 right-0.5"></div>
                    </button>
                  </div>

                  <div className="p-4 bg-purple-50 rounded-2xl border border-purple-200">
                    <div className="flex items-center justify-between mb-3">
                      <p className="font-semibold text-gray-800">对话频率</p>
                      <span className="text-sm font-mono text-purple-600">每 30 秒</span>
                    </div>
                    <input
                      type="range"
                      min="10"
                      max="120"
                      defaultValue="30"
                      className="w-full"
                    />
                    <div className="flex justify-between text-xs text-gray-500 mt-2">
                      <span>高频</span>
                      <span>低频</span>
                    </div>
                  </div>

                  <button className="w-full bg-gradient-to-r from-pink-500 to-purple-500 text-white py-3 rounded-xl font-medium hover:shadow-lg transition-all transform hover:scale-105">
                    测试对话功能
                  </button>
                </div>
              </div>

              {/* 连接设置 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-indigo-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <Bluetooth className="mr-2 text-indigo-500" size={24} />
                  蓝牙连接设置
                </h3>
                <div className="space-y-4">
                  <div className="flex items-center justify-between p-4 bg-indigo-50 rounded-2xl border border-indigo-200">
                    <div>
                      <p className="font-semibold text-gray-800">自动连接</p>
                      <p className="text-xs text-gray-500">启动时自动连接上次设备</p>
                    </div>
                    <button className="w-14 h-7 rounded-full bg-indigo-500 relative">
                      <div className="w-6 h-6 bg-white rounded-full absolute top-0.5 right-0.5"></div>
                    </button>
                  </div>

                  <div className="p-4 bg-indigo-50 rounded-2xl border border-indigo-200">
                    <div className="flex items-center justify-between mb-3">
                      <p className="font-semibold text-gray-800">数据更新频率</p>
                      <span className="text-sm font-mono text-indigo-600">2 秒</span>
                    </div>
                    <input
                      type="range"
                      min="1"
                      max="10"
                      defaultValue="2"
                      className="w-full"
                    />
                    <div className="flex justify-between text-xs text-gray-500 mt-2">
                      <span>1秒 (快)</span>
                      <span>10秒 (慢)</span>
                    </div>
                  </div>
                </div>
              </div>

              {/* 传感器校准 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-green-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <Activity className="mr-2 text-green-500" size={24} />
                  传感器校准
                </h3>
                <div className="space-y-3">
                  <button className="w-full bg-gradient-to-r from-red-500 to-orange-500 text-white py-4 rounded-2xl font-medium hover:shadow-lg transition-all transform hover:scale-105 flex items-center justify-center space-x-2">
                    <ThermometerSun size={20} />
                    <span>校准 SHT30 温湿度传感器</span>
                  </button>
                  <button className="w-full bg-gradient-to-r from-green-500 to-emerald-500 text-white py-4 rounded-2xl font-medium hover:shadow-lg transition-all transform hover:scale-105 flex items-center justify-center space-x-2">
                    <Wind size={20} />
                    <span>校准 BMP280 气压传感器</span>
                  </button>
                  <button className="w-full bg-gradient-to-r from-indigo-500 to-purple-500 text-white py-4 rounded-2xl font-medium hover:shadow-lg transition-all transform hover:scale-105 flex items-center justify-center space-x-2">
                    <Compass size={20} />
                    <span>校准 MPU6050 姿态传感器</span>
                  </button>
                </div>
              </div>

              {/* 数据管理 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-orange-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4 flex items-center">
                  <Database className="mr-2 text-orange-500" size={24} />
                  数据管理
                </h3>
                <div className="space-y-3">
                  <button className="w-full bg-gradient-to-r from-blue-500 to-cyan-500 text-white py-4 rounded-2xl font-medium hover:shadow-lg transition-all transform hover:scale-105">
                    📊 导出历史数据
                  </button>
                  <button className="w-full bg-gradient-to-r from-yellow-500 to-orange-500 text-white py-4 rounded-2xl font-medium hover:shadow-lg transition-all transform hover:scale-105">
                    🗑️ 清除缓存数据
                  </button>
                  <button className="w-full bg-gradient-to-r from-red-500 to-pink-500 text-white py-4 rounded-2xl font-medium hover:shadow-lg transition-all transform hover:scale-105">
                    ⚠️ 重置所有设置
                  </button>
                </div>
              </div>

              {/* 关于信息 */}
              <div className="bg-white rounded-3xl shadow-xl p-6 border-2 border-slate-200">
                <h3 className="text-lg font-bold text-gray-800 mb-4">关于应用</h3>
                <div className="space-y-3">
                  <div className="flex justify-between items-center p-3 bg-slate-50 rounded-xl">
                    <span className="text-sm text-gray-600">应用名称</span>
                    <span className="font-semibold text-gray-800">STM32 智能监控</span>
                  </div>
                  <div className="flex justify-between items-center p-3 bg-slate-50 rounded-xl">
                    <span className="text-sm text-gray-600">版本号</span>
                    <span className="font-mono text-indigo-600 font-bold">v1.0.0</span>
                  </div>
                  <div className="flex justify-between items-center p-3 bg-slate-50 rounded-xl">
                    <span className="text-sm text-gray-600">设备型号</span>
                    <span className="font-mono text-gray-800">STM32F103</span>
                  </div>
                  <div className="flex justify-between items-center p-3 bg-slate-50 rounded-xl">
                    <span className="text-sm text-gray-600">固件版本</span>
                    <span className="font-mono text-gray-800">v2.3.1</span>
                  </div>
                  <div className="flex justify-between items-center p-3 bg-gradient-to-r from-pink-50 to-purple-50 rounded-xl border border-pink-200">
                    <span className="text-sm text-gray-600">开发者</span>
                    <span className="font-medium text-pink-600">加藤惠 AI 团队 💖</span>
                  </div>
                </div>
              </div>
            </div>
          </div>
        )}
      </div>

      {/* 底部导航栏 */}
      <div className="fixed bottom-0 left-0 right-0 bg-white/95 backdrop-blur-sm border-t-2 border-gray-200 shadow-2xl z-10">
        <div className="flex justify-around items-center h-16">
          <button
            onClick={() => setActiveTab(0)}
            className={`flex flex-col items-center justify-center flex-1 h-full transition-all ${
              activeTab === 0 ? 'text-pink-500 scale-110' : 'text-gray-400'
            }`}
          >
            <Bluetooth size={22} className={activeTab === 0 ? 'mb-1' : ''} />
            <span className="text-xs mt-1 font-medium">连接</span>
            {activeTab === 0 && <div className="w-8 h-1 bg-pink-500 rounded-full mt-1"></div>}
          </button>
          
          <button
            onClick={() => setActiveTab(1)}
            className={`flex flex-col items-center justify-center flex-1 h-full transition-all ${
              activeTab === 1 ? 'text-blue-500 scale-110' : 'text-gray-400'
            }`}
          >
            <Cpu size={22} className={activeTab === 1 ? 'mb-1' : ''} />
            <span className="text-xs mt-1 font-medium">控制</span>
            {activeTab === 1 && <div className="w-8 h-1 bg-blue-500 rounded-full mt-1"></div>}
          </button>
          
          <button
            onClick={() => setActiveTab(2)}
            className={`flex flex-col items-center justify-center flex-1 h-full transition-all ${
              activeTab === 2 ? 'text-purple-500 scale-110' : 'text-gray-400'
            }`}
          >
            <LineChart size={22} className={activeTab === 2 ? 'mb-1' : ''} />
            <span className="text-xs mt-1 font-medium">数据</span>
            {activeTab === 2 && <div className="w-8 h-1 bg-purple-500 rounded-full mt-1"></div>}
          </button>
          
          <button
            onClick={() => setActiveTab(3)}
            className={`flex flex-col items-center justify-center flex-1 h-full transition-all ${
              activeTab === 3 ? 'text-slate-600 scale-110' : 'text-gray-400'
            }`}
          >
            <FileText size={22} className={activeTab === 3 ? 'mb-1' : ''} />
            <span className="text-xs mt-1 font-medium">日志</span>
            {activeTab === 3 && <div className="w-8 h-1 bg-slate-600 rounded-full mt-1"></div>}
          </button>
          
          <button
            onClick={() => setActiveTab(4)}
            className={`flex flex-col items-center justify-center flex-1 h-full transition-all ${
              activeTab === 4 ? 'text-indigo-600 scale-110' : 'text-gray-400'
            }`}
          >
            <Settings size={22} className={activeTab === 4 ? 'mb-1' : ''} />
            <span className="text-xs mt-1 font-medium">设置</span>
            {activeTab === 4 && <div className="w-8 h-1 bg-indigo-600 rounded-full mt-1"></div>}
          </button>
        </div>
      </div>

      <style>{`
        @keyframes slide-down {
          from {
            transform: translate(-50%, -20px);
            opacity: 0;
          }
          to {
            transform: translate(-50%, 0);
            opacity: 1;
          }
        }
        .animate-slide-down {
          animation: slide-down 0.3s ease-out;
        }
      `}</style>
    </div>
  );
}