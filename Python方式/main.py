from ctypes import *
import ctypes
import time

# ----------以下四种加载DLL方式皆可-----------------
# pRSS6RBT_Inverse = WinDLL("./RSS6RBT_InverseDLL.dll")
# pRSS6RBT_Inverse = windll.LoadLibrary("./RSS6RBT_InverseDLL.dll")
# pRSS6RBT_Inverse = cdll.LoadLibrary("./RSS6RBT_InverseDLL.dll")
# pRSS6RBT_Inverse = CDLL("./RSS6RBT_InverseDLL.dll")

# File = open('./test.txt', 'a')
# File.write("XP    YP    ZP    YAW    PITCH    ROLL    M1    M2    M3    M4    M5    M6\n")

pInversResult = (c_double*6)()
I =0
J =0

XP = +10
YP = -0
ZP = 168+20
YAW = 5
PITCH = 0
ROLL = 0
print(pInversResult[0], pInversResult[1], pInversResult[2], pInversResult[3], pInversResult[4], pInversResult[5])
# ret = pRSS6RBT_Inverse.InK6RSS(c_double(XP), c_double(YP), c_double(ZP), c_double(YAW), c_double(PITCH), c_double(ROLL), pointer(pInversResult))
# print(ret)S

pRSS6RBT_Inverse = cdll.LoadLibrary('./InK6RSSV1.so')

print(pRSS6RBT_Inverse.InK6RSS(c_double(XP), c_double(YP), c_double(ZP), c_double(YAW), c_double(PITCH), c_double(ROLL), pointer(pInversResult)) )

print(pInversResult[0], pInversResult[1], pInversResult[2], pInversResult[3], pInversResult[4], pInversResult[5])
init_an = [48,130,50,135,55,128]
targetangle = []
for i in range(0,6):
    pInversResult[i] = -pInversResult[i]
    print(pInversResult[i])
    if i == 0 or i == 2 or i == 4:
        print(i)
        angle =  init_an[i] + pInversResult[i] 
    else:
        angle =  init_an[i] - pInversResult[i] 
    targetangle.append(int(angle))
print(targetangle)



import socket
# 单片机的IP地址和端口号
ESP32_IP = '192.168.1.105' # 请替换为您的ESP32的IP地址
PORT = 80 # 端口号，根据您的设置可能需要更改

def convert_angle_to_string(angles):
    return 'A'+','.join(str(angle) for angle in angles)+'\r'

# 创建一个socket对象
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 连接到服务器
s.connect((ESP32_IP, PORT))

angle_data=convert_angle_to_string(targetangle)

# 发送数据
s.sendall(angle_data.encode())

# 关闭连接
s.close()
