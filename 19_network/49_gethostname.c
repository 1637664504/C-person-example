#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int i = 0;
    char str[32] = {0};
    char hostname[32] = "www.baidu.com";
     struct hostent* phost = NULL;

 	
	 printf("liuj-- argc=%d\n",argc);
	if(argc > 1){
		memset(hostname,0,32);
		strcpy(hostname,argv[1]);
	}
    phost = gethostbyname(hostname);
    if (NULL == phost)
    {
		printf("liuj-- 222222222\n");
        return -1;    
    }
    
    printf("---Offical name:\n\t%s\n", phost->h_name);

    printf("---Alias name:\n");    
    for (i = 0;  phost->h_aliases[i]; i++)
    {
        printf("\t%s\n", phost->h_aliases[i]);
    }

    printf("---Address list:\n");
    for (i = 0; phost->h_addr_list[i]; i++)
    {
        printf("\t%s\n", inet_ntop(phost->h_addrtype,  phost->h_addr_list[i], str, sizeof(str)-1));
    }

    return 0;
}

