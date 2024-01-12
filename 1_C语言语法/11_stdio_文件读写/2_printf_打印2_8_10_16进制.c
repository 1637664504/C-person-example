#include <stdio.h>
#include <stdlib.h>
int main() {
    unsigned char byte = 0b10101010; // 定义一个字节数据
    printf("二进制表示: %u\n", byte); // 使用 %u 格式化输出

    char buf[16] = {0};
    itoa(byte, buf, 2);
    printf("buf=%s\n", buf);

    return 0;
}
