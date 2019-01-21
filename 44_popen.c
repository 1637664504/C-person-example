#include <stdio.h>
#include <stdlib.h>
#include <string.h>

  
  int main ( int argc, char *argv[] )
  {
        char buf[256];
        snprintf(buf, 255, "ip route ");
        FILE *p = popen(buf, "r");
        while(fgets(buf,256,p) > 0){   
            printf("liuj-- buf=%s\n",buf);
        }
        pclose(p);
    return 0;
  }   



