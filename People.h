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
public:
	CPEOPLE();
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	bool isImpact(const CVEHICLE *&);
	bool isImpact(const CANIMAL *&);
	bool isFinish();
	bool isDead();
};

#endif /* People.h */