#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <vector>

#include "Shape.h"
#include "AbstractFactory.h"

class ShapeFactory : public AbstractFactory
{
private:
public:
    Shape *getShape();
};

#endif /* SHAPEFACTORY_H */