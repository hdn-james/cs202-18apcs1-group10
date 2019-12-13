#ifndef CONSOLE_H
#define CONSOLE_H

#define Color_Back			0
#define Color_DarkBlue		1
#define Color_DarkGreen		2
#define Color_DarkCyan		3
#define Color_DarkRed		4
#define Color_DarkPink		5
#define Color_DarkYellow	6
#define Color_DarkWhite		7
#define Color_Grey			8
#define Color_Blue			9
#define Color_Green			10
#define Color_Cyan			11
#define Color_Red			12
#define Color_Pink			13
#define Color_Yellow		14
#define Color_White			15

#define default_Color		7

#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdio.h>
#include<iomanip>
#include<fstream>
using namespace std;

void FixConsoleWindow();
void GotoXY(int x, int y);
void resizeConsole(int width, int height);
void hideCursor();
int whereX();
int whereY();
void TextColor(int color);

#endif /* Console.h */