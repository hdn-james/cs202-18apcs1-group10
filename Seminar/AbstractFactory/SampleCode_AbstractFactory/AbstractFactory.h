#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "Shape.h"

class AbstractFactory
{
private:
public:
    virtual Shape *getShape() = 0;
};

#endif /* ABSTRACTFACTORY_H */