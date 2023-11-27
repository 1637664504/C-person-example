#include <stdio.h>
#include <string.h>
#include <stdint.h>

char* memstr(uint8_t* full_data, uint32_t full_data_len, char* substr,uint32_t sublen)
{
    if (full_data == NULL || full_data_len <= 0 || substr == NULL) {
        return NULL;
    }

    if (*substr == '\0') {
        return NULL;
    }

    int i;
    uint8_t* cur = full_data;
    int last_possible = full_data_len - sublen + 1;
    for (i = 0; i < last_possible; i++) {
        if (*cur == *substr) {
            //assert(full_data_len - i >= sublen);
            if (memcmp(cur, substr, sublen) == 0) {
                //found
                return (char *)cur;
            }
        }
        cur++;
    }

    return NULL;
}

int main()
{
    uint8_t a[26] = { 'q','w','e','r','t','y','u','i','o','p','a','s','d','f','\0','h','j','k','\0','z','x','c','v','b','n','m' };
    char* ret = memstr(a, 26, "zxcv",4);
    printf("ret=%s  offset=%ld\n", ret, (uint8_t *)ret-a);

    // test 2
    uint8_t data[16] = { 0x11,0x12,0x13,0x14, 0x15,0x16,0x17,0x18,'h', 'e', 'l', 'l',  'o', '\0', 0x25,0x26 };
    ret = memstr(data, sizeof(data), "hello",5);
    printf("ret=%s  offset=%ld\n", ret, (uint8_t *)ret - data);

    return 0;
}

/*
ret=zxcvbnm  offset=19
ret=hello  offset=8

 */
