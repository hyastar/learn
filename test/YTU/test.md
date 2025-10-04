 YTU  python ytu.py                                                                                                                                                                                                                  
=== ytu_debug_auto_v3_fixed.py (集成 xEncode + 调试输出) ===
username > 202280506216        
password > HTYLY223
ip (default 10.21.xx.xx) > 10.21.64.82

=== 尝试候选: md5(password) | password_mode=0 ===
[*] get_challenge 响应: jQuery6743758240493002_1759454460647({"challenge":"fcae575b637ce71cb0c5e6bced448917599d88cd2c31f4a4c3572f6aaad8c8fe","client_ip":"10.21.64.82","ecode"...
[*] fresh challenge = fcae575b637ce71cb0c5e6bced448917599d88cd2c31f4a4c3572f6aaad8c8fe
[*] hmd5_hex = ac3850c4d33ad101d7c38d8ff02661c6
[info raw] {"username":"202280506216","password":"","ip":"10.21.64.82","acid":"5","enc_ver":"srun_bx1"}
[info field preview] {SRBX1}4sVIEP1B2EiG9vPSb5yQ7TkPGdCHyKVecOSEt2UYOJUHgc3CurzpzFk9++PTNfhtBlD9XY4lOLrr8GlrAYJ4smiOq+Hgi...
[*] chksum = d81d754ffa1569609a8e401b7819505fbd777513
[*] 请求参数:
    callback = jQuery4899138886681324_1759454460672
    action = login
    username = 202280506216
    password = {MD5}ac3850c4d33ad101d7c38d8ff02661c6
    ac_id = 5
    ip = 10.21.64.82
    info = {SRBX1}4sVIEP1B2EiG9vPSb5yQ7TkPGdCHyKVecOSEt2UYOJUHgc3CurzpzFk9++PTNfhtBlD9XY4lOLrr8GlrAYJ4smiOq+HgisoNSRfeEaUSbmHxch82rUkM4JTLuiR4K7jr
    chksum = d81d754ffa1569609a8e401b7819505fbd777513
    n = 200
    type = 1
    _ = 1759454460672
HTTP 200 响应前 200 字符:
jQuery4899138886681324_1759454460672({"client_ip":"10.21.64.82","ecode":"E2553","error":"login_error","error_msg":"E2553: Password is error.","online_ip":"10.21.64.82","res":"login_error","srun_ver":"
[*] 返回 JSON 解析结果:
    client_ip = 10.21.64.82
    ecode = E2553
    error = login_error
    error_msg = E2553: Password is error.
    online_ip = 10.21.64.82
    res = login_error
    srun_ver = SRunCGIAuthIntfSvr V1.18 B20190404
    st = 1759454318
[-] 尝试完毕，等待 20s...


=== 尝试候选: md5(password) | password_mode=1 ===
[*] get_challenge 响应: jQuery6775190170208363_1759454480736({"challenge":"fcae575b637ce71cb0c5e6bced448917599d88cd2c31f4a4c3572f6aaad8c8fe","client_ip":"10.21.64.82","ecode"...
[*] fresh challenge = fcae575b637ce71cb0c5e6bced448917599d88cd2c31f4a4c3572f6aaad8c8fe
[*] hmd5_hex = ac3850c4d33ad101d7c38d8ff02661c6
[info raw] {"username":"202280506216","password":"HTYLY223","ip":"10.21.64.82","acid":"5","enc_ver":"srun_bx1"}
[info field preview] {SRBX1}p2Dpu9HyRcdWABA4fAOI0Bk1kkwZeky0JIafqdA4V+Z5HPVaMb6ln5UaVcipWL4bAOgVPxpWAxguD0Ctx5IssuOSG7mbB...
[*] chksum = 43ffe65478056337a10212eb9dedb630b50b9111
[*] 请求参数:
    callback = jQuery7283917774152449_1759454480752
    action = login
    username = 202280506216
    password = {MD5}ac3850c4d33ad101d7c38d8ff02661c6
    ac_id = 5
    ip = 10.21.64.82
    info = {SRBX1}p2Dpu9HyRcdWABA4fAOI0Bk1kkwZeky0JIafqdA4V+Z5HPVaMb6ln5UaVcipWL4bAOgVPxpWAxguD0Ctx5IssuOSG7mbBMNaBe3T/XZ4O0M4L9luMpIgCzr5+4i47PrUqj9otYPNfm+=
    chksum = 43ffe65478056337a10212eb9dedb630b50b9111
    n = 200
    type = 1
    _ = 1759454480752
HTTP 200 响应前 200 字符:
jQuery7283917774152449_1759454480752({"ServerFlag":0,"ServicesIntfServerIP":"0.0.0.0","ServicesIntfServerPort":"8001","access_token":"fcae575b637ce71cb0c5e6bced448917599d88cd2c31f4a4c3572f6aaad8c8fe",
[*] 返回 JSON 解析结果:
    ServerFlag = 0
    ServicesIntfServerIP = 0.0.0.0
    ServicesIntfServerPort = 8001
    access_token = fcae575b637ce71cb0c5e6bced448917599d88cd2c31f4a4c3572f6aaad8c8fe
    checkout_date = 0
    client_ip = 10.21.64.82
    ecode = 0
    error = ok
    error_msg =
    online_ip = 10.21.64.82
    ploy_msg = E0000: Login is successful.
    real_name =
    remain_flux = 0
    remain_times = 0
    res = ok
    srun_ver = SRunCGIAuthIntfSvr V1.18 B20190404
    suc_msg = login_ok
    sysver = 1.01.20190404
    username = 202280506216
    wallet_balance = 0
[-] 尝试完毕，等待 20s...


=== 尝试候选: md5(password) | password_mode=2 ===
[*] get_challenge 响应: jQuery0248633816445664_1759454500883({"challenge":"ef479e6cdc42c2106ff7be35a990913fd5bfacd71502c152a0980aa729c6f693","client_ip":"10.21.64.82","ecode"...
[*] fresh challenge = ef479e6cdc42c2106ff7be35a990913fd5bfacd71502c152a0980aa729c6f693
[*] hmd5_hex = ac3850c4d33ad101d7c38d8ff02661c6
[info raw] {"username":"202280506216","password":"{MD5}ac3850c4d33ad101d7c38d8ff02661c6","ip":"10.21.64.82","acid":"5","enc_ver":"srun_bx1"}
[info field preview] {SRBX1}Fl1ObWVcCg4XxTIAZ9jPjv+rDhaZwE6tf4Oc6+s6zKNMz+IQ9oTN2Q+r/639emPxrdLLULyETTcL4D2TvfhbZdoxreiZG...
[*] chksum = dedff9b64677b400f088109a24b0ebf3b83b1454
[*] 请求参数:
    callback = jQuery7148713849847895_1759454500914
    action = login
    username = 202280506216
    password = {MD5}ac3850c4d33ad101d7c38d8ff02661c6
    ac_id = 5
    ip = 10.21.64.82
    info = {SRBX1}Fl1ObWVcCg4XxTIAZ9jPjv+rDhaZwE6tf4Oc6+s6zKNMz+IQ9oTN2Q+r/639emPxrdLLULyETTcL4D2TvfhbZdoxreiZG1PBZH9pPzu7SRX+wLSKC0shYh1C0m0BAClTDQu9Vl9cJBhYAF5aoAYzvxaTti4b4FaZEYtubBJ4WA9FOTnHCKTpSL==
    chksum = dedff9b64677b400f088109a24b0ebf3b83b1454
    n = 200
    type = 1
    _ = 1759454500914
HTTP 200 响应前 200 字符:
jQuery7148713849847895_1759454500914({"ServerFlag":0,"ServicesIntfServerIP":"0.0.0.0","ServicesIntfServerPort":"8001","access_token":"ef479e6cdc42c2106ff7be35a990913fd5bfacd71502c152a0980aa729c6f693",
[*] 返回 JSON 解析结果:
    ServerFlag = 0
    ServicesIntfServerIP = 0.0.0.0
    ServicesIntfServerPort = 8001
    access_token = ef479e6cdc42c2106ff7be35a990913fd5bfacd71502c152a0980aa729c6f693
    checkout_date = 0
    client_ip = 10.21.64.82
    ecode = 0
    error = ok
    error_msg =
    online_ip = 10.21.64.82
    ploy_msg = E0000: Login is successful.
    real_name =
    remain_flux = 0
    remain_times = 0
    res = ok
    srun_ver = SRunCGIAuthIntfSvr V1.18 B20190404
    suc_msg = ip_already_online_error
    sysver = 1.01.20190404
    username = 202280506216
    wallet_balance = 0
[-] 尝试完毕，等待 20s...


=== 尝试候选: hmac_md5(password,challenge) | password_mode=0 ===
[*] get_challenge 响应: jQuery9600181131623038_1759454520944({"challenge":"ef479e6cdc42c2106ff7be35a990913fd5bfacd71502c152a0980aa729c6f693","client_ip":"10.21.64.82","ecode"...
[*] fresh challenge = ef479e6cdc42c2106ff7be35a990913fd5bfacd71502c152a0980aa729c6f693
[*] hmd5_hex = 47adbd86c0e94fbcc8d1b80a297ab0eb
[info raw] {"username":"202280506216","password":"","ip":"10.21.64.82","acid":"5","enc_ver":"srun_bx1"}
[info field preview] {SRBX1}jpGEqr21ohzn+n7f0y6L8f6WMfF8frWdbI+ZvoLFEZfKGDhYEs+HRDiYWL+6llhPIpme2n9HLyFyJzzLf/FoEthLX1wvM...
[*] chksum = 024f0a743e58e06837b4a1b1b6d27daddad5eb27
[*] 请求参数:
    callback = jQuery0252279015706867_1759454520960
    action = login
    username = 202280506216
    password = {MD5}47adbd86c0e94fbcc8d1b80a297ab0eb
    ac_id = 5
    ip = 10.21.64.82
    info = {SRBX1}jpGEqr21ohzn+n7f0y6L8f6WMfF8frWdbI+ZvoLFEZfKGDhYEs+HRDiYWL+6llhPIpme2n9HLyFyJzzLf/FoEthLX1wvMtG2xB37Xez6ZFzu1ouLIxfvL4/5A18YVdXs
    chksum = 024f0a743e58e06837b4a1b1b6d27daddad5eb27
    n = 200
    type = 1
    _ = 1759454520960
HTTP 200 响应前 200 字符:
jQuery0252279015706867_1759454520960({"ServerFlag":0,"ServicesIntfServerIP":"0.0.0.0","ServicesIntfServerPort":"8001","access_token":"ef479e6cdc42c2106ff7be35a990913fd5bfacd71502c152a0980aa729c6f693",
[*] 返回 JSON 解析结果:
    ServerFlag = 0
    ServicesIntfServerIP = 0.0.0.0
    ServicesIntfServerPort = 8001
    access_token = ef479e6cdc42c2106ff7be35a990913fd5bfacd71502c152a0980aa729c6f693
    checkout_date = 0
    client_ip = 10.21.64.82
    ecode = 0
    error = ok
    error_msg =
    online_ip = 10.21.64.82
    real_name =
    remain_flux = 0
    remain_times = 0
    res = ok
    srun_ver = SRunCGIAuthIntfSvr V1.18 B20190404
    suc_msg = ip_already_online_error
    sysver = 1.01.20190404
    username = 202280506216
    wallet_balance = 0
[-] 尝试完毕，等待 20s...


=== 尝试候选: hmac_md5(password,challenge) | password_mode=1 ===
[*] get_challenge 响应: jQuery4864837430894884_1759454540988({"challenge":"7ee4b69024e90c05fb687d301af3e16225812fcce9ba3dd428df39c4774aaff7","client_ip":"10.21.64.82","ecode"...
[*] fresh challenge = 7ee4b69024e90c05fb687d301af3e16225812fcce9ba3dd428df39c4774aaff7
[*] hmd5_hex = b41e1c964d6206379f633e861df8b7aa
[info raw] {"username":"202280506216","password":"HTYLY223","ip":"10.21.64.82","acid":"5","enc_ver":"srun_bx1"}
[info field preview] {SRBX1}Gdl4W6eXZk4gMBc4OPU3KwthPopjXoqSDuwruiixfILWaRlKhe7KGzNjnIy1kuRfWJq81nd17jv6MVFuN7LvQwlw0mXlM...
[*] chksum = e0a68ab347be61dc38c3d11f49da8bffcb129f2a
[*] 请求参数:
    callback = jQuery9598397420640467_1759454541015
    action = login
    username = 202280506216
    password = {MD5}b41e1c964d6206379f633e861df8b7aa
    ac_id = 5
    ip = 10.21.64.82
    info = {SRBX1}Gdl4W6eXZk4gMBc4OPU3KwthPopjXoqSDuwruiixfILWaRlKhe7KGzNjnIy1kuRfWJq81nd17jv6MVFuN7LvQwlw0mXlMirCtmtf8AuOUvk9/QmNFue1Tocnx8NeNkIY3aPQwVlPabH=
    chksum = e0a68ab347be61dc38c3d11f49da8bffcb129f2a
    n = 200
    type = 1
    _ = 1759454541015
HTTP 200 响应前 200 字符:
jQuery9598397420640467_1759454541015({"ServerFlag":0,"ServicesIntfServerIP":"0.0.0.0","ServicesIntfServerPort":"8001","access_token":"7ee4b69024e90c05fb687d301af3e16225812fcce9ba3dd428df39c4774aaff7",
[*] 返回 JSON 解析结果:
    ServerFlag = 0
    ServicesIntfServerIP = 0.0.0.0
    ServicesIntfServerPort = 8001
    access_token = 7ee4b69024e90c05fb687d301af3e16225812fcce9ba3dd428df39c4774aaff7
    checkout_date = 0
    client_ip = 10.21.64.82
    ecode = 0
    error = ok
    error_msg =
    online_ip = 10.21.64.82
    real_name =
    remain_flux = 0
    remain_times = 0
    res = ok
    srun_ver = SRunCGIAuthIntfSvr V1.18 B20190404
    suc_msg = ip_already_online_error
    sysver = 1.01.20190404
    username = 202280506216
    wallet_balance = 0
[-] 尝试完毕，等待 20s...


=== 尝试候选: hmac_md5(password,challenge) | password_mode=2 ===
[*] get_challenge 响应: jQuery8142450337065571_1759454561049({"challenge":"7ee4b69024e90c05fb687d301af3e16225812fcce9ba3dd428df39c4774aaff7","client_ip":"10.21.64.82","ecode"...
[*] fresh challenge = 7ee4b69024e90c05fb687d301af3e16225812fcce9ba3dd428df39c4774aaff7
[*] hmd5_hex = b41e1c964d6206379f633e861df8b7aa
[info raw] {"username":"202280506216","password":"{MD5}ac3850c4d33ad101d7c38d8ff02661c6","ip":"10.21.64.82","acid":"5","enc_ver":"srun_bx1"}
[info field preview] {SRBX1}iMxSlBiLhC8UBOFVtf0RsmlxIzF62Qlj8keLJW89z0BQWs9nBhLUz0rpEMpUWn6cKfTRI/TO4EPs8cY2SRoXX7j9s30ym...
[*] chksum = e029be934b368d55c2a4531acc81109ffde93b97
[*] 请求参数:
    callback = jQuery4748985404585806_1759454561065
    action = login
    username = 202280506216
    password = {MD5}b41e1c964d6206379f633e861df8b7aa
    ac_id = 5
    ip = 10.21.64.82
    info = {SRBX1}iMxSlBiLhC8UBOFVtf0RsmlxIzF62Qlj8keLJW89z0BQWs9nBhLUz0rpEMpUWn6cKfTRI/TO4EPs8cY2SRoXX7j9s30ymAl+lGawTmuaA16VU463DeaWiLOvzJwa/ag4ZC9HETtJs32p9R2STwnHpB9V5I81ml67mLLQeiTU96xhCPNCdAmW1S==
    chksum = e029be934b368d55c2a4531acc81109ffde93b97
    n = 200
    type = 1
    _ = 1759454561065
HTTP 200 响应前 200 字符:
jQuery4748985404585806_1759454561065({"ServerFlag":0,"ServicesIntfServerIP":"0.0.0.0","ServicesIntfServerPort":"8001","access_token":"7ee4b69024e90c05fb687d301af3e16225812fcce9ba3dd428df39c4774aaff7",
[*] 返回 JSON 解析结果:
    ServerFlag = 0
    ServicesIntfServerIP = 0.0.0.0
    ServicesIntfServerPort = 8001
    access_token = 7ee4b69024e90c05fb687d301af3e16225812fcce9ba3dd428df39c4774aaff7
    checkout_date = 0
    client_ip = 10.21.64.82
    ecode = 0
    error = ok
    error_msg =
    online_ip = 10.21.64.82
    real_name =
    remain_flux = 0
    remain_times = 0
    res = ok
    srun_ver = SRunCGIAuthIntfSvr V1.18 B20190404
    suc_msg = ip_already_online_error
    sysver = 1.01.20190404
    username = 202280506216
    wallet_balance = 0
[-] 尝试完毕，等待 20s...


=== 尝试候选: md5(md5(password)+challenge) | password_mode=0 ===
[*] get_challenge 响应: jQuery1827275043729248_1759454581104({"challenge":"42ae71760883291888c90185c6a004833f178b2ad55e5ad43c2c61d75262cef1","client_ip":"10.21.64.82","ecode"...
[*] fresh challenge = 42ae71760883291888c90185c6a004833f178b2ad55e5ad43c2c61d75262cef1
[*] hmd5_hex = d1311813b6dc71ff81d7650a9c206381
[info raw] {"username":"202280506216","password":"","ip":"10.21.64.82","acid":"5","enc_ver":"srun_bx1"}
[info field preview] {SRBX1}CGTIKxpsrPfVXb0Dx2IxwjWJz2Q2K9GVRgZq2jUM8Xxb07NzIx9Xzl5k4VZyDzqEurl47j9k7XqyKDG7LntaPngrKjvPc...
[*] chksum = 255e02a5834e7a8722feb43991676194eabb2c98
[*] 请求参数:
    callback = jQuery4466964238837339_1759454581121
    action = login
    username = 202280506216
    password = {MD5}d1311813b6dc71ff81d7650a9c206381
    ac_id = 5
    ip = 10.21.64.82
    info = {SRBX1}CGTIKxpsrPfVXb0Dx2IxwjWJz2Q2K9GVRgZq2jUM8Xxb07NzIx9Xzl5k4VZyDzqEurl47j9k7XqyKDG7LntaPngrKjvPcevt0QtuKp4NAKpkdEDSBMnnKVhoKReqntPk
    chksum = 255e02a5834e7a8722feb43991676194eabb2c98
    n = 200
    type = 1
    _ = 1759454581121
HTTP 200 响应前 200 字符:
jQuery4466964238837339_1759454581121({"ServerFlag":0,"ServicesIntfServerIP":"0.0.0.0","ServicesIntfServerPort":"8001","access_token":"42ae71760883291888c90185c6a004833f178b2ad55e5ad43c2c61d75262cef1",
[*] 返回 JSON 解析结果:
    ServerFlag = 0
    ServicesIntfServerIP = 0.0.0.0
    ServicesIntfServerPort = 8001
    access_token = 42ae71760883291888c90185c6a004833f178b2ad55e5ad43c2c61d75262cef1
    checkout_date = 0
    client_ip = 10.21.64.82
    ecode = 0
    error = ok
    error_msg =
    online_ip = 10.21.64.82
    real_name =
    remain_flux = 0
    remain_times = 0
    res = ok
    srun_ver = SRunCGIAuthIntfSvr V1.18 B20190404
    suc_msg = ip_already_online_error
    sysver = 1.01.20190404
    username = 202280506216
    wallet_balance = 0
[-] 尝试完毕，等待 20s...


=== 尝试候选: md5(md5(password)+challenge) | password_mode=1 ===
[*] get_challenge 响应: jQuery5851734146800481_1759454601156({"challenge":"42ae71760883291888c90185c6a004833f178b2ad55e5ad43c2c61d75262cef1","client_ip":"10.21.64.82","ecode"...
[*] fresh challenge = 42ae71760883291888c90185c6a004833f178b2ad55e5ad43c2c61d75262cef1
[*] hmd5_hex = d1311813b6dc71ff81d7650a9c206381
[info raw] {"username":"202280506216","password":"HTYLY223","ip":"10.21.64.82","acid":"5","enc_ver":"srun_bx1"}
[info field preview] {SRBX1}klnEp6GCVer6Oa2oq/8dvgVYjT2QJ2epcMrVnRPdGMvxUIAENXwJYDyM8u15IUhhk7bExDIIyR8+Ij/PppnBNrHNSspvW...
[*] chksum = fa161db35fde3793ee244ccfd5a41e657489c117
[*] 请求参数:
    callback = jQuery3527088651971500_1759454601184
    action = login
    username = 202280506216
    password = {MD5}d1311813b6dc71ff81d7650a9c206381
    ac_id = 5
    ip = 10.21.64.82
    info = {SRBX1}klnEp6GCVer6Oa2oq/8dvgVYjT2QJ2epcMrVnRPdGMvxUIAENXwJYDyM8u15IUhhk7bExDIIyR8+Ij/PppnBNrHNSspvWnwZ7lRmEhQW66MBcWUtS+M1zo5dptJYM1G0SCn6MuhG/4+=
    chksum = fa161db35fde3793ee244ccfd5a41e657489c117
    n = 200
    type = 1
    _ = 1759454601184
HTTP 200 响应前 200 字符:
jQuery3527088651971500_1759454601184({"ServerFlag":0,"ServicesIntfServerIP":"0.0.0.0","ServicesIntfServerPort":"8001","access_token":"42ae71760883291888c90185c6a004833f178b2ad55e5ad43c2c61d75262cef1",
[*] 返回 JSON 解析结果:
    ServerFlag = 0
    ServicesIntfServerIP = 0.0.0.0
    ServicesIntfServerPort = 8001
    access_token = 42ae71760883291888c90185c6a004833f178b2ad55e5ad43c2c61d75262cef1
    checkout_date = 0
    client_ip = 10.21.64.82
    ecode = 0
    error = ok
    error_msg =
    online_ip = 10.21.64.82
    real_name =
    remain_flux = 0
    remain_times = 0
    res = ok
    srun_ver = SRunCGIAuthIntfSvr V1.18 B20190404
    suc_msg = ip_already_online_error
    sysver = 1.01.20190404
    username = 202280506216
    wallet_balance = 0
[-] 尝试完毕，等待 20s...


=== 尝试候选: md5(md5(password)+challenge) | password_mode=2 ===
[*] get_challenge 响应: jQuery2197688910858681_1759454621210({"challenge":"00a8ceaf5fc52e491d50bde5a630785063b7a787d209a83784659a737e8a2c7a","client_ip":"10.21.64.82","ecode"...
[*] fresh challenge = 00a8ceaf5fc52e491d50bde5a630785063b7a787d209a83784659a737e8a2c7a
[*] hmd5_hex = c600e3cd2f575a5b95f4d72200bc8c07
[info raw] {"username":"202280506216","password":"{MD5}ac3850c4d33ad101d7c38d8ff02661c6","ip":"10.21.64.82","acid":"5","enc_ver":"srun_bx1"}
[info field preview] {SRBX1}ma7ygRdw3NlglXHHnBrfiUxs4sW14a/EGb42I8QHNHWgmm5HL3T/blpS5605eSSxQal4rXp7I2mVLNzdQCioXAYd9WIlM...
[*] chksum = 4199dd78f14a340f1725a2c94ead23a8df4c85bb
[*] 请求参数:
    callback = jQuery6031499877031706_1759454621225
    action = login
    username = 202280506216
    password = {MD5}c600e3cd2f575a5b95f4d72200bc8c07
    ac_id = 5
    ip = 10.21.64.82
    info = {SRBX1}ma7ygRdw3NlglXHHnBrfiUxs4sW14a/EGb42I8QHNHWgmm5HL3T/blpS5605eSSxQal4rXp7I2mVLNzdQCioXAYd9WIlM87oTFEPbbe7389V/Sf2nwjktqqModKfFbb7ZBIvND4KyJTdNv/VU//edV6dk/B5gGayZGw/bUzEe9KTjMWQXQ6Io+==
    chksum = 4199dd78f14a340f1725a2c94ead23a8df4c85bb
    n = 200
    type = 1
    _ = 1759454621225
HTTP 200 响应前 200 字符:
jQuery6031499877031706_1759454621225({"ServerFlag":0,"ServicesIntfServerIP":"0.0.0.0","ServicesIntfServerPort":"8001","access_token":"00a8ceaf5fc52e491d50bde5a630785063b7a787d209a83784659a737e8a2c7a",
[*] 返回 JSON 解析结果:
    ServerFlag = 0
    ServicesIntfServerIP = 0.0.0.0
    ServicesIntfServerPort = 8001
    access_token = 00a8ceaf5fc52e491d50bde5a630785063b7a787d209a83784659a737e8a2c7a
    checkout_date = 0
    client_ip = 10.21.64.82
    ecode = 0
    error = ok
    error_msg =
    online_ip = 10.21.64.82
    real_name =
    remain_flux = 0
    remain_times = 0
    res = ok
    srun_ver = SRunCGIAuthIntfSvr V1.18 B20190404
    suc_msg = ip_already_online_error
    sysver = 1.01.20190404
    username = 202280506216
    wallet_balance = 0
[-] 尝试完毕，等待 20s...


=== 尝试候选: md5(password+challenge) | password_mode=0 ===
[*] get_challenge 响应: jQuery2891479218034274_1759454641260({"challenge":"00a8ceaf5fc52e491d50bde5a630785063b7a787d209a83784659a737e8a2c7a","client_ip":"10.21.64.82","ecode"...
[*] fresh challenge = 00a8ceaf5fc52e491d50bde5a630785063b7a787d209a83784659a737e8a2c7a
[*] hmd5_hex = 320abe0011768437fa2711e2246d3c66
[info raw] {"username":"202280506216","password":"","ip":"10.21.64.82","acid":"5","enc_ver":"srun_bx1"}
[info field preview] {SRBX1}EzS0BTUFYxA1olmlSrr+MyXNhdlzavu2vsSt/K+SUa4waSpe805csDdre8s4xUhW5Q7JzjnEjnU+96L+9F/PFIUM5ajxr...
[*] chksum = 39b80f41008f3d67de70706755e23a45f1df2abd
[*] 请求参数:
    callback = jQuery1558434516867047_1759454641276
    action = login
    username = 202280506216
    password = {MD5}320abe0011768437fa2711e2246d3c66
    ac_id = 5
    ip = 10.21.64.82
    info = {SRBX1}EzS0BTUFYxA1olmlSrr+MyXNhdlzavu2vsSt/K+SUa4waSpe805csDdre8s4xUhW5Q7JzjnEjnU+96L+9F/PFIUM5ajxrULMzeKJ4jQKCMkxjOahmAguYUfTv88yCIzX
    chksum = 39b80f41008f3d67de70706755e23a45f1df2abd
    n = 200
    type = 1
    _ = 1759454641276
HTTP 200 响应前 200 字符:
jQuery1558434516867047_1759454641276({"ServerFlag":0,"ServicesIntfServerIP":"0.0.0.0","ServicesIntfServerPort":"8001","access_token":"00a8ceaf5fc52e491d50bde5a630785063b7a787d209a83784659a737e8a2c7a",
[*] 返回 JSON 解析结果:
    ServerFlag = 0
    ServicesIntfServerIP = 0.0.0.0
    ServicesIntfServerPort = 8001
    access_token = 00a8ceaf5fc52e491d50bde5a630785063b7a787d209a83784659a737e8a2c7a
    checkout_date = 0
    client_ip = 10.21.64.82
    ecode = 0
    error = ok
    error_msg =
    online_ip = 10.21.64.82
    real_name =
    remain_flux = 0
    remain_times = 0
    res = ok
    srun_ver = SRunCGIAuthIntfSvr V1.18 B20190404
    suc_msg = ip_already_online_error
    sysver = 1.01.20190404
    username = 202280506216
    wallet_balance = 0
[-] 尝试完毕，等待 20s...


=== 尝试候选: md5(password+challenge) | password_mode=1 ===
[*] get_challenge 响应: jQuery9096362220036035_1759454661311({"challenge":"e03807a5c68fb527f0afd3feddf797a65baeb968d9026880395f08f60f3687b3","client_ip":"10.21.64.82","ecode"...
[*] fresh challenge = e03807a5c68fb527f0afd3feddf797a65baeb968d9026880395f08f60f3687b3
[*] hmd5_hex = 4a4f886cbfc9f6639ff2fb903eaa40aa
[info raw] {"username":"202280506216","password":"HTYLY223","ip":"10.21.64.82","acid":"5","enc_ver":"srun_bx1"}
[info field preview] {SRBX1}Du1FKt3zW4k9Gx7QPBIzmi8jauMrnYOJN3P+DVP0HMWkDsyFXFWDpW94uojXrcVC9Ok3fWPD2GRECGaxXB67LXHpSglOY...
[*] chksum = 2f869e291c4d53e728f1596bd24f804216655816
[*] 请求参数:
    callback = jQuery2355852929006940_1759454661324
    action = login
    username = 202280506216
    password = {MD5}4a4f886cbfc9f6639ff2fb903eaa40aa
    ac_id = 5
    ip = 10.21.64.82
    info = {SRBX1}Du1FKt3zW4k9Gx7QPBIzmi8jauMrnYOJN3P+DVP0HMWkDsyFXFWDpW94uojXrcVC9Ok3fWPD2GRECGaxXB67LXHpSglOYrnM+i4QE3uqQ8kXTa3RkfQbKHTAXAaGXw4xbBbkshkXkqH=
    chksum = 2f869e291c4d53e728f1596bd24f804216655816
    n = 200
    type = 1
    _ = 1759454661324
HTTP 200 响应前 200 字符:
jQuery2355852929006940_1759454661324({"ServerFlag":0,"ServicesIntfServerIP":"0.0.0.0","ServicesIntfServerPort":"8001","access_token":"e03807a5c68fb527f0afd3feddf797a65baeb968d9026880395f08f60f3687b3",
[*] 返回 JSON 解析结果:
    ServerFlag = 0
    ServicesIntfServerIP = 0.0.0.0
    ServicesIntfServerPort = 8001
    access_token = e03807a5c68fb527f0afd3feddf797a65baeb968d9026880395f08f60f3687b3
    checkout_date = 0
    client_ip = 10.21.64.82
    ecode = 0
    error = ok
    error_msg =
    online_ip = 10.21.64.82
    real_name =
    remain_flux = 0
    remain_times = 0
    res = ok
    srun_ver = SRunCGIAuthIntfSvr V1.18 B20190404
    suc_msg = ip_already_online_error
    sysver = 1.01.20190404
    username = 202280506216
    wallet_balance = 0
[-] 尝试完毕，等待 20s...


=== 尝试候选: md5(password+challenge) | password_mode=2 ===
[*] get_challenge 响应: jQuery5588238452674211_1759454681357({"challenge":"e03807a5c68fb527f0afd3feddf797a65baeb968d9026880395f08f60f3687b3","client_ip":"10.21.64.82","ecode"...
[*] fresh challenge = e03807a5c68fb527f0afd3feddf797a65baeb968d9026880395f08f60f3687b3
[*] hmd5_hex = 4a4f886cbfc9f6639ff2fb903eaa40aa
[info raw] {"username":"202280506216","password":"{MD5}ac3850c4d33ad101d7c38d8ff02661c6","ip":"10.21.64.82","acid":"5","enc_ver":"srun_bx1"}
[info field preview] {SRBX1}BoMC4X8EaLLCHERMYmEMZJPta9mp+iOlSJd0ZDLgahPzoUHzF7PAbHOk+80wNrNDfhudlpw4VTFQNdL2NGfmgzI9Teql0...
[*] chksum = c9e0298ac88a25d2a7203730f3d985051d80274f
[*] 请求参数:
    callback = jQuery2626826986514979_1759454681384
    action = login
    username = 202280506216
    password = {MD5}4a4f886cbfc9f6639ff2fb903eaa40aa
    ac_id = 5
    ip = 10.21.64.82
    info = {SRBX1}BoMC4X8EaLLCHERMYmEMZJPta9mp+iOlSJd0ZDLgahPzoUHzF7PAbHOk+80wNrNDfhudlpw4VTFQNdL2NGfmgzI9Teql0zVuB3BbZvGl+BHidPpo9/E/zoLXH3KciFmDNKLVre5uf+uF+xdkveEBumWbvvNa6PGFbwZCpgMoJm8VWpAWNQCehL==
    chksum = c9e0298ac88a25d2a7203730f3d985051d80274f
    n = 200
    type = 1
    _ = 1759454681384
HTTP 200 响应前 200 字符:
jQuery2626826986514979_1759454681384({"ServerFlag":0,"ServicesIntfServerIP":"0.0.0.0","ServicesIntfServerPort":"8001","access_token":"e03807a5c68fb527f0afd3feddf797a65baeb968d9026880395f08f60f3687b3",
[*] 返回 JSON 解析结果:
    ServerFlag = 0
    ServicesIntfServerIP = 0.0.0.0
    ServicesIntfServerPort = 8001
    access_token = e03807a5c68fb527f0afd3feddf797a65baeb968d9026880395f08f60f3687b3
    checkout_date = 0
    client_ip = 10.21.64.82
    ecode = 0
    error = ok
    error_msg =
    online_ip = 10.21.64.82
    real_name =
    remain_flux = 0
    remain_times = 0
    res = ok
    srun_ver = SRunCGIAuthIntfSvr V1.18 B20190404
    suc_msg = ip_already_online_error
    sysver = 1.01.20190404
    username = 202280506216
    wallet_balance = 0
[-] 尝试完毕，等待 20s...
ChatGPT 说：

👌 看输出结果，核心问题已经清楚了：

第一组 (password_mode=0)

info 里密码是空串，结果报 E2553: Password is error.

说明这种模式不对。

第二组 (password_mode=1)

info 里用明文密码 "HTYLY223"。

返回 JSON：error=ok，suc_msg=login_ok ✅

说明这一组是 正确的组合，已经成功登录。

其它组合 (password_mode=2、不同 hmd5 算法)

全部都返回 error=ok，但 suc_msg=ip_already_online_error。

这说明在 password_mode=1 时已经成功上线了，再尝试其它模式就提示“IP 已在线”。

🔑 总结

烟台大学 SRun 的正确登录方式：

hmd5 = md5(password)

password_mode = 1 (明文密码放在 info 里)

password 参数还是 {MD5}xxxxxx，但 info 里必须带明文。

这就是为什么第一组失败（info 里没密码），第二组成功（info 里带明文密码），后面全部报“已在线”。

🚀 下一步

如果你要做一个稳定的脚本，就不需要每次跑 12 种组合了，直接写死用这一组即可：

hmd5_hex = hashlib.md5(password.encode()).hexdigest()
info_field = make_info(username, ip, ac_id, challenge, 1, password)  # password_mode=1


要不要我帮你整理一个 精简版 ytu_login.py，去掉所有候选，只保留正确模式，然后加个 keep-alive（保持在线）循环？

您说：
那不对呀 第二组 (password_mode=1)

info 里用明文密码 "HTYLY223"。

返回 JSON：error=ok，suc_msg=login_ok ✅

说明这一组是 正确的组合，已经成功登录。 为什么我的电脑没有登录 我现在和你对话是我通过网页登录后的
ChatGPT 说：

嗯，这里就有个关键细节要分清楚了。
从你贴的 第二组 (password_mode=1) 返回 JSON 来看，Portal 确实给了：

error = ok
suc_msg = login_ok
ploy_msg = E0000: Login is successful.


这意味着 网关后台已经接受了认证请求，并且把状态标记成「登录成功」。

但是你说「电脑没有上网，还是靠网页登录」，这通常有几个原因：

🔍 可能的原因

成功登录的 IP 不一致

Portal 是按「IP 地址」来绑定上线的。

你脚本里填的 IP 是 10.21.64.82。

如果这不是你当前系统网卡分配的 IP，而是写死的，Portal 只是给这个 IP 建立了会话，但你的实际流量走的另一个 IP，自然没网。
👉 用 ipconfig (Windows) / ifconfig (Linux/Mac) 看你真实内网 IP，要和脚本里保持一致。

多网卡 / 虚拟网卡冲突

比如 VMware、VirtualBox、VPN 驱动都会占用虚拟网卡。

Portal 会随机选择一个 IP 给你，结果你登录的是虚拟网卡的 IP，主网卡没网。

浏览器登录时，Portal 返回的 IP 不同

你网页登录能上网，说明网页登录时 Portal 识别的 client_ip 和脚本里用的不一样。

你的调试输出里 client_ip = 10.21.64.82，你确认一下网页登录时返回的 JSON 里 client_ip 是不是同一个？

Portal 成功登录，但系统 DNS/路由没刷新

一般在 Linux/Windows 上可能需要清除缓存：

Windows: ipconfig /flushdns

Linux: sudo systemctl restart NetworkManager 或重新拨 DHCP。

但通常不需要手动刷新，除非网络环境比较特殊。

✅ 建议你做的检查

在网页登录状态下，打开浏览器调试台（F12 → 网络），看看登录成功的响应 JSON 里的 client_ip，和脚本跑出来的 client_ip 是否一致。

如果不一致，把脚本里的 IP 改成真实网卡 IP。

如果一致但还是没网，试试把网页登录下线，再运行脚本，看能否直接上网。

要不要我帮你在 ytu_debug_auto_v3_fixed.py 里加一段 自动获取本机 IP 的逻辑（而不是手动输入 10.21.xx.xx），这样就不会出现「登录成功但错 IP」的情况？

您说：
在 ytu_debug_auto_v3_fixed.py 里加一段 自动获取本机 IP 的逻辑   节点类型  . . . . . . . . . . . . : 混合
   IP 路由已启用 . . . . . . . . . . : 否
   WINS 代理已启用 . . . . . . . . . : 否
   DNS 后缀搜索列表  . . . . . . . . : mole-stairs.ts.net

未知适配器 Tailscale:

   连接特定的 DNS 后缀 . . . . . . . : mole-stairs.ts.net
   描述. . . . . . . . . . . . . . . : Tailscale Tunnel
   物理地址. . . . . . . . . . . . . :
   DHCP 已启用 . . . . . . . . . . . : 否
   自动配置已启用. . . . . . . . . . : 是
   IPv6 地址 . . . . . . . . . . . . : fd7a:115c:a1e0::7301:e05e(首选)
   本地链接 IPv6 地址. . . . . . . . : fe80::7c2c:1810:b136:3aa0%6(首选)
   IPv4 地址 . . . . . . . . . . . . : 100.68.1.1(首选)
   子网掩码  . . . . . . . . . . . . : 255.255.255.255
   默认网关. . . . . . . . . . . . . :
   TCPIP 上的 NetBIOS  . . . . . . . : 已禁用
   连接特定的 DNS 后缀搜索列表:
                                       mole-stairs.ts.net

无线局域网适配器 本地连接* 1:

   媒体状态  . . . . . . . . . . . . : 媒体已断开连接
   连接特定的 DNS 后缀 . . . . . . . :
   描述. . . . . . . . . . . . . . . : Microsoft Wi-Fi Direct Virtual Adapter
   物理地址. . . . . . . . . . . . . : C4-75-AB-E0-4A-9E
   DHCP 已启用 . . . . . . . . . . . : 是
   自动配置已启用. . . . . . . . . . : 是

无线局域网适配器 本地连接* 10:

   媒体状态  . . . . . . . . . . . . : 媒体已断开连接
   连接特定的 DNS 后缀 . . . . . . . :
   描述. . . . . . . . . . . . . . . : Microsoft Wi-Fi Direct Virtual Adapter #2
   物理地址. . . . . . . . . . . . . : C6-75-AB-E0-4A-9D
   DHCP 已启用 . . . . . . . . . . . : 否
   自动配置已启用. . . . . . . . . . : 是

以太网适配器 VMware Network Adapter VMnet1:

   连接特定的 DNS 后缀 . . . . . . . :
   描述. . . . . . . . . . . . . . . : VMware Virtual Ethernet Adapter for VMnet1
   物理地址. . . . . . . . . . . . . : 00-50-56-C0-00-01
   DHCP 已启用 . . . . . . . . . . . : 否
   自动配置已启用. . . . . . . . . . : 是
   本地链接 IPv6 地址. . . . . . . . : fe80::371b:cb5b:958c:2f92%5(首选)
   IPv4 地址 . . . . . . . . . . . . : 192.168.72.1(首选)
   子网掩码  . . . . . . . . . . . . : 255.255.255.0
   默认网关. . . . . . . . . . . . . :
   DHCPv6 IAID . . . . . . . . . . . : 855658582
   DHCPv6 客户端 DUID  . . . . . . . : 00-01-00-01-2F-4D-BF-A5-C4-75-AB-E0-4A-9D
   TCPIP 上的 NetBIOS  . . . . . . . : 已启用

以太网适配器 VMware Network Adapter VMnet8:

   连接特定的 DNS 后缀 . . . . . . . :
   描述. . . . . . . . . . . . . . . : VMware Virtual Ethernet Adapter for VMnet8
   物理地址. . . . . . . . . . . . . : 00-50-56-C0-00-08
   DHCP 已启用 . . . . . . . . . . . : 否
   自动配置已启用. . . . . . . . . . : 是
   本地链接 IPv6 地址. . . . . . . . : fe80::19a0:ab23:7990:9def%22(首选)
   IPv4 地址 . . . . . . . . . . . . : 192.168.124.1(首选)
   子网掩码  . . . . . . . . . . . . : 255.255.255.0
   默认网关. . . . . . . . . . . . . :
   DHCPv6 IAID . . . . . . . . . . . : 872435798
   DHCPv6 客户端 DUID  . . . . . . . : 00-01-00-01-2F-4D-BF-A5-C4-75-AB-E0-4A-9D
   TCPIP 上的 NetBIOS  . . . . . . . : 已启用

无线局域网适配器 WLAN:

   连接特定的 DNS 后缀 . . . . . . . :
   描述. . . . . . . . . . . . . . . : Intel(R) Wi-Fi 6 AX200 160MHz
   物理地址. . . . . . . . . . . . . : C4-75-AB-E0-4A-9D
   DHCP 已启用 . . . . . . . . . . . : 是
   自动配置已启用. . . . . . . . . . : 是
   IPv6 地址 . . . . . . . . . . . . : 2001:250:580b:b92:7953:696f:641f:f5e6(首选)
   临时 IPv6 地址. . . . . . . . . . : 2001:250:580b:b92:fc08:8b3e:510a:6ae4(首选)
   本地链接 IPv6 地址. . . . . . . . : fe80::862b:fd30:34b4:f669%12(首选)
   IPv4 地址 . . . . . . . . . . . . : 10.21.64.82(首选)
   子网掩码  . . . . . . . . . . . . : 255.255.0.0
   获得租约的时间  . . . . . . . . . : 2025年10月3日 8:12:30
   租约过期的时间  . . . . . . . . . : 2025年10月3日 18:12:30
   默认网关. . . . . . . . . . . . . : fe80::3ef5:ccff:fe31:c802%12
                                       10.21.255.254
   DHCP 服务器 . . . . . . . . . . . : 10.21.255.254
   DHCPv6 IAID . . . . . . . . . . . : 96761259
   DHCPv6 客户端 DUID  . . . . . . . : 00-01-00-01-2F-4D-BF-A5-C4-75-AB-E0-4A-9D
   DNS 服务器  . . . . . . . . . . . : 218.201.96.130
                                       202.194.116.66
   TCPIP 上的 NetBIOS  . . . . . . . : 已启用

以太网适配器 蓝牙网络连接:

   媒体状态  . . . . . . . . . . . . : 媒体已断开连接
   连接特定的 DNS 后缀 . . . . . . . :
   描述. . . . . . . . . . . . . . . : Bluetooth Device (Personal Area Network)
   物理地址. . . . . . . . . . . . . : C4-75-AB-E0-4A-A1
   DHCP 已启用 . . . . . . . . . . . : 是
ChatGPT 说：

看到了，你机器有很多虚拟网卡（VMware、Tailscale、蓝牙），但真正能上校园网的是 无线网卡 WLAN (Intel Wi-Fi 6 AX200)，它的 IPv4 地址是 10.21.64.82。
脚本里手动输入这个没问题，但为了避免输错，我们可以让脚本自动获取。

在 Python 里有几个办法：

跨平台最稳：用 netifaces 库找出带 10.x.x.x 的地址。

内置库方案：用 socket，配合一个假连接，获取出站 IP。

我建议直接在 ytu_debug_auto_v3_fixed.py 里加一个函数：

import socket

def get_local_ip():
    """
    自动探测当前实际出口 IP (IPv4)
    - 原理：向一个外部地址发 UDP，取内核路由选择的源 IP
    """
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # 随便连一个公网 IP，端口不用真的连通
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
        s.close()
        return ip
    except Exception as e:
        print(f"[!] 自动获取IP失败: {e}")
        return None


然后在 main() 里，把原来输入 IP 的地方改成：

    auto_ip = get_local_ip()
    ip = input(f"ip (default {auto_ip}) > ").strip() or auto_ip


这样脚本会自动识别你电脑当前实际出口 IP（比如 10.21.64.82），如果用户直接回车，就用这个 IP，不需要自己查了。

要不要我直接帮你把这个逻辑嵌到 ytu_debug_auto_v3_fixed.py 完整贴一版？

您说：
嵌到 ytu_debug_auto_v3_fixed.py 完整贴
ChatGPT 说：

好的 ✅，我给你整理一份 完整版 ytu_debug_auto_v3_fixed.py，里面已经包含：

get_xencode（深澜算法）

get_base64（自定义 64 表）

get_sha1（用来算 chksum）

get_local_ip()（自动获取本机出口 IP）

详细调试打印（方便你把参数和响应发给我看）

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import hashlib
import json
import math
import socket
import time
import requests

# ======================================================
# 自定义 Base64 表
# ======================================================
_PADCHAR = "="
_ALPHA = "LVoJPiCN2R8G90yg+hmFHuacZ1OWMnrsSTXkYpUq/3dlbfKwv6xztjI7DeBE45QA"

def _getbyte(s, i):
    x = ord(s[i])
    if x > 255:
        raise ValueError("INVALID_CHARACTER_ERR: DOM Exception 5")
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

# ======================================================
# SHA1
# ======================================================
def get_sha1(value: str) -> str:
    return hashlib.sha1(value.encode()).hexdigest()

# ======================================================
# xEncode
# ======================================================
def ordat(msg, idx):
    if len(msg) > idx:
        return ord(msg[idx])
    return 0

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
    if key:
        return "".join(msg)[0:ll]
    return "".join(msg)

def get_xencode(msg, key):
    if msg == "":
        return ""
    pwd = sencode(msg, True)
    pwdk = sencode(key, False)
    if len(pwdk) < 4:
        pwdk = pwdk + [0] * (4 - len(pwdk))
    n = len(pwd) - 1
    z = pwd[n]
    y = pwd[0]
    c = 0x86014019 | 0x183639A0
    m = 0
    e = 0
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

# ======================================================
# 获取本机出口 IP
# ======================================================
def get_local_ip():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
        s.close()
        return ip
    except Exception as e:
        print(f"[!] 自动获取IP失败: {e}")
        return None

# ======================================================
# 生成 info
# ======================================================
def make_info(username, ip, ac_id, challenge, password_mode, password):
    if password_mode == 0:
        pw = ""
    elif password_mode == 1:
        pw = password
    else:
        pw = "{MD5}" + hashlib.md5(password.encode()).hexdigest()

    raw = {
        "username": username,
        "password": pw,
        "ip": ip,
        "acid": ac_id,
        "enc_ver": "srun_bx1",
    }
    raw_json = json.dumps(raw, separators=(",", ":"))
    encoded = get_xencode(raw_json, challenge)
    info_field = "{SRBX1}" + get_base64(encoded)

    print(f"[info raw] {raw_json}")
    print(f"[info field preview] {info_field[:80]}...")

    return info_field

# ======================================================
# 主程序
# ======================================================
def main():
    username = input("username > ").strip()
    password = input("password > ").strip()
    ac_id = input("ac_id (default 1) > ").strip() or "1"

    auto_ip = get_local_ip()
    ip = input(f"ip (default {auto_ip}) > ").strip() or auto_ip

    print(f"[DEBUG] 使用 IP: {ip}")

    # 请求 challenge
    url_challenge = f"http://10.21.255.253/cgi-bin/get_challenge?username={username}&ip={ip}"
    res = requests.get(url_challenge).text
    print(f"[challenge raw] {res}")
    try:
        challenge = json.loads(res.split("(", 1)[1].split(")", 1)[0])["challenge"]
    except Exception as e:
        print(f"[!] challenge 解析失败: {e}")
        return

    print(f"[challenge] {challenge}")

    # 正确模式：hmd5 = md5(password), password_mode=1
    hmd5_hex = hashlib.md5(password.encode()).hexdigest()
    info_field = make_info(username, ip, ac_id, challenge, 1, password)

    chkstr = (
        challenge
        + username
        + challenge
        + hmd5_hex
        + challenge
        + ac_id
        + challenge
        + ip
        + challenge
        + "200"
        + challenge
        + "1"
        + challenge
        + info_field
    )
    chksum = get_sha1(chkstr)

    url_login = (
        f"http://10.21.255.253/cgi-bin/srun_portal?"
        f"callback=jQuery1124000000000000&action=login&username={username}"
        f"&password={{MD5}}{hmd5_hex}&ac_id={ac_id}&ip={ip}&info={info_field}"
        f"&chksum={chksum}&n=200&type=1&os=Windows+10&name=Windows&double_stack=0&_={int(time.time()*1000)}"
    )

    print(f"[login url] {url_login}")

    res_login = requests.get(url_login).text
    print(f"[login raw] {res_login}")

if __name__ == "__main__":
    main()


这样运行的时候：

它会自动探测你当前出口 IP（比如 10.21.64.82），显示出来。

如果你直接回车，就用探测到的，不用自己查。

所有关键字段（info raw / info field / challenge / chksum / login url / 返回 JSON）都会打印出来。

要不要我再给你加一个「保持在线」循环（比如每隔 5 分钟发个心跳包），这样就不用担心掉线了？

您说：
我的登录网页是http://202.194.116.116/srun_portal_success?ac_id=5&theme=basic1&srun_domain=
出口网关是地链接 IPv6 地址. . . . . . . . : fe80::862b:fd30:34b4:f669%12(首选)
   IPv4 地址 . . . . . . . . . . . . : 10.21.64.82(首选)
   子网掩码  . . . . . . . . . . . . : 255.255.0.0
   获得租约的时间  . . . . . . . . . : 2025年10月3日 8:12:30
   租约过期的时间  . . . . . . . . . : 2025年10月3日 19:22:27
   默认网关. . . . . . . . . . . . . : fe80::3ef5:ccff:fe31:c802%12
                                       10.21.255.254
   DHCP 服务器 . . . . . . . . . . . : 10.21.255.254
你写对了吗
ChatGPT 说：

你这个反馈非常关键 ✅。我之前写的版本默认使用了 http://10.21.255.253/cgi-bin/ 作为 portal 地址，其实应该改成 你网页登录时使用的网关地址。

从你提供的信息来看：

你的网页登录 URL 是：

http://202.194.116.116/srun_portal_success?ac_id=5&theme=basic1&srun_domain=


👉 说明 portal 主机是 202.194.116.116。

你的 默认网关 IPv4 是 10.21.255.254，公网 portal 域名/地址其实就映射到这个网关（或者直接走公网 IP 202.194.116.116）。

登录时 ac_id=5（不是我之前写的 1），所以参数必须对应修改。

✅ 你应该改的地方

在脚本里把：

url_challenge = f"http://10.21.255.253/cgi-bin/get_challenge?..."
url_login = f"http://10.21.255.253/cgi-bin/srun_portal?... "


换成：

PORTAL_HOST = "202.194.116.116"

url_challenge = f"http://{PORTAL_HOST}/cgi-bin/get_challenge?username={username}&ip={ip}"
url_login = (
    f"http://{PORTAL_HOST}/cgi-bin/srun_portal?"
    f"callback=jQuery1124000000000000&action=login&username={username}"
    f"&password={{MD5}}{hmd5_hex}&ac_id={ac_id}&ip={ip}&info={info_field}"
    f"&chksum={chksum}&n=200&type=1&os=Windows+10&name=Windows&double_stack=0&_={int(time.time()*1000)}"
)


同时，把默认的 ac_id 改成 5：

ac_id = input("ac_id (default 5) > ").strip() or "5"

🔎 确认点

你的 WLAN 网卡 IP 是 10.21.64.82 ✅（这个由 DHCP 分配，脚本里自动获取已经没问题了）。

你的 portal 主机就是 202.194.116.116，所以 challenge/login 都要打到这个地址。

登录参数里 ac_id 必须是 5，否则认证不通过。

要不要我直接帮你把 ytu_debug_auto_v3_fixed.py 里的 portal 地址和 ac_id 默认值改好，然后贴一版「烟台大学专用」的最终脚本给你？

您说：
ytu_debug_auto_v3_fixed.py
ChatGPT 说：

明白啦 ✅，我给你整理一份「烟台大学专用」的 ytu_debug_auto_v3_fixed.py，已经改好了：

Portal 地址：202.194.116.116

默认 ac_id：5

自动获取本机出口 IP

打印所有关键参数和返回结果

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import hashlib
import json
import math
import socket
import time
import requests

# ======================================================
# 自定义 Base64 表
# ======================================================
_PADCHAR = "="
_ALPHA = "LVoJPiCN2R8G90yg+hmFHuacZ1OWMnrsSTXkYpUq/3dlbfKwv6xztjI7DeBE45QA"

def _getbyte(s, i):
    x = ord(s[i])
    if x > 255:
        raise ValueError("INVALID_CHARACTER_ERR: DOM Exception 5")
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

# ======================================================
# SHA1
# ======================================================
def get_sha1(value: str) -> str:
    return hashlib.sha1(value.encode()).hexdigest()

# ======================================================
# xEncode
# ======================================================
def ordat(msg, idx):
    if len(msg) > idx:
        return ord(msg[idx])
    return 0

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
    if key:
        return "".join(msg)[0:ll]
    return "".join(msg)

def get_xencode(msg, key):
    if msg == "":
        return ""
    pwd = sencode(msg, True)
    pwdk = sencode(key, False)
    if len(pwdk) < 4:
        pwdk = pwdk + [0] * (4 - len(pwdk))
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

# ======================================================
# 获取本机出口 IP
# ======================================================
def get_local_ip():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
        s.close()
        return ip
    except Exception as e:
        print(f"[!] 自动获取IP失败: {e}")
        return None

# ======================================================
# 生成 info
# ======================================================
def make_info(username, ip, ac_id, challenge, password_mode, password):
    if password_mode == 0:
        pw = ""
    elif password_mode == 1:
        pw = password
    else:
        pw = "{MD5}" + hashlib.md5(password.encode()).hexdigest()

    raw = {
        "username": username,
        "password": pw,
        "ip": ip,
        "acid": ac_id,
        "enc_ver": "srun_bx1",
    }
    raw_json = json.dumps(raw, separators=(",", ":"))
    encoded = get_xencode(raw_json, challenge)
    info_field = "{SRBX1}" + get_base64(encoded)

    print(f"[info raw] {raw_json}")
    print(f"[info field preview] {info_field[:80]}...")

    return info_field

# ======================================================
# 主程序
# ======================================================
def main():
    PORTAL_HOST = "202.194.116.116"   # 烟台大学 portal
    username = input("username > ").strip()
    password = input("password > ").strip()
    ac_id = input("ac_id (default 5) > ").strip() or "5"

    auto_ip = get_local_ip()
    ip = input(f"ip (default {auto_ip}) > ").strip() or auto_ip

    print(f"[DEBUG] 使用 IP: {ip}")

    # 请求 challenge
    url_challenge = f"http://{PORTAL_HOST}/cgi-bin/get_challenge?username={username}&ip={ip}"
    res = requests.get(url_challenge).text
    print(f"[challenge raw] {res}")
    try:
        challenge = json.loads(res.split("(", 1)[1].split(")", 1)[0])["challenge"]
    except Exception as e:
        print(f"[!] challenge 解析失败: {e}")
        return

    print(f"[challenge] {challenge}")

    # 正确模式：hmd5 = md5(password), password_mode=1
    hmd5_hex = hashlib.md5(password.encode()).hexdigest()
    info_field = make_info(username, ip, ac_id, challenge, 1, password)

    chkstr = (
        challenge
        + username
        + challenge
        + hmd5_hex
        + challenge
        + ac_id
        + challenge
        + ip
        + challenge
        + "200"
        + challenge
        + "1"
        + challenge
        + info_field
    )
    chksum = get_sha1(chkstr)

    url_login = (
        f"http://{PORTAL_HOST}/cgi-bin/srun_portal?"
        f"callback=jQuery1124000000000000&action=login&username={username}"
        f"&password={{MD5}}{hmd5_hex}&ac_id={ac_id}&ip={ip}&info={info_field}"
        f"&chksum={chksum}&n=200&type=1&os=Windows+10&name=Windows&double_stack=0&_={int(time.time()*1000)}"
    )

    print(f"[login url] {url_login}")

    res_login = requests.get(url_login).text
    print(f"[login raw] {res_login}")

if __name__ == "__main__":
    main()


👉 这版就是适配你网页登录时看到的 202.194.116.116 + ac_id=5。

运行步骤：

填用户名、密码，直接回车默认 ac_id=5 和自动获取 IP。

会打印 challenge / info / login url / portal 响应 JSON。

要不要我帮你再加个「心跳保持在线」模块（每 5 分钟发一次 srun_portal?action=ping），这样不会被网关踢下线？