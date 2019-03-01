//  poker.c
//  day05
//
//  一个扑克牌生成程序：运行如下：
//  请输入你要的张数：5
//  程序输出:H5、H6、H7、H8、H9（Spade(黑桃)、Club(梅花)、Heart(红桃)、Diamond（方块））
//  建议：char suit[4] = {'S','D','C','H'}
//  char rank[13] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
//  Created by apple on 13-6-6.
//  Copyright (c) 2013年 apple. All rights reserved.
//
 
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

char poker[52][2];
int main()
{
    char suit[4] = {'S','C','H','D'};
    char rank[13] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
    int num = 0,a = 0,b = 0,count=0;
    int temp[4][13] = {0};
    srand((unsigned)time(0));
    
    printf("请输入您要的张数：");
    scanf("%d",&num);
    
    a = rand() % 4;
    b = rand() % 13;
    do{
        if(temp[a][b]==1){
            a = rand() % 4;
            b = rand() % 13;
        }else{
            printf("%c%c\t",suit[a],rank[b]);
            poker[count][0]=a;
            poker[count][1]=b;
            temp[a][b] = 1;
            count++;
            num--;
        }
    }while(num);
 
    
    return 0;
}

