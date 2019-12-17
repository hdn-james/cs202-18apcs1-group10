#include "Dinosaur.h"
using namespace std;

Dinosaur::Dinosaur(int x, int y, int attr)
{
    Object::absX = Object::_x = x;
    Object::absY = Object::_y = y;
    Object::attr = attr;
    Object::width = 9;
    Object::height = 5;
    Object::show = false;
}

void Dinosaur::draw()
{
    if (Object::veX < 0)    
        return drawReverse();    
    Console::drawObject(DINOSAUR, Object::_x, Object::_y);
    Object::show = true;
}

void Dinosaur::drawReverse()
{
    Console::drawObject(DINOSAUR_REVERSE, Object::_x, Object::_y);
    Object::show = true;
}

int Dinosaur::type() const { return Object::dinosaur; }