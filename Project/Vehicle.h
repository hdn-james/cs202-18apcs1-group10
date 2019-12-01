#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>

#include "Console.h"
using namespace std;

class CVEHICLE
{
protected:
	int mX, mY;

public:
	virtual void moveLeft(int);
	virtual void moveRight(int);
	virtual void deleteObject();
};

class CTRUCK : public CVEHICLE
{
private:
	char a = 220, b = 219;
	std::string truckToLeft;  // ▄███
	std::string truckToRight; // ███▄

public:
	CTRUCK();
	void moveLeft(int);		// move to left (int x)
	void moveRight(int);	// same as move to left
	void deleteObject();
};

class CCAR : public CVEHICLE
{
private:
	char a = 220, b = 219;
	std::string car; //▄██▄

public:
	CCAR();
	void moveLeft(int);
	void moveRight(int);
	void deleteObject();
};

#endif /* Vehicle.h */