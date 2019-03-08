#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

enum{
	POK_H=72,//hei tao
	POK_M=77,
	POK_F=70,
	POK_R=82
}type;

struct poker{
	char type;
	int num;
}pok[52];
int poker_count;

struct play_user{
	char name[32];
	struct poker pok[8];
	int num;
	int sum;
}use,*ai;


char ai_name[8][32]={
		"ai_1_xiaoming",
		"ai_2_yangyang",
		"ai_3_zero",
		"ai_4_boss",
		"ai_5_Master",
		"ai_6_??",
		"ai_7_Jax",
		"ai_8_Nuxi"
};


void help()
{
	printf("21 number game.");

}

int init_poker()
{
    u_char suit[4] = {POK_H,POK_M,POK_F,POK_R};
    u_char order[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    int num = 0,a = 0,b = 0,count=0;
    int temp[4][13] = {0};
    srand((unsigned)time(0));

	while(count < 52){
		a = rand()%4;
		b = rand()%13;
		if(temp[a][b]==0){
			pok[count].type=suit[a];
			pok[count].num=order[b];
			printf("%c:%d\n",pok[count].type,pok[count].num);
			count++;
			temp[a][b]=1;
		}
	}
    return 0;
}

void clean_poker()
{
	memset(pok,0,sizeof(pok[52]));
}

struct play_user *init_player(int num)
{
	struct play_user *p,*t;
	int i;
	//init use
	strcpy(use.name,"Hero");

	//init ai
	p = malloc(sizeof(struct play_user)*num);
	if(p == NULL){
		perror("malloc error");
		return NULL;
	}
	memset(p,0,sizeof(struct play_user)*num);
	//init ai->name
	for(i=0;i<num;i++){
		t= p+i;
		strcpy(t->name,&ai_name[i][0]);
	}
	
	return p;
}

void release_player(struct play_user *p,int num)
{
	free(p);
}

int get_one_pok(struct play_user *p)
{
	int num;

	num = p->num;
	if(poker_count >= 52){
		printf("pok number Max 52\n");
		return 0;
	}
	if(num>=8){
		printf("user poker number Max 8\n");
		return 0;
	}
	p->pok[num].type=pok[poker_count].type;
	p->pok[num].num=pok[poker_count].num;
	p->num ++;
	poker_count++;
	
}

void start_send_two_pok(struct play_user *user,struct play_user *ai,int num)
{
	int i;
	struct play_user *t;
	get_one_pok(user);
	for(i=0;i<num;i++){
		t = ai+i;
		get_one_pok(t);
	}
	
	get_one_pok(user);
	for(i=0;i<num;i++){
		t = ai+i;
		get_one_pok(t);
	}
}

void display_user(struct play_user *p)
{
	int i;
	int n = p->num;
	for(i=0;i<n;i++){
		printf("|    |  ");
	}
	printf("\n");
	
	for(i=0;i<n;i++){
		printf("|%c:%d|   ",p->pok[i].type,p->pok[i].num);
	}
	printf("\n");

	for(i=0;i<n;i++){
		printf("|    |  ");
	}
	printf("\n name:%s ------------>\n\n",p->name);

}



void main_play()
{
	int num;
	struct play_user *p;
	
		printf("input player num");
		scanf("%d",&num);
		if(num<1 || num > 7){
			printf("Player num 1~7.Please re_input\n");
			return;
		}
		p=init_player(num);
		init_poker();

		start_send_two_pok(&use,p,num);
		

		clean_poker();
		release_player(p,num);
	
}

int main(int argc, char** argv)
{
	int num;
	char buf[32];
	char cmd;
	help();
	while(1){
		printf("Do you want continue play game!\n Q queit , any other key continue\n");
		scanf("%c",&cmd);
		if(cmd == 'q'){
			break;
		}
		main_play();
	}
}

