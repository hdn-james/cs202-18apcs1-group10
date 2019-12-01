#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include "Shape.h"

class Circle : public Shape
{
private:
    Point center;
    float radius;

public:
    Circle();

    void input();
    float calcArea();
};

#endif /* CIRCLE_H */