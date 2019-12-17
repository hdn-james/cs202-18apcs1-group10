#include "SplashScreen.h"
using namespace std;

void ChangeTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return;
}

void ChangeText(string& s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == 'B') ChangeTextColor(3);
		else if (s[i] == 'b') ChangeTextColor(11);
		else if (s[i] == 'W') ChangeTextColor(15);

		else if (s[i] == 'R') ChangeTextColor(4);
		else if (s[i] == 'r') ChangeTextColor(12);
		else if (s[i] == 'Y') ChangeTextColor(14);

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
		Console::GotoXY(x, y + i);
		//cout << s[i];
	}
	file.close();
	return;
}

void SplashScreen::draw() 
{
	DrawObject(SS_CAR, 58, 6+3);
	DrawObject(SS_NAME, 42, 20+3);
	Console::GotoXY(26, 29+3);
	Console::changeTextColor(Utilities::Color::LightGreen);
	cout << "Loading....";
	string path;
	for (int i = 1; i <= 4; i++)
	{
		Sleep(1000);
		path = SS_LOAD + to_string(i) + txt;
		DrawObject(path,18, 30+3);
	}
	system("cls");
}
