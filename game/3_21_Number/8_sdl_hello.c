#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "SDL_draw.h"           //包含SDL_draw库的头文件
int main()
{
        int i;
        double t;
        double x,y;
        double x0=320, y0=240;
        Uint32 screen_color;
        SDL_Surface *screen;    //一个屏幕指针
        if(SDL_Init(SDL_INIT_VIDEO) < 0){       //初始化视频子系统失败
                fprintf(stderr,"无法初始化:%s\n",SDL_GetError());       //不能用printf()，因为没有包含stdio.h头文件
                exit(1);
        }           
        //设置视频模式
        screen=SDL_SetVideoMode(640,480,16,SDL_SWSURFACE);
        if(screen==NULL){
                fprintf(stderr,"无法设置视频模式:%s\n",SDL_GetError());
                exit(1);
        }   
        atexit(SDL_Quit);       //退出

        //画直线，从点(240,180)到点(400,300),颜色为白色
        Draw_Line(screen,240,180,400,300,SDL_MapRGB(screen->format, 255,255,255));
        //画直线，从点(400,180)到点(240,300),颜色为蓝色
        Draw_Line(screen,400,180,240,300,SDL_MapRGB(screen->format, 0,0,255));
        for(i=0;i<640;i+=2){
                x=240-120*sin(3.14*i/180);
                i+=2;
                y=240-120*sin(3.14*i/180);
                Draw_Line(screen,i-2,x,i,y,SDL_MapRGB(screen->format, 0,0,255));
                SDL_Delay(5);                   //停留5毫秒
                SDL_UpdateRect(screen,0,0,0,0);         //更新整个屏幕
        }       
        SDL_UpdateRect(screen,0,0,0,0);         //更新整个屏幕
        SDL_Delay(3000);                        //停留5秒
        return 0;
}

