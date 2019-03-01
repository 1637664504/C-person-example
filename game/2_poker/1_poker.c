
 
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define BOSS 0
#define PLAYER_1 1
#define PLAYER_2 2

int poker[52][2];
void display_user(int (*use)[2],int len)
{
	int i;
	for(i=0;i<len;i++)
		printf("%d:%d ",use[i][0],use[i][1]);

	printf("\n");
}

void send_user_poker(int (*use_1)[2],int (*use_2)[2],int (*use_3)[2],int len)
{
	int i;
	
	for(i=0;i<52,--len>=0;i+=3){
		use_1[len][0] = poker[i][0];
		use_1[len][1] = poker[i][1];
		
		use_2[len][1] = poker[i+=1][0];
		use_2[len][1] = poker[i+=1][1];
		
		use_3[len][1] = poker[i+=2][0];
		use_3[len][1] = poker[i+=2][1];
	}
}

int init_poker()
{
    char suit[4] = {1,2,3,4};
    char rank[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    int num = 0,a = 0,b = 0,count=0;
    int temp[4][13] = {0};
    srand((unsigned)time(0));

	while(count < 52){
		a = rand()%4;
		b = rand()%13;
		if(temp[a][b]==0){
			poker[count][0]=a;
			poker[count][1]=b;
			printf("%d:%d\n",a,b);
			count++;
			temp[a][b]=1;
		}
	}
    return 0;
}

int main(void)
{
	int use[13][2];
	init_poker();
	send_user_poker(use,13,BOSS);
	display_user(use, 13);
}

