#include <stdio.h>
int main() {
    char input_str[100]; // 定义一个字符串，用来存输入的内容
    printf("请输入任意内容：");
    scanf("%s", input_str); // 读取键盘输入
    printf("你输入的内容是：%s\n", input_str);
    return 0;
}
