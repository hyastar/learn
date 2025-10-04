#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import hashlib
import json
import math
import socket
import time
import requests
import subprocess
import re
# 注意：这次我们不再需要 hmac 模块

# ======================
# 自定义 Base64
# ======================
_PADCHAR = "="
_ALPHA = "LVoJPiCN2R8G90yg+hmFHuacZ1OWMnrsSTXkYpUq/3dlbfKwv6xztjI7DeBE45QA"

def _getbyte(s, i):
    x = ord(s[i])
    if x > 255:
        raise ValueError("INVALID_CHARACTER_ERR")
    return x

def get_base64(s: str) -> str:
    i = 0
    b10 = 0
    x = []
    imax = len(s) - len(s) % 3
    if len(s) == 0:
        return s
    for i in range(0, imax, 3):
        b10 = (_getbyte(s, i) << 16) | (_getbyte(s, i + 1) << 8) | _getbyte(s, i + 2)
        x.append(_ALPHA[(b10 >> 18)])
        x.append(_ALPHA[((b10 >> 12) & 63)])
        x.append(_ALPHA[((b10 >> 6) & 63)])
        x.append(_ALPHA[(b10 & 63)])
    i = imax
    if len(s) - imax == 1:
        b10 = _getbyte(s, i) << 16
        x.append(_ALPHA[(b10 >> 18)] + _ALPHA[((b10 >> 12) & 63)] + _PADCHAR + _PADCHAR)
    elif len(s) - imax == 2:
        b10 = (_getbyte(s, i) << 16) | (_getbyte(s, i + 1) << 8)
        x.append(_ALPHA[(b10 >> 18)] + _ALPHA[((b10 >> 12) & 63)] + _ALPHA[((b10 >> 6) & 63)] + _PADCHAR)
    return "".join(x)

# ======================
# SHA1
# ======================
def get_sha1(value: str) -> str:
    return hashlib.sha1(value.encode()).hexdigest()

# ======================
# xEncode
# ======================
def ordat(msg, idx):
    return ord(msg[idx]) if idx < len(msg) else 0

def sencode(msg, key):
    l = len(msg)
    pwd = []
    for i in range(0, l, 4):
        pwd.append(
            ordat(msg, i)
            | ordat(msg, i + 1) << 8
            | ordat(msg, i + 2) << 16
            | ordat(msg, i + 3) << 24
        )
    if key:
        pwd.append(l)
    return pwd

def lencode(msg, key):
    l = len(msg)
    ll = (l - 1) << 2
    if key:
        m = msg[l - 1]
        if m < ll - 3 or m > ll:
            return
        ll = m
    for i in range(0, l):
        msg[i] = (
            chr(msg[i] & 0xFF)
            + chr(msg[i] >> 8 & 0xFF)
            + chr(msg[i] >> 16 & 0xFF)
            + chr(msg[i] >> 24 & 0xFF)
        )
    return "".join(msg)[:ll] if key else "".join(msg)

def get_xencode(msg, key):
    if msg == "":
        return ""
    pwd = sencode(msg, True)
    pwdk = sencode(key, False)
    if len(pwdk) < 4:
        pwdk += [0] * (4 - len(pwdk))
    n = len(pwd) - 1
    z = pwd[n]
    y = pwd[0]
    c = 0x86014019 | 0x183639A0
    q = math.floor(6 + 52 / (n + 1))
    d = 0
    while q > 0:
        d = d + c & (0x8CE0D9BF | 0x731F2640)
        e = d >> 2 & 3
        for p in range(0, n):
            y = pwd[p + 1]
            m = (z >> 5 ^ y << 2) + ((y >> 3 ^ z << 4) ^ (d ^ y)) + (pwdk[(p & 3) ^ e] ^ z)
            pwd[p] = pwd[p] + m & (0xEFB8D130 | 0x10472ECF)
            z = pwd[p]
        y = pwd[0]
        m = (z >> 5 ^ y << 2) + ((y >> 3 ^ z << 4) ^ (d ^ y)) + (pwdk[(n & 3) ^ e] ^ z)
        pwd[n] = pwd[n] + m & (0xBB390742 | 0x44C6F8BD)
        z = pwd[n]
        q -= 1
    return lencode(pwd, False)

# ======================
# 获取本机出口 IP
# ======================
def get_local_ip():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
        s.close()
        return ip
    except:
        return None

# ======================
# 获取默认网关（Windows ipconfig）
# ======================
def get_gateway_ip():
    try:
        output = subprocess.check_output("ipconfig", shell=True, text=True, encoding="gbk", errors="ignore")
        match = re.search(r"默认网关[ .:]*([\d]+\.[\d]+\.[\d]+\.[\d]+)", output)
        if match:
            return match.group(1)
    except:
        pass
    return "10.21.255.254"

