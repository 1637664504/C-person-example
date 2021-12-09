#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main (void)
{
  char IPdotdec[20]="192.168.1.2"; // 存放点分十进制IP地址
  char buf[16]="";
  struct in_addr s;  // IPv4地址结构体
  // 输入IP地址
  printf("Please input IP address: ");
  //scanf("%s", &IPdotdec);
  // 转换
  inet_pton(AF_INET, IPdotdec, (void *)&s);
  printf("inet_pton: 0x%x\n", s.s_addr); // 注意得到的字节序
  // 反转换
  inet_ntop(AF_INET, (void *)&s, buf, 16);
  printf("inet_ntop: %s\n", buf);
}