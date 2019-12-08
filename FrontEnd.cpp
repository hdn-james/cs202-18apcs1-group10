#include <windows.h>
#include "FrontEnd.h"
using namespace std;
//                    A,B,C,D,E,F,G,F,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
const int num[26] = { 7,7,7,7,7,7,7,7,3,7,7,7,9,8,7,7,7,7,7,7,7,7,7,7,7,7 };

void DrawFrame(int x, int y, int h, int w) // coordinates x,y ------ height --- width
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

void ChangeTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return;
}

void ChangeText(string &s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == 'B') ChangeTextColor(3);
		else if (s[i] == 'b') ChangeTextColor(11);
		else if (s[i] == 'W') ChangeTextColor(15);
		else if (s[i] == 'R') ChangeTextColor(12);
		else if (s[i] == 'r') ChangeTextColor(13);
		else if (s[i] == 'Y') ChangeTextColor(14);
		else if (s[i] == 'N') ChangeTextColor(4);
		else if (s[i] == 'G') ChangeTextColor(2);
		else if (s[i] == 'g') ChangeTextColor(10);
		if (s[i] != ' ') s[i] = char(219);
		cout << s[i];
	}
	return;
}

void DrawObject(const string link, int x, int y)
{
	ifstream file(link);
	int tmp = 0;
	string s[20];
	while (getline(file, s[tmp]))
		++tmp;
	for (int i = 0; i < tmp; i++)
	{
		ChangeText(s[i]);
		CPointer(x, y + i);
		//cout << s[i];
	}
	file.close();
	return;
}
