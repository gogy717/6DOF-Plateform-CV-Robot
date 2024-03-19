#include <Arduino.h>
#include "tcpip.h"
#include <Adafruit_NeoPixel.h>
#include "servo_task.h"
#include "servoController.h"


// user defined
const char* ssid = "kbjw"; // 替换为您的SSID
const char* password =  "qwerwsad"; // 替换为您的Wi-Fi密码
WiFiServer server(80);

int minUs = 500;
int maxUs = 2500;

// for the ESP32-S3 the GPIO pins are 1-21,35-45,47-48
int servoPin1 = 9;
int servoPin2 = 10;
int servoPin3 = 11;
int servoPin4 = 12;
int servoPin5 = 13;
int servoPin6 = 14;
ServoController servo1(9), servo2(10), servo3(11), servo4(12), servo5(13), servo6(14);

#define PIN 48 // 假设WS2812B LED数据线连接到GPIO 48
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:

  // Connect to Wi-Fi Red light on if connectted
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200);
  tcpip_setup(ssid, password);
  strip.setPixelColor(0, strip.Color(1, 0, 0));
  strip.show();

  // Start the servo task
  xTaskCreate(
    TaskMoveServo, // Task function
    "TaskMoveServo", // A name just for humans
    10000, // This stack size can be checked & adjusted by reading the Stack Highwater
    &servo1, // Parameters to pass to the task
    1, // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
		NULL); // Task handle
}




void loop() {
  // put your main code here, to run repeatedly:
}

