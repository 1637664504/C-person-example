#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main () {
    mqd_t mq_id;
    //打开创建好的消息队列
	mq_id = mq_open("/notify",O_WRONLY | O_CREAT, 0666, NULL);
	if (mq_id == -1) {
        perror("mq_open failed");
        exit(-1);
	}
	
	//持续向消息队列中每隔两秒写入数据
	while(1) {
		if (mq_send(mq_id, "hello world", sizeof("hello world"), 1) == -1) {
			printf("mq_send failed \n");
			_exit(-1);
		}
		printf("msg send success -----\n");
		sleep(2);
	}
	return 0;
}
