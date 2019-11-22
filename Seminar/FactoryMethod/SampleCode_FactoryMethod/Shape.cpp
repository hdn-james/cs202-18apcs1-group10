#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
using namespace std;

Point::Point(float x, float y)
{
    this->x = x;
    this->y = y;
}

Point::Point()
{
    this->x = 0;
    this->y = 0;
}

void Point::set(float x, float y)
{
    this->x = x;
    this->y = y;
}

Shape *Shape::initShape(int type)
{
    if (type == 1)
        return new Rectangle;
    else if (type == 2)
        return new Circle;
    else return nullptr;
}
