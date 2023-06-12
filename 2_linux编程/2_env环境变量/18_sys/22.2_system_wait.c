#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void test2(void)
{
    int ret,status,finish;

    //2. 不存在的文件
    ret = system("ls 123aa.txt");
    if(ret)
        printf("ret=%d ,err=%s\n",ret,strerror(errno));
    if(WIFEXITED(status)){
        finish= WIFEXITED(status);
        printf("child exit with %d. Finish=%d\n", WEXITSTATUS(status),finish);
    }

}

void test3(void)
{
    int ret,status,finish;

    //3. 不存在的命令
    ret = system("catt 123aa.txt");
    if(ret)
        printf("ret=%d ,err=%s\n",ret,strerror(errno));
    if(WIFEXITED(status)){
        finish= WIFEXITED(status);
        printf("child exit with %d. Finish=%d\n", WEXITSTATUS(status),finish);
    }

}


int main(void)
{
    pid_t wait_pid;
    int ret,status,finish;

    //1. normal script
    ret = system("ls ~");

    /* 运行错误: 提示不存在子进程
    wait_pid = wait(&status);   //等待回收子进程
    if(wait_pid == -1){
        perror("wait error:");
        exit(1);
    }
    */
    if(ret)
        printf("ret=%d ,err=%s\n",ret,strerror(errno));
    if(WIFEXITED(status)){
        finish= WIFEXITED(status);
        printf("child exit with %d. Finish=%d\n", WEXITSTATUS(status),finish);
    }

    test2();
    test3();

    return 0;
}