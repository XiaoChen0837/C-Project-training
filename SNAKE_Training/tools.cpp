#include "tools.h"
#include <windows.h>
#include <stdio.h>

void SetWindowSize(int cols,int lines)
{
    system("title ̰����");
    char cmd[30];
    sprintf(cmd,"mode con cols=%d lines=%d",cols * 2,lines);
    system(cmd);
}

void SetColor(int colorID)  //�ı���ɫ
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorID);
}

void SetBackColor()  //�ı�����ɫ
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_BLUE |
                            BACKGROUND_BLUE |
                            BACKGROUND_GREEN |
                            BACKGROUND_RED );
}

void SetCursorPosition(const int x,const int y)  //���
{
    COORD position;
    position.X = x*2;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position);
}
