#include "Truck.h"
using namespace std;

Truck::Truck(int x, int y, int attr)
{
    Object::absX = Object::_x = x;
    Object::absY = Object::_y = y;
    Object::attr = attr;
    Object::width = 17;
    Object::height = 5;
    Object::show = false;
}

void Truck::draw()
{
    if (Object::veX < 0)
        return drawReverse();
    Console::drawObject(TRUCK, Object::_x, Object::_y);
    show = true;
}

void Truck::drawReverse()
{
    Console::drawObject(TRUCK_REVERSE, Object::_x, Object::_y);
    show = true;
}

int Truck::type() const { return Object::truck; }