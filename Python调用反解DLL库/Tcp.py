import socket

# 单片机的IP地址和端口号
ESP32_IP = '192.168.43.13' # 请替换为您的ESP32的IP地址
PORT = 80 # 端口号，根据您的设置可能需要更改

def convert_angle_to_string(angles):
    return 'A'+','.join(str(angle) for angle in angles)+'\r'



# 创建一个socket对象
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 连接到服务器
s.connect((ESP32_IP, PORT))


angle_list = [60, 117, 62, 122, 67, 115]   # 请替换为您的角度
angle_data=convert_angle_to_string(angle_list)

# 发送数据
s.sendall(angle_data.encode())

# 关闭连接
s.close()
