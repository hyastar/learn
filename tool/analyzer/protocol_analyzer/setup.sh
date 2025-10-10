#!/bin/bash

echo "======================================"
echo "🔍 Saleae Logic 协议分析器 - 安装向导"
echo "======================================"
echo ""

# 检查Python
echo "📋 检查Python环境..."
if command -v python3 &> /dev/null; then
    PYTHON_VERSION=$(python3 --version)
    echo "✅ 已安装: $PYTHON_VERSION"
else
    echo "❌ 未找到Python3，请先安装Python 3.7+"
    exit 1
fi

# 创建虚拟环境 (可选)
echo ""
read -p "是否创建虚拟环境? (推荐) [y/N]: " CREATE_VENV
if [[ $CREATE_VENV =~ ^[Yy]$ ]]; then
    echo "📦 创建虚拟环境..."
    python3 -m venv venv
    source venv/bin/activate
    echo "✅ 虚拟环境已激活"
fi

# 安装依赖
echo ""
echo "📥 安装Python依赖包..."
pip install -r requirements.txt

if [ $? -eq 0 ]; then
    echo "✅ 依赖安装成功"
else
    echo "❌ 依赖安装失败"
    exit 1
fi

# 创建目录结构
echo ""
echo "📁 创建目录结构..."
mkdir -p data output

# 创建测试CSV
echo ""
read -p "是否创建测试数据? [y/N]: " CREATE_TEST
if [[ $CREATE_TEST =~ ^[Yy]$ ]]; then
    echo "📝 生成测试I2C数据..."
    cat > data/test_i2c.csv << 'EOF'
Time [s],Channel 0,Channel 1
0.000000,1,1
0.000001,1,1
0.000002,1,0
0.000003,0,0
0.000004,0,0
0.000005,1,0
0.000006,1,1
0.000007,1,1
0.000008,0,1
0.000009,0,1
0.000010,1,1
0.000011,1,0
0.000012,0,0
0.000013,1,0
0.000014,1,1
0.000015,1,1
EOF
    echo "✅ 测试数据已创建: data/test_i2c.csv"
fi

# 完成
echo ""
echo "======================================"
echo "✅ 安装完成！"
echo "======================================"
echo ""
echo "🚀 快速开始:"
echo "   1. 将Saleae导出的CSV文件放入 data/ 目录"
echo "   2. 运行: python analyzer.py"
echo "   3. 查看结果:"
echo "      - JSON: output/analysis.json"
echo "      - HTML: output/analysis.html"
echo ""
echo "📚 帮助文档: 查看 README.md"
echo "======================================"