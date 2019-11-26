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
    hideCursor();
    drawMainMenu();
}

menuFunction::~menuFunction()
{
    hideCursor();
    deleteMenu();
}

void menuFunction::drawMainMenu()
{
    cout << this->title;
	drawBorder();
	TextColor(Color_Cyan);
	for (int i = 0; i < numOfItems; i++) {
		GotoXY(70, i * 2 + 15);
		cout << MENU[i];
	}
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
