#include <windows.h>
#include "FrontEnd.h"
using namespace std;
//                    A,B,C,D,E,F,G,F,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
const int num[26] = { 7,7,7,7,7,7,7,7,3,7,7,7,9,8,7,7,7,7,7,7,7,7,7,7,7,7 };


void PrStr(const char* name, int x, int y, int color) //prt str
{
	ChangeTextColor(color);
	CPointer(x, y);
	cout << name;
	return;
}

void PaintFrame(int x, int y, int h, int w) // coordinates x,y ------ height --- width
{
	for (int i = 0; i <= h + 1; i++)
		for (int j = 0; j <= w + 1; j++)
		{
			CPointer(x + j, y + i);
			if ((i == 0) && (j == 0))
			{
				cout << char(218);
				continue;
			}
			if ((i == 0) && (j == w + 1))
			{
				cout << char(191);
				continue;
			}
			if ((i == h + 1) && (j == 0))
			{
				cout << char(192);
				continue;
			}
			if ((i == h + 1) && (j == w + 1))
			{
				cout << char(217);
				continue;
			}
			if ((i == 0) || (i == h + 1)) cout << char(196);
			if ((j == 0) || (j == w + 1)) cout << char(179);
		}
	return;
}

void ClearFrame(int x, int y, int h, int w)
{
	for (int i = y; i <= y + h - 1; i++)
	{
		CPointer(x, i);
		for (int j = x; j < x + w - 1; j++) cout << " ";
	}
	return;
}

void CPointer(int x, int y) //Change Pointer
{
	COORD pt = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pt);
	return;
}


void ChangeText(string &s)
{
	for (int i = 0; i < s.size(); i++)
		if (s[i] == '*') s[i] = char(254);
		//else if (s[i] == 'W') s[i] = char(220);
		//else if (s[i] == 'F') s[i] = char(223);
		//else if (s[i] == '|') s[i] = char(248);
		//else if (s[i] == '+') s[i] = char(176);
		//else if (s[i] == 'X') s[i] = char(254);
	return;
}

void DrawObject(const char* type, int x, int y)
{
	ifstream myfile(type);
	int cnt = 0;
	string s[20];
	while (getline(myfile, s[cnt]))
		++cnt;
	for (int i = 0; i < cnt; i++)
	{
		ChangeText(s[i]);
		CPointer(x, y + i);
		cout << s[i];
	}
	myfile.close();
	return;
}

void ChangeTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return;
}


