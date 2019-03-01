#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int Mon[12]={31,28,31,30,31,30,
	31,31,30,31,30,31};
int MonSum[12]={0,31,59,90,120,151,181,
	212,243,273,304,334};

//计算月数的总数
int cal_mon_sum(int mon)
{
	return MonSum[mon];
}

int cal_first_wek(int year)
{
	int sum=0,wek;
	sum=(year*356)+(year%4-1);
	wek=(sum+6)%7;
	
	return wek;
}

int display_mon(int mon,int wek)
{
	int i,j,count=0,len,t;
	char buf[1024]={0};

	printf("\t %d \n",mon);
	printf("Mo Tu We Th Fr Sa Su\n");

	len=0;
	for(i=0;i<wek;i++){
		len += sprintf(buf+len,"   ");
	}
	count+=wek;
	t=Mon[mon]+wek;
	
	for(j=1;j<=Mon[mon],i<t;j++,i++){
		if(count++%7 == 0){
			len+=sprintf(buf+len,"\n");
		}
		len+=sprintf(buf+len,"%2d ",j);
	
	}
	printf("%s\n",buf);
	printf("wek=%d\n",t%7);

}

void display_year(int year)
{
	int i,wek;
	wek = cal_first_wek(year);

	for(i=0;i<12;i++){
		wek = display_mon(i,wek);
	}
}

int main(int argc,char *argv[])
{
	int year,mon;
	int total_day = 0;
	if(argc==2){
		year = atoi(argv[1]);
	}else if(argc == 2){
		year = atoi(argv[1]);
		mon = atoi(argv[2]);
	}
	display_year(2018);
	//display_mon(1,3);
}

