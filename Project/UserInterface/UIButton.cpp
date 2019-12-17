#include "UIButton.h"
#include "../Console/Console.h"
#include "../Console/Utilities.h"
#include "../Console/Config.h"
using namespace std;

UIButton::UIButton(int x, int y, std::string label)
{
    UI::_x = x;
    UI::_y = y;
    UI::_width = UI::_height = 0;
    UIButton::label = label;

    int pos;
    int last = 0;
    std::string s = label + '\n';
    while ((pos = s.find_first_of('\n', last)) != std::string::npos)
    {
        _height++;
        if (pos - last > _width)
            _width = pos - last;
        last = pos + 1;
    }
}

void UIButton::draw()
{
    Console::write(_x, _y, label, _hover ? Utilities::color(Utilities::Color::Black, Utilities::Color::Yellow) : Utilities::Color::Yellow);
    _show = true;
}

bool UIButton::onKeyPressed(unsigned short key)
{
    if (key == Config::key_enter)
        return true;
    return false;
}