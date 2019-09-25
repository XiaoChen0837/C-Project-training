#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "controller.h"
#include "tools.h"
#include "startinterface.h"
#include "map.h"
#include "snake.h"
#include "food.h"

void Controller::Start()    //开始界面
{
    SetWindowSize(41,32);
    SetColor(2);
    StartInertface *start = new StartInertface();   //类实例化
    start -> Action();
    delete start;

    SetCursorPosition(13,26);
    std::cout << "Press any key to start...";
    SetCursorPosition(13,27);
    system("pause");
}

void Controller::Slect()
{
    SetColor(3);
    SetCursorPosition(13,26);
    std::cout << "                          " ;
    SetCursorPosition(13,27);
    std::cout << "                          " ;
    SetCursorPosition(6,21);
    std::cout <<"请选择难度：";
    SetCursorPosition(6,22);
    std::cout <<"(上下键选择，回车键确认)";
    SetCursorPosition(27,22);
    SetBackColor();
    std::cout << "简单模式";
    SetCursorPosition(27,24);
    SetColor(3);
    std::cout << "普通模式";
    SetCursorPosition(27,26);
    std::cout << "困难模式";
    SetCursorPosition(27,28);
    std::cout << "炼狱模式";
    SetCursorPosition(0,31);
    score = 0;

   /*键盘操作*/
   int ch;
   key = 1;
   bool flag = false;
   while ((ch = getch()))
   {
       switch (ch)
       {
        case 72:  //up
            if (key > 1)
            {
                switch (key)
                {
                case 2:
                    SetCursorPosition(27,22);
                    SetBackColor();
                    std::cout << "简单模式";

                    SetCursorPosition(27,24);
                    SetColor(3);
                    std::cout << "普通模式";

                    --key;
                    break;

                case 3:
                    SetCursorPosition(27,24);
                    SetBackColor();
                    std::cout << "普通模式";

                    SetCursorPosition(27,26);
                    SetColor(3);
                    std::cout << "困难模式";

                    --key;
                    break;

                case 4:
                    SetCursorPosition(27,26);
                    SetBackColor();
                    std::cout << "困难模式";

                    SetCursorPosition(27,28);
                    SetColor(3);
                    std::cout << "炼狱模式";

                    --key;
                    break;
                }
            }
            break;

        case 80:  //down
            if (key < 4)
            {
                switch (key)
                {
                case 1:
                    SetCursorPosition(27,24);
                    SetBackColor();
                    std::cout << "普通模式";

                    SetCursorPosition(27,22);
                    SetColor(3);
                    std::cout << "简单模式";

                    ++key;
                    break;

                case 2:
                    SetCursorPosition(27,26);
                    SetBackColor();
                    std::cout << "困难模式";

                    SetCursorPosition(27,24);
                    SetColor(3);
                    std::cout << "普通模式";

                    ++key;
                    break;

                case 3:
                    SetCursorPosition(27,28);
                    SetBackColor();
                    std::cout << "炼狱模式";

                    SetCursorPosition(27,26);
                    SetColor(3);
                    std::cout << "困难模式";

                    ++key;
                    break;
                }
            }
            break;

        case 13: //Enter
            flag = true;
            break;
        default:
            break;
       }
       if (flag) break;

       SetCursorPosition(0,31);
   }

   switch (key)
   {
    case 1:
        speed = 135 ;
        break;
    case 2:
        speed = 100 ;
        break;
    case 3:
        speed = 60 ;
        break;
    case 4:
        speed = 30 ;
        break;
    default:
        break;
   }
}

void Controller::DrawGame()   //游戏界面
{
    system("cls");//清屏

    /*Draw Map*/
    SetColor(3);
    Map *init_map = new Map();
    init_map -> PrintInitmap();
    delete init_map;


    SetColor(3);
    SetCursorPosition(33,1);
    std::cout << "Greedy Snake";
    SetCursorPosition(33,2);
    std::cout << "贪吃蛇";
    SetCursorPosition(33,4);
    std::cout << "难度：";
    SetCursorPosition(36, 5);
    switch (key)
    {
    case 1:
        std::cout << "简单模式" ;
        break;
    case 2:
        std::cout << "普通模式" ;
        break;
    case 3:
        std::cout << "困难模式" ;
        break;
    case 4:
        std::cout << "炼狱模式" ;
        break;
    default:
        break;
    }
    SetCursorPosition(31,7);
    std::cout << "得分：";
    SetCursorPosition(37,8);
    std::cout << "     0" ;
    SetCursorPosition(33,13);
    std::cout << "方向键移动" ;
    SetCursorPosition(33,15);
    std::cout << "ESC键暂停" ;
}

int Controller::PlayGame()
{
    Snake *csnake = new Snake();
    Food  *cfood = new Food;
    SetColor(6);
    csnake -> InitSnake();
    srand((unsigned)time(NULL));
    cfood ->DrawFood(*csnake);

    /*游戏循环*/
    while(csnake->OverEdge() && csnake->HitItself())
    {
        if (!csnake->ChangDirection())
        {
            int tmp = Menu();
            switch(tmp)
            {
            case 1:
                break;
            case 2:
                delete csnake;
                delete cfood;
                return 1;
            case 3:
                delete csnake;
                delete cfood;
                return 2;
            default:
                break;
            }
        }

        if (csnake->GetFood(*cfood))
        {
            csnake -> Move();
            UpdateScore(1);
            RewriteScore();
            cfood ->DrawFood(*csnake);
        }
        else
        {
            csnake->NormalMove();
        }

        if (csnake->GetBigFood(*cfood))
        {
            csnake -> Move() ;
            UpdateScore(cfood->GetProgressBar()/5);
            RewriteScore();
        }

        if(cfood->GetBigFlag())
        {
            cfood->FlashBigFood();
        }
        Sleep(speed);
    }

    /*蛇死亡*/
    delete csnake;
    delete cfood;
    int tmp = GameOver();
    switch(tmp)
    {
    case 1:
        return 1;
    case 2:
        return 2;
    default:
        return 2;
    }
}

