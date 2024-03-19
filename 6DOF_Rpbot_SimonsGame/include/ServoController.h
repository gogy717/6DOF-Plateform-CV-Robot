#ifndef MOTORFUN_H
#define MOTORFUN_H

#include <ESP32Servo.h>

// Published values for SG90 servos; adjust if needed
extern int minUs;
extern int maxUs;

class ServoController {
public:
    ServoController(int pin) : servoPin(pin) {}

    void attach() {
        servo.attach(servoPin,minUs,maxUs); // 附加舵机到其引脚
        // 可选：设置舵机到初始位置
    }

    void detach() {
        servo.detach(); // 从其引脚上分离舵机
    }

    void moveToAngle(int targetAngle, int stepDelay) {
        attach(); // 附加舵机到其引脚
        if (currentAngle < targetAngle) {
            for (int pos = currentAngle; pos <= targetAngle; pos++) {
                servo.write(pos);
                delay(stepDelay);
            }
        } else {
            for (int pos = currentAngle; pos >= targetAngle; pos--) {
                servo.write(pos);
                delay(stepDelay);
            }
        }
        currentAngle = targetAngle; // 更新当前角度为目标角度
        detach(); // 从其引脚上分离舵机
    }

private:
    Servo servo;
    int servoPin;
    int currentAngle;
};


#endif // MOTORFUN_H
