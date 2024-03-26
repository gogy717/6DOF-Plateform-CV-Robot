import socket
import time
import random

# ESP32的IP地址和端口号
ESP32_IP = '192.168.43.13'  # 请替换为您的ESP32的IP地址
PORT = 80  # 端口号，根据您的设置可能需要更改

def connect_to_esp32(ip, port):
    """尝试连接到ESP32服务器."""
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.connect((ip, port))
        s.settimeout(2.0)  # 设置超时时间
        print("Connected to ESP32")
    except socket.error as e:
        print(f"Connection error: {e}")
        s = None
    return s

def send_data(sock, data):
    """向ESP32发送数据，并接收响应."""
    try:
        sock.sendall(data.encode())
        response = sock.recv(1024).decode()  # 阻塞等待响应，考虑非阻塞或超时处理
        print(f"Received: {response}")
    except socket.error as e:
        print(f"Error sending data: {e}")

def main():
    with connect_to_esp32(ESP32_IP, PORT) as sock:
        if sock is not None:
            for _ in range(10):  # 发送10次数据
                # 随机选择一个颜色并发送
                color = random.choice(['R', 'G', 'B', 'Y'])
                data = f"C{color}\r"
                print(f"Sending: {data.strip()}")
                send_data(sock, data)
                time.sleep(1)  # 模拟工作
        else:
            print("Failed to connect to ESP32.")

if __name__ == "__main__":
    main()
