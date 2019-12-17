#include "People.h"

People::People(int x, int y, int attr)
{
    Object::absX = Object::_x = x;
    Object::absY = Object::_y = y;
    Object::attr = attr;
    Object::width = 7;
    Object::height = 5;
    Object::show = false;
}

void People::draw()
{
    std::stringstream people;
    people
        << char(32) << char(32) << char(222) << char(219) << char(221) << char(32) << char(32) << "\n"
        << char(220) << char(220) << char(220) << char(219) << char(220) << char(220) << char(220) << "\n"
        << char(219) << char(222) << char(219) << char(219) << char(219) << char(221) << char(219) << "\n"
        << char(32) << char(222) << char(219) << char(219) << char(219) << char(221) << char(32) << "\n"
        << char(32) << char(32) << char(219) << char(32) << char(219) << char(32) << char(32);

    Console::write(Object::_x, Object::_y, people.str(), Object::attr);
    Object::show = true;
}

void People::drawReverse() { draw(); }

int People::type() const { return Object::people; }
