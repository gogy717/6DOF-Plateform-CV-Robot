#ifndef TCPIP_H  // 防止头文件被重复包含
#define TCPIP_H

#include <WiFi.h>  // 包含ESP32 WiFi库
extern WiFiServer server;

// 声明tcpip_setup函数
void tcpip_setup(const char* ssid, const char* password);

#endif // TCPIP_H
