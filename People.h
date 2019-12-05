#ifndef PEOPLE_H
#define PEOPLE_H

#include <iostream>
#include "Animal.h"
#include "Vehicle.h"
using namespace std;

class CPEOPLE
{
	int mX, mY;
	bool mState; // trang thai song chet
	string people;
public:
	CPEOPLE();
	void Up();
	void Left();
	void Right();
	void Down();
	bool isImpact(const CVEHICLE *&);
	bool isImpact(const CANIMAL *&);
	bool isFinish();
	bool isDead();
	void deleteObject();
	void drawPeople();
};

#endif /* People.h */