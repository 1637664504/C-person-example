#include <stdio.h>
#include <stdint.h>
struct Demo{
	uint8_t a;
	uint32_t b;
}demo;

#pragma pack(1)
struct Demo2{
	uint8_t a;
	uint32_t b;
}demo2;

int main(void)
{
    printf("对齐 &a=%p, &b=%p, sizeof=%lu\n", &demo.a, &demo.b, sizeof(demo));
    printf("不对齐 &a=%p, &b=%p, sizeof=%lu\n", &demo2.a, &demo2.b, sizeof(demo2));

    return 0;
}