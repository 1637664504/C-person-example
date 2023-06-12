#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TEST_FILE "123.txt"
int main ( int argc, char *argv[] )
{
    FILE *fp;
    int i=0;
    for(i=0;i<64;i++){
        fp = fopen(TEST_FILE,"r");
    }

    sleep(60);

    return 0;
}

/*
./a.out
ls -l /proc/pid/fd

结果: 一共打开 75 个文件
 0 -> /dev/pts/4
 1 -> /dev/pts/4
 10 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 11 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 12 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 13 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 14 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 15 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 16 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 17 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 18 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 19 -> /dev/ptmx
 2 -> /dev/pts/4
 20 -> /dev/ptmx
 21 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 22 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 23 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 24 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 25 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 26 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 27 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 28 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 29 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 3 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 30 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 31 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 32 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 33 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 34 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 35 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 36 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 37 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 38 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 39 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 4 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 40 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 41 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 42 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 43 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 44 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 45 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 46 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 47 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 48 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 49 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 5 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 50 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 51 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 52 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 53 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 54 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 55 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 56 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 57 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 58 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 59 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 6 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 60 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 61 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 62 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 63 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 64 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 65 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 66 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 67 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 68 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 7 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 8 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
 9 -> /home/kali/1_Data/5_src/1_C_example/15_stdio/123.txt
*/