#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <string>

#include "InputHandler.h"

class Console
{
private:
    static HANDLE _hStdin;
    static HANDLE _hStdout;
    static HWND _consoleWindows;
    static size_t _bufferSize;
    static _CHAR_INFO *_buffer;
    static CONSOLE_SCREEN_BUFFER_INFO _info;
    static CONSOLE_CURSOR_INFO _cInfo;

    static void mapXY(short &, short &);

public:
    static void init();
    static void cls();
    static void cls(short, short, short, short);
	static COORD getSize();
    static void waitInput(InputHandler *);
    static void GotoXY(short, short);
    static void changeTextColor(short);
    static void changeTextAndDraw(std::string &, short, short);
    static void drawObject(const std::string, int, int);
    static void drawFrame(short, short, short, short);
    static void clearFrame(short, short, short, short);
    static void write(short, short, std::string);
    static void write(short, short, std::string, int);
    static void write(short, short, char, int);
    static void draw();
    static void destroy();
};

#endif // !CONSOLE_H