#include "ShapeFactory.h"
using namespace std;

Shape *ShapeFactory::getShape()
{
    return Shape::initShape(1);
}
