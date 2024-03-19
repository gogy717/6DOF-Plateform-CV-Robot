from ctypes import *
import ctypes
import time

# 假设DLL已正确加载，这里直接使用之前的方式
pRSS6RBT_Inverse = CDLL("./RSS6RBT_InverseDLL.dll")

# 打开文件用于写入结果s
File = open('./specific_target_test.txt', 'w')
File.write("XP    YP    ZP    YAW    PITCH    ROLL    M1    M2    M3    M4    M5    M6\n")

# 创建用于接收逆向运动学结果的数组
pInversResult = (c_double*6)()

# 设置目标位置和姿态
XP = 0  # 示例目标位置X
YP = 0   # 示例目标位置Y
ZP = 168+20  # 示例目标位置Z
YAW = 0  # 示例目标姿态Yaw
PITCH = 0  # 示例目标姿态Pitch
ROLL = 0  # 示例目标姿态Roll

# 调用逆向运动学函数
ret = pRSS6RBT_Inverse.InK6RSS(c_double(XP), c_double(YP), c_double(ZP), c_double(YAW), c_double(PITCH), c_double(ROLL), pointer(pInversResult))

# 检查结果是否有效
if not all(angle == -360 for angle in pInversResult) and ret != 0:
    # 写入目标位置、姿态和计算得到的关节角度
    result_line = f"{XP}    {YP}    {ZP}    {YAW}    {PITCH}    {ROLL}    " + "    ".join(str(angle) for angle in pInversResult) + "\n"
    print([str(angle) for angle in pInversResult])
    File.write(result_line)
else:
    print("逆向运动学计算失败或结果无效")

File.close()