void Controller::UpdateScore(const int& tmp)
{
    score += key * 10 * tmp;
}

void Controller::RewriteScore()
{
    SetCursorPosition(37,8);
    SetColor(11);
    int bit = 0;
    int tmp = score;
    while(tmp != 0)
    {
        ++bit;
        tmp /= 10;
    }
    for (int i = 0; i < (6 - bit) ; ++i)
    {
        std::cout << " " ;
    }
     std::cout << score;
}

int Controller::Menu()
{
    /*绘制菜单*/
    SetColor(11);
    SetCursorPosition(32, 19);
    std::cout << "菜单：" ;
    Sleep(100);
    SetCursorPosition(34, 21);
    SetBackColor();
    std::cout << "继续游戏" ;
    Sleep(100);
    SetCursorPosition(34, 23);
    SetColor(11);
    std::cout << "重新开始" ;
    Sleep(100);
    SetCursorPosition(34, 25);
    std::cout << "退出游戏" ;
    SetCursorPosition(0, 31);

    /*选择部分*/
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while ((ch = getch()))
    {
        switch (ch)
        {
        case 72://UP
            if (tmp_key > 1)
            {
                switch (tmp_key)
                {
                case 2:
                    SetCursorPosition(34, 21);
                    SetBackColor();
                    std::cout << "继续游戏" ;
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << "重新开始" ;

                    --tmp_key;
                    break;
                case 3:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    std::cout << "重新开始" ;
                    SetCursorPosition(34, 25);
                    SetColor(11);
                    std::cout << "退出游戏" ;

                    --tmp_key;
                    break;
                }
            }
            break;

        case 80://DOWN
            if (tmp_key < 3)
            {
                switch (tmp_key)
                {
                case 1:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    std::cout << "重新开始" ;
                    SetCursorPosition(34, 21);
                    SetColor(11);
                    std::cout << "继续游戏" ;

                    ++tmp_key;
                    break;
                case 2:
                    SetCursorPosition(34, 25);
                    SetBackColor();
                    std::cout << "退出游戏" ;
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << "重新开始" ;

                    ++tmp_key;
                    break;
                }
            }
            break;

        case 13://Enter
            flag = true;
            break;

        default:
            break;
        }

        if (flag)
        {
            break;
        }
        SetCursorPosition(0, 31);
    }

    if (tmp_key == 1) //选择继续游戏，则将菜单擦除
    {
        SetCursorPosition(32, 19);
        std::cout << "      " ;
        SetCursorPosition(34, 21);
        std::cout << "        ";
        SetCursorPosition(34, 23);
        std::cout << "        ";
        SetCursorPosition(34, 25);
        std::cout << "        ";
    }
    return tmp_key;

}

void Controller::Game()
{
    Start();   //开始界面
    while (true)
    {
        Slect();  //选择界面
        DrawGame();
        int tmp = PlayGame();

        if (tmp == 1)
        {
            system("cls");
            continue;
        }
        /*
        else if (tmp == 2 );
        {
            break;
        }
        */
        else
        {
            break;
        }
    }
}

int Controller::GameOver()//游戏结束界面
{
    /*绘制游戏结束界面*/
    Sleep(500);
    SetColor(11);
    SetCursorPosition(10, 8);
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━" ;
    Sleep(30);
    SetCursorPosition(9, 9);
    std::cout << " ┃               Game Over !!!              ┃" ;
    Sleep(30);
    SetCursorPosition(9, 10);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(9, 11);
    std::cout << " ┃              很遗憾！你挂了              ┃" ;
    Sleep(30);
    SetCursorPosition(9, 12);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(9, 13);
    std::cout << " ┃             你的分数为：                 ┃" ;
    SetCursorPosition(24, 13);
    std::cout << score ;
    Sleep(30);
    SetCursorPosition(9, 14);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(9, 15);
    std::cout << " ┃   是否再来一局？                         ┃" ;
    Sleep(30);
    SetCursorPosition(9, 16);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(9, 17);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(9, 18);
    std::cout << " ┃    嗯，好的        不了，还是学习有意思  ┃" ;
    Sleep(30);
    SetCursorPosition(9, 19);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(9, 20);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(10, 21);
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━" ;

    Sleep(100);
    SetCursorPosition(12, 18);
    SetBackColor();
    std::cout << "嗯，好的" ;
    SetCursorPosition(0, 31);

    /*选择部分*/
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while ((ch = getch()))
    {
        switch (ch)
        {
        case 75://LEFT
            if (tmp_key > 1)
            {
                SetCursorPosition(12, 18);
                SetBackColor();
                std::cout << "嗯，好的" ;
                SetCursorPosition(20, 18);
                SetColor(11);
                std::cout << "不了，还是学习有意思" ;
                --tmp_key;
            }
            break;

        case 77://RIGHT
            if (tmp_key < 2)
            {
                SetCursorPosition(20, 18);
                SetBackColor();
                std::cout << "不了，还是学习有意思" ;
                SetCursorPosition(12, 18);
                SetColor(11);
                std::cout << "嗯，好的" ;
                ++tmp_key;
            }
            break;

        case 13://Enter
            flag = true;
            break;

        default:
            break;
        }

        SetCursorPosition(0, 31);
        if (flag) {
            break;
        }
    }

    SetColor(11);
    switch (tmp_key)
    {
    case 1:
        return 1;//重新开始
    case 2:
        return 2;//退出游戏
    default:
        return 1;
    }
}























