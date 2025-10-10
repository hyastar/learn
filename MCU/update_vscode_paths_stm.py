import os
import json
import sys
import re

def replace_path_case_insensitive(text, old, new):
    """大小写不敏感地替换路径（防止 \ 被正则解析）"""
    pattern = re.compile(re.escape(old), re.IGNORECASE)
    return pattern.sub(lambda m: new, text)

def update_vscode_configs_recursively():
    """
    自动修复 VSCode c_cpp_properties.json 中的 includePath 绝对路径。
    修复大小写替换失败 + 反斜杠转义错误。
    """
    base_dir = os.getcwd()
    print(f"[*] 脚本将在根目录中运行: {base_dir}")
    print("[*] 开始递归扫描所有子目录以查找项目...")

    all_project_roots = []
    for dirpath, dirnames, filenames in os.walk(base_dir):
        if ".vscode" in dirnames:
            config_path = os.path.join(dirpath, ".vscode", "c_cpp_properties.json")
            if os.path.isfile(config_path):
                all_project_roots.append(os.path.normpath(dirpath))
                dirnames.clear()

    if not all_project_roots:
        print("[!] 未发现任何包含 VSCode 配置的项目。")
        return

    print(f"[*] 扫描完成！共找到 {len(all_project_roots)} 个项目需要处理。")

    for project_path in all_project_roots:
        folder_name = os.path.basename(project_path)
        config_path = os.path.join(project_path, ".vscode", "c_cpp_properties.json")

        print(f"\n--- 正在处理项目: {folder_name} ({project_path}) ---")

        try:
            with open(config_path, "r", encoding="utf-8") as f:
                data = json.load(f)
        except Exception as e:
            print(f"[!] 无法读取 {config_path}: {e}")
            continue

        is_modified = False
        current_root = project_path

        for config in data.get("configurations", []):
            config_name = config.get("name", "未命名配置")
            include_paths = config.get("includePath", [])
            if not include_paths:
                continue

            first_path = os.path.normpath(include_paths[0])
            old_root = None

            for known_root in all_project_roots:
                if os.path.normcase(first_path).startswith(os.path.normcase(known_root) + os.sep):
                    old_root = known_root
                    break

            if old_root is None:
                print(f"    [?] 路径 '{first_path[:60]}...' 不属于任何已知项目，跳过。")
                continue

            if os.path.normcase(old_root) == os.path.normcase(current_root):
                print(f"    [+] 配置 '{config_name}' 的路径已正确。")
                continue

            print(f"    [*] 在配置 '{config_name}' 中检测到路径不匹配：")
            print(f"        - 旧路径: {old_root}")
            print(f"        - 正确路径: {current_root}")

            updated_paths = [
                replace_path_case_insensitive(p, old_root, current_root)
                for p in include_paths
            ]
            config["includePath"] = updated_paths
            is_modified = True

        if is_modified:
            try:
                with open(config_path, "w", encoding="utf-8") as f:
                    json.dump(data, f, indent=4, ensure_ascii=False)
                print(f"    [✓] 已修改并保存 {config_path}")
            except Exception as e:
                print(f"[!] 写入失败: {e}")
        else:
            print("    [=] 无需修改。")

    print("\n[*] 所有项目处理完毕。")
    input("按 Enter 键退出...")

if __name__ == "__main__":
    update_vscode_configs_recursively()
