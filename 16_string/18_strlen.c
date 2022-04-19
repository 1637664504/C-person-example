#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void test2()
{
    char *p = NULL;
    int len = 0;
    //非法，segmentation eror.
    //-- len = strlen(p);
    printf("%s 访问NULL len=%d\n",len);       
}
/*结论: strlen() 读取非法内存，导致段错误。
*/

int main ( int argc, char *argv[] )
{
    char *p = NULL;
    char buf[16] = {0};

    int ret1=0,ret2=0;
    //ret1 = strlen(p);
    ret2 = strlen(buf);
 
    test2();
    return 0;
}