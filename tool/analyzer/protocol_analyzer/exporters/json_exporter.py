"""
JSON导出器 - 用于AI和程序处理
"""

import json
from pathlib import Path


def export_json(transactions, output_path):
    """
    导出事务数据为JSON格式
    
    Args:
        transactions: 事务列表
        output_path: 输出文件路径
    """
    output_path = Path(output_path)
    
    # 按协议类型分组
    grouped = {}
    for trans in transactions:
        protocol = trans.get('protocol', 'Unknown')
        if protocol not in grouped:
            grouped[protocol] = []
        grouped[protocol].append(trans)
    
    # 生成统计信息
    stats = {
        'total_transactions': len(transactions),
        'by_protocol': {
            protocol: len(trans_list)
            for protocol, trans_list in grouped.items()
        }
    }
    
    # 构建输出结构
    output_data = {
        'statistics': stats,
        'transactions': transactions,
        'grouped_by_protocol': grouped
    }
    
    # 写入JSON文件
    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(output_data, f, indent=2, ensure_ascii=False)
    
    print(f"✅ JSON导出成功: {output_path}")
    print(f"   总事务数: {len(transactions)}")
    for protocol, count in stats['by_protocol'].items():
        print(f"   {protocol}: {count} 个事务")