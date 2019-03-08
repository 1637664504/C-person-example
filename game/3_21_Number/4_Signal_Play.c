#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

typedef unsigned char u_char;


#define USER_WIN 333
enum{
	POK_H=72,//hei tao
	POK_M=77,
	POK_F=70,
	POK_R=82
}type;

enum{
	GET_NEW_POK=0,
	FINISH=1,
};

struct poker{
	char type;
	int num;
}pok[52];
int g_pok_num;

struct play_user{
	char name[32];
	struct poker pok[8];
	int num;
	int sum;
}use,*ai;


void display_pok(struct play_user* user)
{
	int i;
	int n = user->num;
	for(i=0;i<n;i++){
		printf("|    |  ");
	}
	printf("\n");
	
	for(i=0;i<n;i++){
		printf("|%c:%d|   ",user->pok[i].type,user->pok[i].num);
	}
	printf("\n");

	for(i=0;i<n;i++){
		printf("|    |  ");
	}
	printf("\n name:%s ------------>\n\n",user->name);
}

int get_one_pok(struct play_user * user)
{
	int n = user->num;
	if(g_pok_num >=52){
		printf("No pok can set\n");
		return 0;
	}
	if(n >= 8){
		printf("Very user max pok num is 8\n");
		return 0;
	}
	
	user->pok[n].type =pok[g_pok_num].type;
	user->pok[n].num =pok[g_pok_num].num;
	user->num++;
	g_pok_num++;
	
	return 1;
}

void update_pokSum(struct play_user *p)
{
	int j;
	int num,sum;
	
	num = p->num;
	p->sum=0;
	sum=0;

	for(j=0;j<num;j++){
			if(p->pok[j].num > 10){
				sum += 10;
			}else{
				sum += p->pok[j].num;
			}
	}
	p->sum = sum;

}

int ai_player_need_getPok(struct play_user *use)
{
	int remain;
	int prob;
	int ret =0;

	remain = 21- use->sum;
	if(remain <= 10){
		// 100%
		ret =1;
	}else if(remain == 21 || remain < 0){
		// 0%
		ret =0;
	}else{
		// 20 10%
		if((rand()%(remain+9)) ==1){
			ret =1;
		}else{
			ret =0;
		}
	}

	return ret;
}


int get_cmd()
{
	char cmd;
	char buf[64]={0};
	int ret;

	printf("cmd:\n");
	//while((cmd=getchar())!='/n' && cmd!=EOF){
	while(read(0,buf,64) != 0){
		sscanf(buf,"%c",&cmd);
		if(cmd == 'y'){
			return GET_NEW_POK;
		}
		else if(cmd == 'n'){
			return FINISH;
		}
	}
}

int clean_pok()
{
	memset(pok,0,sizeof(pok[52]));
	memset(&use,0,sizeof(use));
	g_pok_num = 0;
}

int start_send_pok(struct play_user *use,struct play_user *ai,int n)
{
	int i;
	get_one_pok(use);
	for(i=0;i<n;i++)
		get_one_pok(ai+i);

	get_one_pok(use);
	for(i=0;i<n;i++)
		get_one_pok(ai+i);
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

struct play_user * init_ai(int num)
{
	struct play_user *p,*t;
	int i;
	p = malloc(sizeof(struct play_user)*num);
	if(p == NULL)
	{
		perror("malloc error");
		return NULL;
	}

	memset(p,0,sizeof(struct play_user)*num);
	for(i=0;i<num;i++){
		t=p+i;
		strcpy(t->name,&ai_name[i][0]);
	}

	return p;
}

int check_win(struct play_user *use,struct play_user *ai,int n)
{
	int i,j,num;
	int sum,max,ret;
	struct play_user *p;

	sum = 0;
	max = 0;

	//get use
	num=use->num;
	for(j=0;j<num;j++){
		if(use->pok[j].num > 10){
			sum += 10;
		}else{
			sum += use->pok[j].num;
		}
	}
	if(sum < 22){
		max = sum;
		ret = USER_WIN;
	}

	//get ai
	for(i=0;i<num;i++){
		p= ai+i;
		num=p->num;
		sum=0;
		for(j=0;j<num;j++){
			if(p->pok[j].num > 10){
				sum += 10;
			}else{
				sum += p->pok[j].num;
			}
		}
		if(sum < 22 && sum>max){
			max = sum;
			ret = i;
		}
	}
	
	return ret;
}

void play_game(int num)
{
	struct play_user *p,*t;
	int i,ret;
	p = init_ai(num);
	if(p == NULL){
		printf("can't malloc exit\n");
		exit(-1);
	}
	strcpy(use.name,"player_user");
	ai = p;

	init_poker();
	start_send_pok(&use,p,num);
	display_pok(&use);

	for(i=0;i<num;i++){
		t =p+i;
		display_pok(t);
	}
	while(get_cmd() == GET_NEW_POK){
		get_one_pok(&use);
		display_pok(&use);
		i=0;
		for(i=0;i<num;i++){
			t = p+i;
			update_pokSum(t);
			if(ai_player_need_getPok(t)){
				get_one_pok(t);
				display_pok(t);
			}
		}
	}
	
	if((ret=check_win(&use,p,num)) == USER_WIN){
		printf("Win %s\n",use.name);
		display_pok(&use);
	}else{
		t = p+ret;
		printf("Win %s\n",t->name);
		display_pok(t);
	}
	clean_pok();
	free(p);
}

int main(int argc, char *argv[])
{
	int play_num;

	while(1){
		printf("Input user play num:");
		scanf("%d",&play_num);
		if(play_num<2 || play_num > 8){
			printf("User play num 2 ~ 8\n");
			continue;
		}
		play_game(play_num);
	}

    return 0;
}

