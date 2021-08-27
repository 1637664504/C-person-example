#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
  char buf[256];
  int len=0;

  FILE *p = popen("ip route", "r");
  len=fread(buf,256,1,p);
  printf("len=%d, buf====\n%s++++\n",len,buf);

  pclose(p);
  return 0;
}