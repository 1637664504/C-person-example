#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>
 
#define MAX_THREAD_NUM 100
#define SEG_LEN 10
#define MAX_PORT 1000
 
typedef struct PortNode
{
    char ip[30];
    int minPort;
    int maxPort;
}PortNode;
pthread_t tid;

void* doit(void* arg)
{
    int i, sockfd, connfd;
    struct sockaddr_in servaddr;
    PortNode* port = (PortNode*)arg;
    pthread_detach(pthread_self());//为避免存储器泄漏，每个可结合线程都应该被其他线程显式地收回，要么通过调用pthread_detach函数被分离
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    //inet_pton(AF_INET, port->ip, &servaddr.sin_addr);
    servaddr.sin_addr.s_addr = inet_addr(port->ip);
    for(i = port->minPort; i <= port->maxPort; i++){
        servaddr.sin_port = htons(i);
        if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
            perror("socket error");
            pthread_exit(NULL);
        }
        if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) == 0){
            printf("%s:%d\n", port->ip, i);
        }
        close(sockfd);//注意关闭！！
    }
    pthread_exit(NULL);
}
 
 
int main(int argc, char** argv)
{
    int i,j;
    for(i = 1; i < argc; i++){
        PortNode* port = (PortNode*)malloc(sizeof(PortNode));
        for(j = 0; j < MAX_THREAD_NUM; j++){
            strcpy(port->ip, argv[i]);
            port->minPort = j*SEG_LEN + 1;
            if(j == (MAX_THREAD_NUM - 1))port->maxPort = MAX_PORT;
            else port->maxPort = port->minPort + SEG_LEN - 1;
            if(pthread_create(&tid, NULL, doit, (void*) port)  != 0 ){
                perror("pthread create error.\n");
                free(port);
                port=NULL;
                exit(1);
            }
        }
    }
    sleep(3);
}

