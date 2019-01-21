#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char buf[1024] =
    "<html><head>create VPN failed.</head>\
           <body>Only supports one mode of pptp and l2tp. Please delete another one.\
           </body>\
     </html>";

    //printf("liuj-- buf=%s\n",buf);
    fprintf(stdout,"222: %s\n",buf);
}

