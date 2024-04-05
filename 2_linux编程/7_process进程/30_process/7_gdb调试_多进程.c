#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	pid_t pid;

	// pid = vfork();	// 创建进程
	pid = fork();	// 创建进程
	if (pid < 0) { // 出错
		perror("vfork");
	}

	if (0 == pid) { // 子进程
		int count = 10;
		while (count --) {
			printf("i am sun\n");
			sleep(1);
		}
		_exit(0); // 退出子进程，必须
	}
	else if (pid > 0) { // 父进程
		int count = 20;
		while (count --) {
			printf("i am father\n");
			sleep(1);
		}
	}

	return 0;
}
