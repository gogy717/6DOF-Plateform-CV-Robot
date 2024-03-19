#include "servo_task.h"
#include "ServoController.h" // 假设这是包含ServoController类定义的头文件

// Published values for SG90 servos; adjust if needed


void TaskMoveServo(void *pvParameters) {
    ServoController* servo = static_cast<ServoController*>(pvParameters);
    for (;;) {
        servo->moveToAngle(90, 10); // 移动到90度
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
        servo->moveToAngle(0, 10); // 移动到0度
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
