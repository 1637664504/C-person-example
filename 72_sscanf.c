#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,const char *argv[])
{
    char buf[64]="atm0|IN|eth1|1";
    char p1[64]={0},p2[64]={0},p3[64]={0};

    char buf2[64]="_id:7755 _name:liuj";
    int id;
    char name[32]={0};

    char buf3[64]="liuj@xiaom#Hi How are you!";
    char recv_name[32]={0};

    //sscanf(buf,"%[^|]%[^|]%[^|]1",p1,p2,p3);
    //sscanf(buf,"%s |%s |%s |1",p1,p2,p3);
    sscanf(buf,"%[^|]|%[^|]|%[^|]|1",p1,p2,p3);
    printf("p1=%s,p2=%s,p3=%s\n",p1,p2,p3);


    //2. _id:7755 _name:liuj
    sscanf(buf2,"_id:%d _name:%s",&id,name);
    printf("id=%d,name=%s\n",id,name);

    //3.
    sscanf(buf3,"%*[^@]@%[^#]",recv_name);
    printf("recv_name=%s\n",recv_name);

	return 0;
}
