#include "Car.h"
using namespace std;

Car::Car(int x, int y, int attr)
{
    Object::absX = Object::_x = x;
    Object::absY = Object::_y = y;
    Object::attr = attr;
    Object::width = 9;
    Object::height = 4;
    Object::show = false;
}

void Car::draw()
{
    if (Object::veX < 0)
        return drawReverse();
    Console::drawObject(CAR, Object::_x, Object::_y);
    show = true;
}

void Car::drawReverse()
{
    Console::drawObject(CAR, Object::_x, Object::_y);
    show = true;
}

int Car::type() const { return Object::car; }
