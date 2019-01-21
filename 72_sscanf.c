#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,const char *argv[])
{
    char buf[64]="atm0|IN|eth1|1";
    char p1[64]={0},p2[64]={0},p3[64]={0};

    //sscanf(buf,"%[^|]%[^|]%[^|]1",p1,p2,p3);
    //sscanf(buf,"%s |%s |%s |1",p1,p2,p3);
    sscanf(buf,"%[^|]|%[^|]|%[^|]|1",p1,p2,p3);
    printf("p1=%s,p2=%s,p3=%s\n",p1,p2,p3);

	return 0;
}
