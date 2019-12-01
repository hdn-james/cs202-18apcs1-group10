#include "Shape.h"
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
