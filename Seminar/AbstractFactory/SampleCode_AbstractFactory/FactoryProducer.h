#ifndef FACTORYPRODUCER_H
#define FACTORYPRODUCER_H

#include <vector>

#include "AbstractFactory.h"

class FactoryProducer
{
private:

public:
    AbstractFactory *getFactory();
};

#endif /* FACTORYPRODUCER_H */