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

void Controller::Start()    //��ʼ����
{
    SetWindowSize(41,32);
    SetColor(2);
    StartInertface *start = new StartInertface();   //��ʵ����
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
    std::cout <<"��ѡ���Ѷȣ�";
    SetCursorPosition(6,22);
    std::cout <<"(���¼�ѡ�񣬻س���ȷ��)";
    SetCursorPosition(27,22);
    SetBackColor();
    std::cout << "��ģʽ";
    SetCursorPosition(27,24);
    SetColor(3);
    std::cout << "��ͨģʽ";
    SetCursorPosition(27,26);
    std::cout << "����ģʽ";
    SetCursorPosition(27,28);
    std::cout << "����ģʽ";
    SetCursorPosition(0,31);
    score = 0;

   /*���̲���*/
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
                    std::cout << "��ģʽ";

                    SetCursorPosition(27,24);
                    SetColor(3);
                    std::cout << "��ͨģʽ";

                    --key;
                    break;

                case 3:
                    SetCursorPosition(27,24);
                    SetBackColor();
                    std::cout << "��ͨģʽ";

                    SetCursorPosition(27,26);
                    SetColor(3);
                    std::cout << "����ģʽ";

                    --key;
                    break;

                case 4:
                    SetCursorPosition(27,26);
                    SetBackColor();
                    std::cout << "����ģʽ";

                    SetCursorPosition(27,28);
                    SetColor(3);
                    std::cout << "����ģʽ";

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
                    std::cout << "��ͨģʽ";

                    SetCursorPosition(27,22);
                    SetColor(3);
                    std::cout << "��ģʽ";

                    ++key;
                    break;

                case 2:
                    SetCursorPosition(27,26);
                    SetBackColor();
                    std::cout << "����ģʽ";

                    SetCursorPosition(27,24);
                    SetColor(3);
                    std::cout << "��ͨģʽ";

                    ++key;
                    break;

                case 3:
                    SetCursorPosition(27,28);
                    SetBackColor();
                    std::cout << "����ģʽ";

                    SetCursorPosition(27,26);
                    SetColor(3);
                    std::cout << "����ģʽ";

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

void Controller::DrawGame()   //��Ϸ����
{
    system("cls");//����

    /*Draw Map*/
    SetColor(3);
    Map *init_map = new Map();
    init_map -> PrintInitmap();
    delete init_map;


    SetColor(3);
    SetCursorPosition(33,1);
    std::cout << "Greedy Snake";
    SetCursorPosition(33,2);
    std::cout << "̰����";
    SetCursorPosition(33,4);
    std::cout << "�Ѷȣ�";
    SetCursorPosition(36, 5);
    switch (key)
    {
    case 1:
        std::cout << "��ģʽ" ;
        break;
    case 2:
        std::cout << "��ͨģʽ" ;
        break;
    case 3:
        std::cout << "����ģʽ" ;
        break;
    case 4:
        std::cout << "����ģʽ" ;
        break;
    default:
        break;
    }
    SetCursorPosition(31,7);
    std::cout << "�÷֣�";
    SetCursorPosition(37,8);
    std::cout << "     0" ;
    SetCursorPosition(33,13);
    std::cout << "������ƶ�" ;
    SetCursorPosition(33,15);
    std::cout << "ESC����ͣ" ;
}

int Controller::PlayGame()
{
    Snake *csnake = new Snake();
    Food  *cfood = new Food;
    SetColor(6);
    csnake -> InitSnake();
    srand((unsigned)time(NULL));
    cfood ->DrawFood(*csnake);

    /*��Ϸѭ��*/
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

    /*������*/
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
    /*���Ʋ˵�*/
    SetColor(11);
    SetCursorPosition(32, 19);
    std::cout << "�˵���" ;
    Sleep(100);
    SetCursorPosition(34, 21);
    SetBackColor();
    std::cout << "������Ϸ" ;
    Sleep(100);
    SetCursorPosition(34, 23);
    SetColor(11);
    std::cout << "���¿�ʼ" ;
    Sleep(100);
    SetCursorPosition(34, 25);
    std::cout << "�˳���Ϸ" ;
    SetCursorPosition(0, 31);

    /*ѡ�񲿷�*/
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
                    std::cout << "������Ϸ" ;
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << "���¿�ʼ" ;

                    --tmp_key;
                    break;
                case 3:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    std::cout << "���¿�ʼ" ;
                    SetCursorPosition(34, 25);
                    SetColor(11);
                    std::cout << "�˳���Ϸ" ;

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
                    std::cout << "���¿�ʼ" ;
                    SetCursorPosition(34, 21);
                    SetColor(11);
                    std::cout << "������Ϸ" ;

                    ++tmp_key;
                    break;
                case 2:
                    SetCursorPosition(34, 25);
                    SetBackColor();
                    std::cout << "�˳���Ϸ" ;
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << "���¿�ʼ" ;

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

    if (tmp_key == 1) //ѡ�������Ϸ���򽫲˵�����
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
    Start();   //��ʼ����
    while (true)
    {
        Slect();  //ѡ�����
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

int Controller::GameOver()//��Ϸ��������
{
    /*������Ϸ��������*/
    Sleep(500);
    SetColor(11);
    SetCursorPosition(10, 8);
    std::cout << "��������������������������������������������" ;
    Sleep(30);
    SetCursorPosition(9, 9);
    std::cout << " ��               Game Over !!!              ��" ;
    Sleep(30);
    SetCursorPosition(9, 10);
    std::cout << " ��                                          ��" ;
    Sleep(30);
    SetCursorPosition(9, 11);
    std::cout << " ��              ���ź��������              ��" ;
    Sleep(30);
    SetCursorPosition(9, 12);
    std::cout << " ��                                          ��" ;
    Sleep(30);
    SetCursorPosition(9, 13);
    std::cout << " ��             ��ķ���Ϊ��                 ��" ;
    SetCursorPosition(24, 13);
    std::cout << score ;
    Sleep(30);
    SetCursorPosition(9, 14);
    std::cout << " ��                                          ��" ;
    Sleep(30);
    SetCursorPosition(9, 15);
    std::cout << " ��   �Ƿ�����һ�֣�                         ��" ;
    Sleep(30);
    SetCursorPosition(9, 16);
    std::cout << " ��                                          ��" ;
    Sleep(30);
    SetCursorPosition(9, 17);
    std::cout << " ��                                          ��" ;
    Sleep(30);
    SetCursorPosition(9, 18);
    std::cout << " ��    �ţ��õ�        ���ˣ�����ѧϰ����˼  ��" ;
    Sleep(30);
    SetCursorPosition(9, 19);
    std::cout << " ��                                          ��" ;
    Sleep(30);
    SetCursorPosition(9, 20);
    std::cout << " ��                                          ��" ;
    Sleep(30);
    SetCursorPosition(10, 21);
    std::cout << "��������������������������������������������" ;

    Sleep(100);
    SetCursorPosition(12, 18);
    SetBackColor();
    std::cout << "�ţ��õ�" ;
    SetCursorPosition(0, 31);

    /*ѡ�񲿷�*/
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
                std::cout << "�ţ��õ�" ;
                SetCursorPosition(20, 18);
                SetColor(11);
                std::cout << "���ˣ�����ѧϰ����˼" ;
                --tmp_key;
            }
            break;

        case 77://RIGHT
            if (tmp_key < 2)
            {
                SetCursorPosition(20, 18);
                SetBackColor();
                std::cout << "���ˣ�����ѧϰ����˼" ;
                SetCursorPosition(12, 18);
                SetColor(11);
                std::cout << "�ţ��õ�" ;
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
        return 1;//���¿�ʼ
    case 2:
        return 2;//�˳���Ϸ
    default:
        return 1;
    }
}























