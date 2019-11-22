#include "Shape.h"
#include "Rectangle.h"
#include "RoundedRectangle.h"
using namespace std;

Shape *Shape::initShape(int type)
{
    if (type == 1)
        return new Rectangle;
    else if (type == 2)
        return new RoundedRectangle;
    else
        return nullptr;
}