#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>

class Point
{
private:
    float x, y;

public:
    Point(float, float);
    Point();
    ~Point();

    void set(float, float);
};

class Shape
{
public:
    virtual void input() = 0;
    virtual float calcArea() = 0;
};

#endif /* SHAPE_H */
