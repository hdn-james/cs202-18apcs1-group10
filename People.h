#ifndef PEOPLE_H
#define PEOPLE_H

#include "Object.h"

class People : public Object
{
public:
    People(int x = 0, int y = 0, int attr = 15);

    void draw();
    void drawReverse();
    
    int type() const;
};

#endif // !PEOPLE_H
