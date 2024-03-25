#include <Arduino.h>
#include "tcpip.h"
#include <Adafruit_NeoPixel.h>
#include "esp32-hal-ledc.h"

const int freq = 50; // PWM信号频率，一般为50Hz
const int resolution = 10; // 分辨率，10位意味着1024级
const int minPulseWidth = 500; // 最小脉宽，单位为微秒
const int maxPulseWidth = 2500; // 最大脉宽，单位为微秒

//1,3,5 : 55 deg ********* 2,4,6 : 135 deg
int targetAngles[6] = {42, 135, 44, 140, 49, 133}; // 示例目标角度

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
void divide_angle(String line);



// task declaration
void TaskMoveServo(void *parameter);
void TaskTCPSerial(void *parameter);
void TaskUpdateAngel(void *parameter);
void processColorData(String colorData);
void TaskTCPSerial(void *parameter); 

// user defined
// const char* ssid = "kbjw"; // 替换为您的SSID
// const char* password =  "qwerwsad"; // 替换为您的Wi-Fi密码
// const char* ssid = "Gogy’s iPhone"; // 替换为您的SSID
// const char* password =  "88888888"; // 替换为您的Wi-Fi密码
const char* ssid = "/676"; // 替换为您的SSID
const char* password =  "31415926"; // 替换为您的Wi-Fi密码
WiFiServer server(80);

int minUs = 500;
int maxUs = 2500;

// for the ESP32-S3 the GPIO pins are 1-21,35-45,47-48

#define PIN 48 // 假设WS2812B LED数据线连接到GPIO 48
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
  setupServos(); // 初始化所有舵机
  // Connect to Wi-Fi Red light on if connectted
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200);
  
  tcpip_setup(ssid, password);


  xTaskCreate(TaskTCPSerial,"Serial Port by TCP",10000,NULL,1,NULL);
  xTaskCreate(TaskMoveServo, "ServoMoveTask", 10000, NULL, 1, NULL);
  
  delay(2000);

  int temp[] = {42, 135, 44, 140, 49, 133};
  memcpy(targetAngles, temp, sizeof(targetAngles));

  delay(2000);
  int temp1[] = {81, 122, 22, 106, 52, 162};
  memcpy(targetAngles, temp1, sizeof(targetAngles));

  delay(2000);
  memcpy(targetAngles, temp, sizeof(targetAngles));

  delay(2000);
  int temp2[] = {37, 94, 28, 156, 90, 138};
  memcpy(targetAngles, temp2, sizeof(targetAngles));
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

void divide_angle(String line){
// 分割接收到的字符串
  int angles[6]; // 假设我们有6个角度值
  int index = 0; // 用于angles数组的索引
  int lastIndex = 0; // 字符串分割的上一个索引
  for (int i = 0; i <= line.length(); i++) {
    // 检查逗号或字符串的末尾
    if (line.charAt(i) == ',' || i == line.length()) {
      String angleStr = line.substring(lastIndex, i); // 提取子字符串
      angles[index] = angleStr.toInt(); // 将字符串转换为整数
      index++;
      lastIndex = i + 1; // 更新下一个子字符串的起始索引
    }
  memcpy(targetAngles, angles, sizeof(targetAngles));
  }
}


void processColorData(String colorData) {
    // 这里实现颜色数据的处理逻辑
    // 例如，将颜色字符串转换为颜色代码，并设置LED颜色
    Serial.println("Received color data: " + colorData);
    // 假设颜色数据是单个字符，如"R"、"G"、"B"
    if (colorData == "R") {
        // 设置为红色
        strip.setPixelColor(0, strip.Color(255, 0, 0)); 
        
    } else if (colorData == "G") {
        // 设置为绿色
        strip.setPixelColor(0, strip.Color(0, 255, 0));
    } else if (colorData == "B") {
        // 设置为蓝色
        strip.setPixelColor(0, strip.Color(0, 0, 255));
    } else if (colorData == "Y") {
        // 设置为黄色
        strip.setPixelColor(0, strip.Color(255, 255, 0));
    }

    strip.show();
}


// user defined tasks
void TaskMoveServo(void *parameter) {
  //use global variable targetAngles
  for (;;) {
    // 这里可以添加代码，从其他设备接收数据，更新目标角度
    int i = 0;
    for(i = 0 ; i<6 ; i++){
      moveServo(i, targetAngles[i]);
    }
    delay(100); // 模拟工作，延时2秒
  }

}


void TaskTCPSerial(void *parameter) {
  for (;;) {
    WiFiClient client = server.available(); // 监听客户端连接
    if (client) {
      if (client.available()) {
        String line = client.readStringUntil('\r'); // 读取一行数据
        if (line.startsWith("C")) {
            // 处理颜色数据
            processColorData(line.substring(1)); // 去掉前缀"C"
        } else if (line.startsWith("A")) {
            // 处理角度数据
            divide_angle(line.substring(1)); // 去掉前缀"A"
        }
        Serial.println(line);
        client.flush(); // 清空缓冲区
      }
    }
    delay(20); // 模拟工作，延时20ms
  }
}

