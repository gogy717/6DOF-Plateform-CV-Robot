import neopixel
from machine import Pin
import time
import urandom


from machine import Pin
import network
import esp
esp.osdebug(None)
import gc
gc.collect()
import socket


GBIO_IN = Pin(48)  # 控制信号输入引脚
LED_NUM = 1  # LED灯的数量

# class NeoPixel(pin, n, bpp=3, timing=0)
#    pin :输出引脚,可使用引脚见下文
#    n :LED灯的个数
#    bpp:
#        3:默认为3元组RGB
#        4:对于具有3种以上颜色的LED，例如RGBW像素或RGBY像素,采用4元组RGBY或RGBY像素
#    timing:默认等于0,为400KHz速率；等于1，为800KHz速率
#


def setup():
    LED = neopixel.NeoPixel(pin=GBIO_IN, n=LED_NUM, timing=1)  # 创建控制对象

    LED.fill((255, 0, 0))  # GRB填充数据(RGB顺序, 0为不亮，255为全亮)
    LED.write()  # 写入数据
    time.sleep(1)
    LED.fill((0, 255, 0))  # GRB填充数据(RGB顺序, 0为不亮，255为全亮)
    LED.write()  # 写入数据
    time.sleep(1)
    LED.fill((0, 0, 255))  # GRB填充数据(RGB顺序, 0为不亮，255为全亮)
    LED.write()  # 写入数据
    time.sleep(1)
    LED.fill((0,0,0))
    LED.write()

# 
# def socket():
#     

setup()




# while True:
#     r = urandom.randint(0, 255)
#     g = urandom.randint(0, 255)
#     b = urandom.randint(0, 255)
#     for i in range(LED_NUM):
#         LED[i] = (r, g, b)  # 依次设置LED灯珠的颜色
#         print(f"color is:{r},{g},{b}")
#         LED.write()  # 写入数据
#         time.sleep_ms(500)
# 
#     r = urandom.randint(0, 255)
#     g = urandom.randint(0, 255)
#     b = urandom.randint(0, 255)
#     for i in range(LED_NUM-1, -1, -1):
#         LED[i] = (r, g, b)  # 依次设置LED灯珠的颜色
#         LED.write()  # 写入数据
#         time.sleep_ms(500)


