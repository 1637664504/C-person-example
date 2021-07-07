

#include <zconf.h>
#include <zlib.h>
#include <stdio.h> /* 因为 printf 相关的函数在这个头文件中定义的 */
#include <errno.h> /* 因为 errno 相关的函数在这个头文件中定义的 */
#include <stdlib.h> /* 因为 exit 函数在这个头文件中定义的 */
#include <string.h> /* 因为 strlen 函数在这个头文件中定义的 */

int main(int argc, char **argv)
{
        gzFile mygzfp;
        char buf[64]={0};

        mygzfp = gzopen(argv[1], "r");
        if(mygzfp == NULL) {
                printf("以写方式打开文件'%s'出错，错误信息：%s", argv[1], strerror(errno));
                exit(0);
        }

        gzread(mygzfp,buf,64);
        printf("buf=%s\n",buf);

        gzclose(mygzfp);
        return 0;
}