#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_ADMIN_USER_TIP "(Default: admin)"
#define DEFAULT_ADMIN_PASS_TIP "(Default: admin)"

int main ( int argc, char *argv[] )
{
	char user[64]={0};
	char pass[64]={0};
	sscanf(DEFAULT_ADMIN_USER_TIP,"(Default: %[^)])",user);
	sscanf(DEFAULT_ADMIN_PASS_TIP,"(Default: %[^)])",pass);
	
	printf("liuj-- user=%s ,pass=%s\n",user,pass);
	
	return 0;
}
