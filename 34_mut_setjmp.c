#include	<stdlib.h>
#include    <stdio.h>
#include <unistd.h>
#include <string.h>
#include <setjmp.h>

static jmp_buf jmpbuffer;
static var;

void bcd()
{
    if(var == 5)
        exit(1);

    var++;
    printf("5555555555555\n\n");
    longjmp(jmpbuffer,var);
}

void abc(){
    printf("444444444444\n");
    if(setjmp(jmpbuffer) == 4){
        printf("sec 444444444\n");
    }else {
        printf("sec 4----------\n");
    }
    bcd();
}

int main ( int argc, char *argv[] )
{
    if(setjmp(jmpbuffer) == 1){
        printf("111111111\n");
    }else{
        printf("222222222\n");
    }
    printf("3333333333333333\n");
    abc();
}
/*
Run:
222222222
3333333333333333
444444444444
5555555555555

111111111
3333333333333333
444444444444
5555555555555

222222222
3333333333333333
444444444444

*/

