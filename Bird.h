#ifndef DOG_H
#define DOG_H

#include "Object.h"

class Bird : public Object
{
public:
    Bird(int x = 0, int y = 0, int attr = 15);

    void draw();
    void drawReverse();

    int type() const;
};

#endif // !DOG_H
