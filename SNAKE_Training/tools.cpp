#include "tools.h"
#include <windows.h>
#include <stdio.h>

void SetWindowSize(int cols,int lines)
{
    system("title 贪吃蛇");
    char cmd[30];
    sprintf(cmd,"mode con cols=%d lines=%d",cols * 2,lines);
    system(cmd);
}

void SetColor(int colorID)  //文本颜色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorID);
}

void SetBackColor()  //文本背景色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_BLUE |
                            BACKGROUND_BLUE |
                            BACKGROUND_GREEN |
                            BACKGROUND_RED );
}

void SetCursorPosition(const int x,const int y)  //光标
{
    COORD position;
    position.X = x*2;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position);
}
