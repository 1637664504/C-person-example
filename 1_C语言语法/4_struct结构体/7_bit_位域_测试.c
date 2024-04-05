#include <stdio.h>
#include <stdint.h>

#define Protocol_b0 0b1
#define Protocol_b12 0b110
#define Protocol_b3_5 0b111000

struct Bit
{
    uint8_t a : 1;    //bit 0
    uint8_t b : 2;    //bit 1 ~ 2
    uint8_t c : 3;    //bit 3 ~ 5
};

int main(void)
{
    struct Bit a;
    a.a = 1;
    a.b = 3;
    a.c = 7;

    printf("%x %x %x\n", a.a, a.b, a.c); // 打印16进制

    uint8_t var = *(uint8_t*)&a;
    printf("%u %u %u\n", var & Protocol_b0, var & Protocol_b12, var & Protocol_b3_5);

    return 0;
}

/* 运行结果
1 3 7
1 6 56

python 计算
>>> bin(6)
'0b110'
>>> bin(56)
'0b111000'

 */