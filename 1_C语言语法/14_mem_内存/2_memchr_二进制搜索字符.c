#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main()
{
    uint8_t data[16] = { 0x11,0x12,0x13,0x14, 0x15,0x16,0x17,0x18,'h', 'e', 'l', 'l',  'o', '\0', 0x25,0x26 };
    uint8_t *ret = memchr(data,0x13,16);
    printf("ret=%s  offset=%ld\n", (char *)ret, (uint8_t *)ret - data);

    return 0;
}

/*

 */
