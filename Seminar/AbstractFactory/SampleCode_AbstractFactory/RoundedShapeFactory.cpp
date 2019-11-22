#include "RoundedShapeFactory.h"
using namespace std;

Shape *RoundedShapeFactory::getShape()
{
    return Shape::initShape(2);
}
