#include "Console.h"
#include "Config.h"
#include "Utilities.h"

#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

HANDLE Console::_hStdin;
HANDLE Console::_hStdout;
HWND Console::_consoleWindows;
size_t Console::_bufferSize;
CHAR_INFO *Console::_buffer;
CONSOLE_SCREEN_BUFFER_INFO Console::_info;
CONSOLE_CURSOR_INFO Console::_cInfo;

void ThrowError(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	ExitProcess(0);
}

void Console::mapXY(short &x, short &y)
{
	if (x < 0)
		x = _info.dwMaximumWindowSize.X + x;
	if (y < 0)
		y = _info.dwMaximumWindowSize.Y + y;
}

void Console::init()
{
	_hStdin = GetStdHandle(STD_INPUT_HANDLE);
	_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (_hStdout == INVALID_HANDLE_VALUE || _hStdin == INVALID_HANDLE_VALUE)
		ThrowError("GetStdHandle Error");
	_consoleWindows = GetConsoleWindow();

	if (!SetConsoleTitleA("Cross the road by NHN"))
		ThrowError("SetConsoleTitle Error");

	// Set window size
	if (!MoveWindow(_consoleWindows,
					0, 0,
					Config::get(Config::console_width),
					Config::get(Config::console_height),
					TRUE))
		ThrowError("MoveWindow Error");

	// Hide Cursor
	_cInfo.bVisible = FALSE;
	_cInfo.dwSize = 20;
	if (!SetConsoleCursorInfo(_hStdout, &_cInfo))
		ThrowError("SetCursorHide Error");

	// Unresizable
	auto style = GetWindowLongA(_consoleWindows, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLongA(_consoleWindows, GWL_STYLE, style);

	// Unscrollable
	if (!GetConsoleScreenBufferInfo(_hStdout, &_info))
		ThrowError("GetConsoleScreenBufferInfo Error");
	COORD new_size{
		static_cast<short>(_info.srWindow.Right - _info.srWindow.Left + 1),
		static_cast<short>(_info.srWindow.Bottom - _info.srWindow.Top + 1)};
	_info.dwMaximumWindowSize = new_size;
	if (!SetConsoleScreenBufferSize(_hStdout, new_size))
		ThrowError("SetConsoleScreenBufferSize");

	_bufferSize = new_size.X * new_size.Y;
	_buffer = new CHAR_INFO[_bufferSize];
	cls();
}

void Console::cls()
{
	for (size_t i = 0; i < _bufferSize; i++)
	{
		_buffer[i].Attributes = 0;
		_buffer[i].Char.AsciiChar = ' ';
	}
}

void Console::cls(short x, short y, short width, short height)
{
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			if (x + i + 1 > _info.dwMaximumWindowSize.X)
				break;

			if (y + j + 1 > _info.dwMaximumWindowSize.Y)
				break;

			_buffer[(x + i) + (y + j) * _info.dwMaximumWindowSize.X].Attributes = 0;
			_buffer[(x + i) + (y + j) * _info.dwMaximumWindowSize.X].Char.AsciiChar = ' ';
		}
	}
}

COORD Console::getSize() { return _info.dwMaximumWindowSize; }

void Console::waitInput(InputHandler *inputHandler)
{
	static DWORD cNumRead, i;
	static COORD cursorPos = {0, 0};
	static INPUT_RECORD irInBuf[128];

	auto handleKeyEvent = [&inputHandler](KEY_EVENT_RECORD ker) {
		if (ker.bKeyDown)
			inputHandler->onKeyPressed(ker.wVirtualKeyCode);
	};
	PeekConsoleInput(_hStdin, irInBuf, 128, &cNumRead);
	if (cNumRead == 0)
		return;

	if (!ReadConsoleInput(_hStdin, irInBuf, 128, &cNumRead))
		ThrowError("ReadConsoleInput");

	for (i = 0; i < cNumRead; i++)
	{
		switch (irInBuf[i].EventType)
		{
		case KEY_EVENT:
			handleKeyEvent(irInBuf[i].Event.KeyEvent);
			break;
		case WINDOW_BUFFER_SIZE_EVENT:
		case FOCUS_EVENT:
		case MENU_EVENT:
			break;
		default:
			ThrowError("Unknown event type");
			break;
		}
	}
};

