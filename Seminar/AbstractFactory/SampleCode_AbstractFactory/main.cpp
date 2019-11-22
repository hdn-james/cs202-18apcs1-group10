#include "FactoryProducer.h"
using namespace std;

int main()
{
    FactoryProducer FP;
    AbstractFactory *a = FP.getFactory();
    Shape *s1 = a->getShape();
    s1->draw();
    FactoryProducer FP1;
    AbstractFactory *a1 = FP1.getFactory();
    Shape *s2 = a1->getShape();
    s2->draw();
    return 0;
}
