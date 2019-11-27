#include "menu.h"

#include "GraphicsHandler.h"
using namespace std;

menuFunction::menuFunction()
{
    numOfItems = 4;
    MENU.push_back("NEW GAME");
    MENU.push_back("LOAD GAME");
    MENU.push_back("SETTING");
    MENU.push_back("EXIT");
}

menuFunction::~menuFunction()
{
    //deleteMenu();
}

void menuFunction::drawMainMenu()
{
    cout << this->title;
    drawBorder();
    TextColor(Color_Cyan);
    for (int i = 0; i < numOfItems; i++)
    {
        GotoXY(70, i * 2 + 18);
        cout << MENU[i];
    }
    TextColor(Color_Red);
    credit();
    TextColor(default_Color);
}

void menuFunction::deleteMenu()
{
    for (int i = 1; i < Y_MAX - 1; i++)
    {
        for (int j = 0; j < Y_MAX; j++)
        {
            GotoXY(i, j);
            cout << " ";
        }
    }
}

int getMove()
{
    char c = _getwch();
    if ((int)c == -32)
        c = _getwch();
    switch ((int)c)
    {
    case 72:
        return 1; // up
    case 80:
        return 2; // down
    case 75:
        return 3; // left
    case 77:
        return 4; // right
    case 27:
        return 5; // esc
    case 13:
        return 6; // enter
    default:
        return 0;
    }
}

void menuFunction::drawBorder()
{
    char a = 201, b = 205, c = 187; // ╔ ═ ╗
    GotoXY(0, 0);
    cout << a;
    for (int i = 1; i < (X_MAX); i++)
    {
        cout << b;
    }
    cout << c;
    char d = 186, e = 200, f = 188; // ║ ╚ ╝
    for (int i = 1; i < Y_MAX; i++)
    {
        GotoXY(0, i);
        cout << d;
        GotoXY(X_MAX, i);
        cout << d;
    }
    cout << e;
    for (int i = 1; i < (X_MAX); i++)
    {
        cout << b;
    }
    cout << f;
}

void menuFunction::credit()
{
    GotoXY((X_MAX - 55) / 2, Y_MAX - 3);
    cout << "Author: Huynh Dai Nhan - Mai Hoang Nhi - Pham Quoc Huy";
}

void menuFunction::arrow(int x, int y)
{
    GotoXY(67, 18);
    cout << " ";
    GotoXY(67, 20);
    cout << " ";
    GotoXY(67, 22);
    cout << " ";
    GotoXY(67, 24);
    cout << " ";
    char a = 175;
    GotoXY(x, y);
    cout << a;
}

int menuFunction::choice()
{
    arrow(67, 18);
    int c;
    c = getMove();
    while (c == 0)
    {
        c = getMove();
    }
    do
    {
        if (c == 5)
            return 4;
        if (whereY() == 18)
        {
            c = getMove();
            while (c == 0)
            {
                c = getMove();
            }
            if (c == 6)
                return 1;
            if (c == 2 || c == 4)
                arrow(67, 20);
            if (c == 1 || c == 3)
                arrow(67, 24);
        }
        if (whereY() == 20)
        {
            c = getMove();
            while (c == 0)
            {
                c = getMove();
            }
            if (c == 6)
                return 2;
            if (c == 2 || c == 4)
                arrow(67, 22);
            if (c == 1 || c == 3)
                arrow(67, 18);
        }
        if (whereY() == 22)
        {
            c = getMove();
            while (c == 0)
            {
                c = getMove();
            }
            if (c == 6)
                return 3;
            if (c == 2 || c == 4)
                arrow(67, 24);
            if (c == 1 || c == 3)
                arrow(67, 20);
        }
        if (whereY() == 24)
        {
            c = getMove();
            while (c == 0)
            {
                c = getMove();
            }
            if (c == 6)
                return 4;
            if (c == 2 || c == 4)
                arrow(67, 18);
            if (c == 1 || c == 3)
                arrow(67, 22);
        }
    } while (c != 0);

    return -1;
}
