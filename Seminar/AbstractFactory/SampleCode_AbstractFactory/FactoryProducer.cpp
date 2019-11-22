#include "FactoryProducer.h"
#include "ShapeFactory.h"
#include "RoundedShapeFactory.h"

using namespace std;

AbstractFactory *FactoryProducer::getFactory()
{
    int type;
    do
    {
        cout << "1: Rectangle, 2: Rounded Rectangle" << endl;
        cin >> type;
    } while (type < 1 || type > 2);
    if (type == 1)
        return new ShapeFactory;
    else if (type == 2)
        return new RoundedShapeFactory;
    return nullptr;
}