void Console::changeTextColor(short color)
{
	_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(_hStdout, color);
	return;
}

void Console::changeTextAndDraw(string &s, short x, short y)
{
	int color = 15;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == 'B')
			color = Utilities::Color::Cyan;
		else if (s[i] == 'b')
			color = Utilities::Color::LightCyan;
		else if (s[i] == 'W')
			color = Utilities::Color::White;
		else if (s[i] == 'R')
			color = Utilities::Color::Red;
		else if (s[i] == 'r')
			color = Utilities::Color::LightRed;
		else if (s[i] == 'Y')
			color = Utilities::Color::Yellow;
		else if (s[i] == 'G')
			color = Utilities::Color::Green;
		else if (s[i] == 'g')
			color = Utilities::Color::LightGreen;
		if (s[i] != ' ')
			s[i] = char(219);
		write(x + i, y, s[i], color);
	}
}

void Console::drawObject(const string path, int x, int y)
{
	ifstream file(path);
	int tmp = 0;
	string s[20];
	while (getline(file, s[tmp]))
		++tmp;
	for (int i = 0; i < tmp; i++)
		changeTextAndDraw(s[i], x, y + i);
	file.close();
	return;
}

void Console::drawFrame(short x, short y, short height, short width)
{
	for (short i = 0; i <= height + 1; i++)
		for (short j = 0; j <= width + 1; j++)
		{
			GotoXY(x + j, y + i);
			if ((i == 0) && (j == 0))
			{
				cout << char(218);
				continue;
			}
			if ((i == 0) && (j == width + 1))
			{
				cout << char(191);
				continue;
			}
			if ((i == height + 1) && (j == 0))
			{
				cout << char(192);
				continue;
			}
			if ((i == height + 1) && (j == width + 1))
			{
				cout << char(217);
				continue;
			}
			if ((i == 0) || (i == height + 1))
				cout << char(196);
			if ((j == 0) || (j == width + 1))
				cout << char(179);
		}
}

void Console::clearFrame(short x, short y, short height, short width)
{
	for (short i = y; i <= y + height + 1; i++)
	{
		GotoXY(x, i);
		for (short j = x; j <= x + width + 1; j++)
			cout << " ";
	}
}

void Console::GotoXY(short x, short y)
{
	static COORD cursor;
	mapXY(x, y);
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(_hStdout, cursor);
}

void Console::write(short x, short y, string str)
{
	write(x, y, str, Utilities::Color::White);
}

void Console::write(short x, short y, string str, int attr)
{
	mapXY(x, y);
	str.append("\n");
	size_t i, j = 0;
	size_t offset, pos, last = 0;
	std::string temp;
	while ((pos = str.find_first_of('\n', last)) != std::string::npos)
	{
		temp = str.substr(last, pos - last);

		if (temp.length() > 0)
		{
			offset = x + (y + j) * _info.dwMaximumWindowSize.X;
			for (i = 0; i < temp.length(); i++)
			{
				if (x + i + 1 > _info.dwMaximumWindowSize.X)
					break;
				_buffer[offset + i].Char.AsciiChar = temp[i];
				_buffer[offset + i].Attributes = attr;
			}
		}

		last = pos + 1;
		j++;
	}
}

void Console::write(short x, short y, char c, int attr)
{
	mapXY(x, y);
	size_t offset = x + y * _info.dwMaximumWindowSize.X;
	_buffer[offset].Char.AsciiChar = c;
	_buffer[offset].Attributes = attr;
}

void Console::draw()
{
	static COORD p0{0, 0};
	static SMALL_RECT writeArea{
		0, 0,
		Config::get(Config::console_width),
		Config::get(Config::console_height)};

	WriteConsoleOutputA(
		_hStdout, _buffer,
		_info.dwMaximumWindowSize,
		p0, &writeArea);
}

void Console::destroy() { delete _buffer; }