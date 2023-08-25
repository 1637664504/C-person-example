
#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
    float f;
    char* str = "23.5";
    f = atof(str);
    printf("string=%s,f=%f\n", str, f);

    return 0;
}
