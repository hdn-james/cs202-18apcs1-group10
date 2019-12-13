#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <stdio.h>
using namespace std;

void ClearFrame(int x, int y, int h, int w);
void CPointer(int x, int y);
void ChangeText(string &s);
void DrawObject(const string link, int x, int y);
void DrawFrame(int x, int y, int h, int w);
void ChangeTextColor(int color);
void OutputString(string text, int x, int y, bool chosen);
void PrStr(const char* text, int x, int y, int color);
void DrawSplashScreen();
void DrawMenu();