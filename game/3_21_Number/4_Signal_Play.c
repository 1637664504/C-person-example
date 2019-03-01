#include <stdio.h>
#include <string.h>

typedef unsigned char u_char;

enum{
	POK_H=72,//hei tao
	POK_M=77,
	POK_F=70,
	POK_R=82
};

enum{
	GET_NEW_POK=0,
	FINISH=1,
};

u_char pok[52][2];
int pok_opt;

struct use_pok{
	u_char pok[8][2];
	int pok_num;
}use,ai;


void display_pok(struct *use_pok user)
{
	int i;
	int len = user->pok_num;
	for(i=0;i<len;i++){
		printf("|     | ");
	}
	printf("\n");
	
	for(i=0;i<len;i++){
		printf("| %c:%d | ",user->pok[i][0],user->pok[i][1]);
	}
	printf("\n");

	for(i=0;i<len;i++){
		printf("|     | ");
	}
	printf("\n");
}

int get_cmd()
{
	char cmd;
	int ret;
	printf("cmd:");
	cmd = getchar();
	if(cmd == 'n'){
		send_a_pok();
		ret = GET_NEW_POK;
	}
	else{
		ret = FINISH;
	}
}

int clean_pok()
{
	memset(pok,0,sizeof(char)*(104));
	pok_opt = 0;
}

int get_one_pok(struct *use_pok user)
{
	int n = user->pok_num;
	if(pok_opt >=52){
		printf("No pok can set\n");
		return 0;
	}
	if(n >= 8){
		printf("Very user max pok num is 8\n");
		return 0;
	}
	
	user->pok[n][0] =pok[pok_opt][0];
	user->pok[n][0] =pok[pok_opt][1];
	user->pok_num++;
	pok_opt++;
	
	return 1;
}

int start_send_pok()
{
	get_one_pok(use);
	get_one_pok(ai);
	get_one_pok(use);
	get_one_pok(ai);
}

int init_poker()
{
    u_char suit[4] = {POK_H,POK_M,POK_F,POK_R};
    u_char rank[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    int num = 0,a = 0,b = 0,count=0;
    int temp[4][13] = {0};
    srand((unsigned)time(0));

	while(count < 52){
		a = rand()%4;
		b = rand()%13;
		if(temp[a][b]==0){
			pok[count][0]=a;
			pok[count][1]=b;
			printf("%c:%d\n",a,b);
			count++;
			temp[a][b]=1;
		}
	}
    return 0;
}


int main(int argc, char *argv[])
{
	init_poker();
	start_send_pok();
	display_pok(use);
	display_pok(ai);

    return 0;
}

