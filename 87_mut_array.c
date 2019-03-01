#include<stdlib.h>
#include<stdio.h>
#define MAX 10

void display(int (*num)[2],int a,int b)
{
	int i,j;
	for(i=0;i<a;i++){
		for(j=0;j<b;j++){
			printf("%d ",num[i][j]);
		}
		printf("\n");
	}
}
 
int main(void)
{
	int num[3][2]={1,2,3,
			4,5,6};

	//display(&num[0][0],3,2);
	display(num,3,2);

	return 0;
}


