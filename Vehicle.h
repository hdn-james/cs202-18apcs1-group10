#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
using namespace std;

class CVEHICLE
{
	int mX, mY;

public:
	virtual void Move(int, int);
	//...
};

class CTRUCK : public CVEHICLE
{
public:
	//...
};

class CCAR : public CVEHICLE
{
public:
	//...
};

#endif /* Vehicle.h */