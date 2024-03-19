import socket

# 单片机的IP地址和端口号
ESP32_IP = '192.168.1.112' # 请替换为您的ESP32的IP地址
PORT = 80 # 端口号，根据您的设置可能需要更改

# 创建一个socket对象
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 连接到服务器
s.connect((ESP32_IP, PORT))

# 发送数据
s.sendall("Hello, ESP32!\r".encode())

# 关闭连接
s.close()
