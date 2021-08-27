#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char str[32] = "";
    // [] 表示指定范围
    sscanf("123456abcdedf", "%31[0-9]", str);       //123456
    sscanf("123456abcdedf", "%31[0-9a-z]", str);    //123456abcdedf

    // ^ 表示非
    sscanf("123456abcdedf", "%31[^a-z]", str);      //123456
    // * 表示忽略
    sscanf("123456abcdedf", "%*[0-9]%31[a-z]", str);    //abcdedf
    %*s 忽略一段字符串;
    %*d 忽略一个int
    char buf[128] = "? (192.168.1.2) at 14:6b:9c:bd:46:8d [ether]  on br-lan";
    char ip[16] = {0};
    char mac[18] = {0};
    sscanf(buf,"%*s (%15[. 0-9]) at %17[: 0-9 a-z]",ip,mac);    //ip=192.168.1.2,mac=14:6b:9c:bd:46:8d

    return 0;
}