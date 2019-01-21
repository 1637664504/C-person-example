#include <stdio.h>
#include <string.h>
int main(void)
{
//char str[] = "root:x::0:root:/root:/bin/bash:";
char str[] = " wl mpc 0;wl ap;wl ssid"";wl down;wl country ALL;";
char *buf;
char *token;
buf = str;
while((token = strsep(&buf, ";")) != NULL){
printf("%s\n", token);
}
return 0;
}