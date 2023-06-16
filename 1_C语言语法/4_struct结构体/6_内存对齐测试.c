#include <stdio.h>

// 设置 1字节对齐
#pragma pack(1)
struct aa {
    char a;
    int b;
    char c;
};
#pragma pack()
// 恢复 字节对齐

struct bb {
    char a;
    int b;
    char c;
};

int main(void)
{
    printf("size 对齐:%lu 不对齐:%lu\n", sizeof(struct aa), sizeof(struct bb));
    return 0;
}


/*测试:

size 对齐:6 不对齐:12


结果:
#pragma pack(1)

#pragma pack()      -->恢复对齐
 */