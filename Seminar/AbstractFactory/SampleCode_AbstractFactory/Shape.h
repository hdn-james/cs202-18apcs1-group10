#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <string>

class Shape
{
private:
public:
    static Shape* initShape(int);
    virtual void draw() = 0;
};

#endif /* SHAPE_H */