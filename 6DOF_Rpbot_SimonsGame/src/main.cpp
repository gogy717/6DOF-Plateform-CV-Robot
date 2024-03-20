#include <Arduino.h>
#include "tcpip.h"
#include <Adafruit_NeoPixel.h>
#include "esp32-hal-ledc.h"

const int freq = 50; // PWM信号频率，一般为50Hz
const int resolution = 10; // 分辨率，10位意味着1024级
const int minPulseWidth = 500; // 最小脉宽，单位为微秒
const int maxPulseWidth = 2500; // 最大脉宽，单位为微秒

//1,3,5 : 55 deg ********* 2,4,6 : 135 deg
int targetAngles[6] = {48,130,50,135,55,128}; // 示例目标角度

struct ServoConfig {
    int pin;
    int channel;
};

// 定义6个舵机的配置
ServoConfig servos[6] = {
    {9, 0},  // GPIO 9,  使用LEDC通道 0
    {10, 1}, // GPIO 10, 使用LEDC通道 1
    {11, 2}, // GPIO 11, 使用LEDC通道 2
    {12, 3}, // GPIO 12, 使用LEDC通道 3
    {13, 4}, // GPIO 13, 使用LEDC通道 4
    {14, 5}  // GPIO 14, 使用LEDC通道 5
};



// function declaration
void setupServos();
void moveServo(int servoIndex, int angle);

// task declaration
void TaskMoveServo(void *parameter);
void TaskTCPSerial(void *parameter);


// user defined
const char* ssid = "kbjw"; // 替换为您的SSID
const char* password =  "qwerwsad"; // 替换为您的Wi-Fi密码
WiFiServer server(80);

int minUs = 500;
int maxUs = 2500;

// for the ESP32-S3 the GPIO pins are 1-21,35-45,47-48

#define PIN 48 // 假设WS2812B LED数据线连接到GPIO 48
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
  setupServos(); // 初始化所有舵机
  // for (int angle = 0; angle <= 180; angle += 1) {
  //     for (int i = 0; i < 6; i+=1) {
  //         moveServo(i, angle); // 将所有舵机移动到当前角度
  //       }
  //     delay(10);
  //   }
  // Connect to Wi-Fi Red light on if connectted
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  // Serial.begin(115200);
  // tcpip_setup(ssid, password);
  delay(1000);
  strip.setPixelColor(0, strip.Color(1, 0, 0));
  strip.show();
  delay(1000);
  xTaskCreate(TaskMoveServo, "ServoMoveTask", 10000, NULL, 1, NULL);
  delay(500);
  strip.setPixelColor(0, strip.Color(0, 1, 0));
  strip.show();
  int temp[] = {60, 117, 62, 122, 67, 115};
  memcpy(targetAngles, temp, sizeof(targetAngles));
  
  delay(500);
  strip.setPixelColor(0, strip.Color(0, 0, 1));
  strip.show();
  int temp1[] = {79, 113, 16, 110, 61, 165};
  memcpy(targetAngles, temp1, sizeof(targetAngles));

  delay(500);
  strip.setPixelColor(0, strip.Color(0, 0, 1));
  strip.show();
  int temp2[] = {77, 82, 6, 118, 93, 167};
  memcpy(targetAngles, temp2, sizeof(targetAngles));

  //   //1,3,5 : 55 deg ********* 2,4,6 : 135 deg
  // for (int angle = 180; angle >= 135; angle -= 1) {
  //     for (int i = 1; i < 6; i+=2) {
  //       moveServo(i, angle);
  //     }
  //     delay(10);
  //   }
}




void loop() {
  // put your main code here, to run repeatedly:
}


// user defined functions
void setupServos() {
    for (int i = 0; i < 6; i++) {
        ledcSetup(servos[i].channel, freq, resolution);
        ledcAttachPin(servos[i].pin, servos[i].channel);
    }
}

void moveServo(int servoIndex, int angle) {
    if (servoIndex < 0 || servoIndex >= 6) return; // 检查索引有效性
    
    int duty = map(angle, 0, 180, minPulseWidth, maxPulseWidth);
    duty = duty * pow(2, resolution) / 20000; // 转换脉宽为LEDC占空比值
    ledcWrite(servos[servoIndex].channel, duty);
}


void TaskMoveServo(void *parameter) {
  //use global variable targetAngles
  for (;;) {
    // 这里可以添加代码，从其他设备接收数据，更新目标角度
    int i = 0;
    for(i = 0 ; i<6 ; i++){
      moveServo(i, targetAngles[i]);
    }
    delay(200); // 模拟工作，延时2秒
  }

}


void TaskTCPSerial(void *parameter) {
  for (;;) {
    WiFiClient client = server.available(); // 监听客户端连接
    if (client) {
      Serial.println("Client connected");
      Serial.println(client.remoteIP());
      while (client.connected()) {
        if (client.available()) {
          String line = client.readStringUntil('\r');
          Serial.print("Received data: ");
          Serial.println(line); // 通过串行端口输出接收到的数据
          // 这里可以添加代码，将接收到的数据（比如坐标）发送给其他设备
        }
      }

      client.stop();
      Serial.println("Client disconnected");
    }
    delay(20); // 模拟工作，延时20ms
  }
}

void TaskUpdateAngel(void *parameter) {
  for (;;) {
    // 这里可以添加代码，从其他设备接收数据，更新目标角度

    delay(2000); // 模拟工作，延时2秒
  }
}