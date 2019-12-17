#ifndef TRUCK_H
#define TRUCK_H

#include "Object.h"

class Truck : public Object
{
public:
    Truck(int x = 0, int y = 0, int attr = 15);

    void draw();
    void drawReverse();

    int type() const;
};

#endif // !TRUCK_H
