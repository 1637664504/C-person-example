#include <stdio.h>
double Sum(int *num, int Length);
 
int main()
{
	int a[6] = { 1,2,3,4,5,6 };
	printf("sum=%f\n", Sum(a, 6));
	//getchar();
	return 0;
}
 
double Sum(int *num,int Length)
{
	double sum=0;
	for (size_t i = 0; i < Length; i++)
	{
		sum += num[i];
	}
	return sum;
}
 

