#include "startinterface.h"
#include <windows.h>

void StartInertface::PrintFirst()
{
    for(auto& point : startsnake)
    {
        point.Print();
        Sleep(speed);
    }
}

void StartInertface::PrintSecond()
{
    for (int i = 10; i != 40; ++i)
    {
        int j = (((i-2)%8) < 4) ? (15 + (i-2)%8 ) : (21 - (i-2)%8 );
        startsnake.emplace_back(Point(i,j));
        startsnake.back().Print();
        startsnake.front().Clear();
        startsnake.pop_front();
        Sleep(speed);
    }
}

void StartInertface::PrintThird()
{
    while(!startsnake.empty() || textsnake.back().GetX() < 33)
    {
        if(!startsnake.empty())
        {
            startsnake.front().Clear();
            startsnake.pop_front();
        }
        ClearText();
        PrintText();
        Sleep(speed);
    }
}

void StartInertface::PrintText()
{
    for (auto& point : textsnake)
    {
        if (point.GetX() >= 0)
            point.Print();
    }
}

void StartInertface::ClearText()
{
    for (auto& point : textsnake)
     {
         if (point.GetX() >= 0)
             point.Clear();
         point.ChangePosition(point.GetX() + 1,point.GetY());
     }
}

void StartInertface::Action()
{
    PrintFirst();
    PrintSecond();
    PrintThird();
}
