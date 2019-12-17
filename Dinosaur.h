#ifndef DINOSAUR_H
#define DINOSAUR_H

#include "Object.h"

class Dinosaur : public Object
{
public:
	Dinosaur(int x = 0, int y = 0, int attr = 15);

	void draw();
	void drawReverse();

	int type() const;
};

#endif // !DINOSAUR_H
