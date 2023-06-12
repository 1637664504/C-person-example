#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <>
char *get_oneline(char *oneline,unsigned int len,char *str)
{
    char *p = str;
    char *p_newlineChar;
    char *result = NULL;
    if((*p != '\0') && (p_newlineChar = strchr(p,'\n')))
    {
        strncpy(oneline,str,p_newlineChar-p);
        if(*(++p_newlineChar))
            result = p_newlineChar;
    }
    else
    {
        strncpy(oneline,str,p_newlineChar-p);
        result = NULL;
    }

    return result;
}

int getCmdResult(const char *cmd, char *result, int len)
{
    int ret = 0;
    FILE *fp = popen(cmd, "r");

	if(!fp) 
		return 0;
    ret = fread(result,len,1,fp);
    pclose(fp);

    return ret;
}

void do_oneline_test(void)
{
    char buf[512] = {0};
    char oneline[64] = {0};
    char *p = NULL;
    char *p_buf = buf;


    getCmdResult("cat /proc/net/if_inet6",buf,512);

    while(p = strchr(p_buf,'\n')){
        *p = '\0';
        strcpy(oneline,p_buf);
        printf("%s \n",oneline);
        char address[40]={0};
        int if_idx = 0;
        unsigned int prefix_len = 0;
        unsigned int type = 0;
        unsigned int flags = 0;

        sscanf(oneline,"%s %x %x %x %x",address, &if_idx, &prefix_len, &type, &flags);
        printf("111 %s, %d, %d, %d, %d\n",address,if_idx,prefix_len,type, flags);
        p_buf = ++p;
    }
}

int main ( int argc, char *argv[] )
{
    char buf[128] = "D2:22:33:44:55:61\nD2:22:33:44:55:62\n";
    char oneline[64] = {0};
    char *p = buf;
#if 0
    while(p = get_oneline(oneline,sizeof(oneline)-1,p)){    //failed
        printf("%s \n",oneline);
    }
#endif
    do_oneline_test();

    return 0;
}