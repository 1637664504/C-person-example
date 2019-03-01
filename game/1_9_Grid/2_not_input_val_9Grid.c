#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <semaphore.h>

#define debug printf
char map[3][3]={' '};
int step;

void help()
{
	printf("9 Grid '#' play Game\n");
	printf("input: [line][col][x/o]\n");
}

void game_init()
{
	memset(&map[0][0],' ',9);
	step = 0;
}
int game_cmd(void)
{
	char cmd;
	printf("** You Win ** play%d\n",step%2?1:0);
	printf("input q Exit,any key continue\n");
	cmd = getc(stdin);
	if(cmd == 'q'){
		printf("Exit\n");
		return 1;
	}

	game_init();
	return 0;
}

void display_9grid(void)
{
	int i;
	printf("\n");
	for(i=0;i<3;i++){
		printf(" %c | %c | %c \n",map[i][0],map[i][1],map[i][2]);
		printf("____________\n");
	}
}

int check_win(void)
{
	int i,j,a;

	if(step < 5){
		return 0;
	}

	//1.横3条
	for(i=0;i<3;i++){
		a = map[i][0];
		if(a != ' '){
			if(a == map[i][1] && a == map[i][2]){
				printf("- - - win ");
				return 1;
			}
		}
	}
	//2. 竖3条
	for(i=0;i<3;i++){
		a = map[0][i];
		if(a != ' '){
			if(a == map[1][i] && a==map[2][i]){
				printf("| | | win ");
				return 1;
			}
		}
	}
	//3. 2条叉
	{
		a = map[1][1];
		if(a != ' '){
			if(a == map[0][0] && a==map[2][2]){
				printf("x1 x1 x1 win ");
				return 1;
			}
			if(a ==map[0][2] && a==map[2][0]){
				printf("x2 x2 x2 win ");
				return 1;
			}
		}
	}

	return 0;
}

int input_number()
{
	int a,b,n;
	char val;

	if(step%2 == 0){
		printf("\nplay1 a b :");
		val = 'x';
	}else{
		printf("\nplay2 a b :");
		val = 'o';
	}
	scanf("%d %d",&a,&b);

	if((a>2 && a<1) && (b>2 && b<1)){
		printf("9Grid a,b rang is:1 2 3\n");
		return -1;
	}

	{
		n = map[a-1][b-1];
		if(n != ' '){
			printf("this grid is set\n");
			return -1;
		}
		map[a-1][b-1]=val;
		step++;

		return 0;
	}
	
	return -1;
}

int main ( int argc, char *argv[] )
{
	int ret;
	char cmd;
	help();
	game_init();
	#if 1
	while(1){
		display_9grid();
		if(input_number()){
			printf("re inpit\n");
		}else{
			ret = check_win();
			if(ret){				// win
				display_9grid();	//
				if(game_cmd())	//continue or exit cmd
					break;
			}
		}
	}
	#endif

	return 0;
}


