#include "Bird.h"
using namespace std;

Bird::Bird(int x, int y, int attr)
{
    Object::absX = Object::_x = x;
    Object::absY = Object::_y = y;
    Object::attr = attr;
    Object::width = 7;
    Object::height = 5;
    Object::show = false;
}

void Bird::draw()
{
    if (Object::veX < 0)   
        return drawReverse();  
    Console::drawObject(BIRD, Object::_x, Object::_y);
    Object::show = true;
}

void Bird::drawReverse()
{
    Console::drawObject(BIRD_REVERSE, Object::_x, Object::_y);
    Object::show = true;
}

int Bird::type() const { return Object::bird; }