#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include "Shape.h"

class Rectangle : public Shape
{
private:
    Point topLeft;
    float width;
    float height;

public:
    Rectangle();

    void input();
    float calcArea();
};

#endif /* RECTANGLE_H */