# ======================
# 自动抓认证服务器 IP
# ======================
def get_auth_server(gateway_ip):
    try:
        html = requests.get(f"http://{gateway_ip}/", timeout=3, allow_redirects=True).text
        match = re.search(r'http://([\d\.]+)/srun_portal_pc', html)
        if match:
            return match.group(1)
    except Exception as e:
        print(f"[WARN] 无法从网关({gateway_ip})页面提取认证服务器:", e)
    return "202.194.116.116"


# ======================
# 生成 info
# ======================
def make_info(username, ip, ac_id, challenge, password):
    raw = {
        "username": username,
        "password": password,
        "ip": ip,
        "acid": ac_id,
        "enc_ver": "srun_bx1",
    }
    raw_json = json.dumps(raw, separators=(",", ":"))
    encoded = get_xencode(raw_json, challenge)
    return "{SRBX1}" + get_base64(encoded)

# ======================
# 主逻辑
# ======================
def login(username, password, ac_id="1"):
    ip = get_local_ip()
    if not ip:
        print("[ERROR] 无法获取本机IP地址，请检查网络连接。")
        return
        
    gw_ip = get_gateway_ip()
    auth_server = get_auth_server(gw_ip)

    print(f"[INFO] 本机出口 IP: {ip}")
    print(f"[INFO] 默认网关 IP: {gw_ip}")
    print(f"[INFO] 认证服务器 IP: {auth_server}")

    timestamp = int(time.time() * 1000)
    callback_param = f"jQuery11240{str(time.time()).replace('.','')}{int(time.time()*1000)}_{timestamp}"
    
    url_challenge = (
        f"http://{auth_server}/cgi-bin/get_challenge?"
        f"callback={callback_param}&"
        f"username={username}&"
        f"ip={ip}&"
        f"ac_id={ac_id}&"
        f"_={timestamp}"
    )
    print("[DEBUG] challenge url:", url_challenge)

    try:
        res = requests.get(url_challenge, timeout=5).text
    except requests.exceptions.RequestException as e:
        print(f"[ERROR] 请求 challenge 失败: {e}")
        return

    print("[DEBUG] challenge raw:", res[:200])

    if "ok" in res and "challenge" not in res:
        print("[INFO] 服务器返回 'ok'，表示您可能已经登录成功。")
        return

    try:
        json_str = res[len(callback_param)+1:-1]
        challenge_data = json.loads(json_str)
        challenge = challenge_data.get("challenge")
        if not challenge:
            print(f"[ERROR] 未能在响应中找到 challenge: {challenge_data}")
            return
        print("[INFO] challenge =", challenge)
    except (IndexError, json.JSONDecodeError) as e:
        print(f"[ERROR] 解析 challenge 失败: {e}. 原始响应: {res}")
        return

    # [FINAL ATTEMPT] Revert to the simplest password hashing: MD5(challenge + password)
    hmd5_hex = hashlib.md5((challenge + password).encode()).hexdigest()
    
    info_field = make_info(username, ip, ac_id, challenge, password)

    chkstr = (
        challenge + username +
        challenge + hmd5_hex +
        challenge + ac_id +
        challenge + ip +
        challenge + "200" +
        challenge + "1" +
        challenge + info_field
    )
    chksum = get_sha1(chkstr)
    
    login_timestamp = int(time.time()*1000)
    login_callback = f"jQuery11240{str(time.time()).replace('.','')}{int(time.time()*1000)}_{login_timestamp}"

    url_login = (
        f"http://{auth_server}/cgi-bin/srun_portal?"
        f"callback={login_callback}&action=login&username={username}"
        f"&password={{MD5}}{hmd5_hex}&ac_id={ac_id}&ip={ip}&info={info_field}"
        f"&chksum={chksum}&n=200&type=1&os=Windows+10&name=Windows"
        f"&double_stack=0&_={login_timestamp}"
    )

    print("[DEBUG] login url:", url_login[:150], "...")
    try:
        res_login = requests.get(url_login, timeout=5).text
        print("[INFO] 服务器响应:", res_login)
        # Check if login response is truly successful
        if "suc_msg" in res_login or "login_ok" in res_login or '"error":"ok"' in res_login:
            print("\n[SUCCESS] 登录成功！")
        else:
            print("\n[FAIL] 登录失败，请检查服务器响应信息。")

    except requests.exceptions.RequestException as e:
        print(f"[ERROR] 登录请求失败: {e}")
        return
    
# ======================
if __name__ == "__main__":
    user = input("username > ").strip()
    pw = input("password > ").strip()
    login(user, pw, ac_id="5")

