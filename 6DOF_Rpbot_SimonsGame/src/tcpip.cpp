#include "tcpip.h"



void tcpip_setup(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  server.begin(); // 启动服务器
  // 打印ESP32的IP地址
  Serial.println(WiFi.localIP());
}

