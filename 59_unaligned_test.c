/*
非对其测试:
要么指令没对齐，要么数据没有对齐。
比如指针int *p指向的地址不是4字节对齐的（例如p=0x0001，而不是0x0000或者0x0004），
那么*p = N在某些CPU下就会产生数据非对齐的错误。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char buf[8]={0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18};
int main ( int argc, char *argv[] )
{
	unsigned char *str =NULL;
	int *p = NULL; 
	
	str = (unsigned char *)malloc(8);
	memcpy(str,buf,8);
	printf(" *buf addr=%p ,str addr=%p\n",&buf[0],str);

	p = (int *)(str+7);
	printf("111 *p=%X \n",*p);
	*p = 0x12345678;
	printf("222 *p=%X \n",*p);

	return 0;
}



