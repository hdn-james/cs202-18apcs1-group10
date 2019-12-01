#include "Shape.h"
#include "Rectangle.h"
#include "RoundedRectangle.h"
using namespace std;

void Shape::draw()
{
#ifdef RECTANGLE
    Shape *shape = new Rectangle;
#else
    Shape *shape = new RoundedRectangle;
#endif
    shape->draw();
}