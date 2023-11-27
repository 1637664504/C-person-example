#include <stdio.h>
#include <stdint.h>
int main()
{
    uint8_t data[16] = { 0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF };
    uint16_t var_u16 = *(uint16_t*)(data);
    uint16_t var_u16_2 = (uint16_t) * (data);
    uint32_t var_32 = *(uint32_t*)(data);

	return 0;
}

/* gdb内存值:
var_u16: 0x0201 = 513
var_u16_2: 0x1 = 1
var_32 0x04030201 = 67305985
 */