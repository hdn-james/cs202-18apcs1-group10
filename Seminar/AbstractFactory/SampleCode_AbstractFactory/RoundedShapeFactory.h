#ifndef ROUNDEDSHAPEFACTORY_H
#define ROUNDEDSHAPEFACTORY_H

#include <vector>

#include "Shape.h"
#include "AbstractFactory.h"

class RoundedShapeFactory : public AbstractFactory
{
private:
public:
    Shape *getShape();
};

#endif /* ROUNDEDSHAPEFACTORY_H */