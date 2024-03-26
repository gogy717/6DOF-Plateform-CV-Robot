#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#include <string.h>  
  
#define MAX_COLORS 4  
#define MAX_SEQUENCE_LENGTH 10  
  
void play_simon_game() {  
    // 初始化灯的颜色数组  
    char *colors[MAX_COLORS] = {"红灯", "黄灯", "绿灯", "蓝灯"};  
      
    // 存储电脑生成的序列  
    char sequence[MAX_SEQUENCE_LENGTH];  
    int sequence_length = 0;  
      
    // 游戏是否结束  
    int game_over = 0;  
      
    // 游戏难度等级，初始为1  
    int difficulty = 1;  
      
    // 使用当前时间初始化随机数生成器  
    srand((unsigned int)time(NULL));  
      
    while (!game_over) {  
        // 生成当前难度等级对应的颜色并添加到序列中  
        char new_color[10];  
        strcpy(new_color, colors[rand() % MAX_COLORS]);  
        sequence[sequence_length++] = *new_color; // 只存储颜色的首字符作为标识  
        sequence[sequence_length] = '\0'; // 确保字符串以null结尾  
          
        // 显示给玩家看的颜色序列  
        printf("STEP %d: 电脑-%s\n", difficulty, sequence);  
          
        // 获取玩家的输入  
        char player_input[MAX_SEQUENCE_LENGTH];  
        printf("请输入你记住的颜色序列（用空格隔开）：");  
        scanf("%s", player_input); // 注意：这不会处理空格分隔的输入，需要改进  
          
        // 检查玩家输入的序列是否正确  
        if (strcmp(player_input, sequence) == 0) {  
            printf("正确！增加难度。\n");  
            // 难度增加，但序列保持不变  
            difficulty++;  
        } else {  
            game_over = 1;  
            printf("游戏结束，你失败了！\n");  
        }  
    }  
      
    printf("游戏结束，你的最高难度等级是：%d\n", difficulty - 1);  
}  
  
int main() {  
    // 开始游戏  
    play_simon_game();  
    return 0;  
}