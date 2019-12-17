#include "UISidePanel.h"

#include "../Console/Console.h"
#include "../Console/Config.h"
#include "../Console/Utilities.h"

#include <sstream>

UISidePanel *UISidePanel::_instance = nullptr;
UISidePanel *UISidePanel::getInstance()
{
    if (_instance == nullptr)
        _instance = new UISidePanel();
    return _instance;
}

UISidePanel::UISidePanel()
{
    using namespace Utilities;
    _x = 0;
    _y = 0;
    _width = 33;
    _height = 47;
    _info = "";
}

UISidePanel::~UISidePanel()
{
}

void UISidePanel::setInfo(std::string info)
{
    _info = info;
}

void UISidePanel::writeHeader(short y, std::string header, short attr)
{
    using namespace Utilities;
    auto charsPixel = getPixelChars();
    Console::write(_x + _width, y, charsPixel.full, Color::Yellow);
    Console::write(_x + _width, y + 2, charsPixel.full, Color::Yellow);
    for (short i = 0; i < _width; i++)
    {
        Console::write(_x + i, y, charsPixel.bottom, Color::Yellow);
        Console::write(_x + i, y + 2, charsPixel.top, Color::Yellow);
    }
    Console::write(_x, y + 1, alignText(TextAlign::center, header, 33), attr);
}

void UISidePanel::writeInfo(short inX, short inY, std::string text, int attr)
{
    Console::write(_x + inX, _y  + 28 + inY, text, attr);
}

void UISidePanel::clsInfo()
{
    Console::cls(_x, _y + 29, _width, 8);
}

void UISidePanel::writeInstruct(short inX, short inY, std::string text, int attr)
{
    Console::write(_x + inX, _y + 11 + inY, text, attr);
}

void UISidePanel::clsInstruct() { Console::cls(_x, _y + 12, _width, 15); }

bool UISidePanel::onKeyPressed(unsigned short key) { return false; }

void UISidePanel::draw()
{
    using namespace Utilities;
    cls();
	writeHeader(_y + 26, "INFORMATION");
	writeHeader(_y + 34, "");
	writeInfo(0, 2, _info, Color::DarkGray);
    writeHeader(_y + 9, "INSTRUCTION");

    writeInstruct(0, 2,
                      alignText(center, std::string("         CONTROL          \n"), _width),
                  Color::White);
    writeInstruct(0, 3,         
                      alignText(center, std::string("     Use Arrow key        \n"), _width) +
                      alignText(center, std::string("       to move            \n"), _width),              
                  Color::DarkGray);
    writeInstruct(0, 7,
                      alignText(center, std::string("          SETTING         \n"), _width),
                  Color::White);
    writeInstruct(0, 8,
                      alignText(center, std::string("     Save game: L         \n"), _width) +
                      alignText(center, std::string("     Load game: T         \n"), _width) +
                      alignText(center, std::string("     Pause/Continue: P    \n"), _width) +
                      alignText(center, std::string("     Mute/Unmute: M       \n"), _width) +
                      alignText(center, std::string("     Menu: Esc            \n"), _width),
                  Color::DarkGray);
    for (int i = _y; i < _height; ++i)
    {
        Console::write(_x + _width, i, Utilities::getPixelChars().full, Utilities::Color::Yellow);
    }
	Console::drawObject("Object/Draw/bird.txt", 5, 2);
	Console::drawObject("Object/Draw/birdR.txt", 21, 2);
	Console::drawObject("Object/Draw/dinosaur.txt", 5, 40);
	Console::drawObject("Object/Draw/dinosaurR.txt", 21, 40);
}