#ifndef CAR_H
#define CAR_H

#include "Object.h"

class Car : public Object
{
public:
    Car(int x = 0, int y = 0, int attr = 15);

    void draw();
    void drawReverse();

    int type() const;
};

#endif // !CAR_H
