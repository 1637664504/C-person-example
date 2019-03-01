#include<stdlib.h>
#include<stdio.h>
#define MAX 10
 
int main(void)
{
	int number[MAX] = {0};
	int i;
	unsigned int seed;
	scanf("%d",&seed);/*手动输入种子*/
	srand(seed);
	for(i = 0; i < MAX; i++)
	{
		number[i] = (rand() % 10);/*产生100以内的随机整数*/
		printf("%d ",number[i]);
	}
	printf("\n");
	return 0;
}
/*
liuj@22:~/1_Data/5_linux$ ./a.out
1
83 86 77 15 93 35 86 92 49 21
liuj@22:~/1_Data/5_linux$ ./a.out
1
83 86 77 15 93 35 86 92 49 21

liuj@22:~/1_Data/5_linux$ ./a.out
22
70 78 86 21 48 51 53 42 87 37

结论:rand() 需要随机初始化种子
*/
