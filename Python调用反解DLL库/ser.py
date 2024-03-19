import time
import threading
import serial
from ctypes import *


pRSS6RBT_Inverse = CDLL("./RSS6RBT_InverseDLL.dll")
pInversResult = (c_double*6)()

serialPort = "COM3"  # 串口
baudRate = 115200  # 波特率
ser = serial.Serial(serialPort, baudRate, timeout=2)  # 打开串口
def read_from_port(ser):
    while True:
        reading = ser.readline().decode()
        if reading != "":
            print(reading)
Read = threading.Thread(target=read_from_port, args=(ser,))


def write_to_port(ser):
    while True:
        ser.write(b"Hello, world!\n")
        time.sleep(10)

Write = threading.Thread(target=write_to_port, args=(ser,))

def reverse_kinematics(XP, YP, ZP, YAW, PITCH, ROLL):





def main():
    Read.start()
    Write.start()
    Read.join()
    Write.join()
    ser.close()

if __name__ == "__main__":
    main()

