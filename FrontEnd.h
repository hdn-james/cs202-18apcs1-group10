#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <conio.h>
using namespace std;

void PrStr(const char* name, int x, int y, int color);
void OutputFunction(const char* name, int x, int y, bool chosen);
void OutputString(string name, int x, int y, bool chosen);
void ClearFrame(int x, int y, int h, int w);
void CPointer(int x, int y);
void ChangeText(string &s);
void DrawObject(const char* type, int x, int y);
void ChangeTextColor(int color);
void PaintFrame(int x, int y, int h, int w);
bool InputChar(string &res, int x, int y, bool password, int bound, bool edit);
int Select(int r, int c, int &Pos);