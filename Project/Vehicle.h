#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>

#include "Console.h"
using namespace std;

class CVEHICLE
{
	int mX, mY;

public:
	virtual void moveLeft(int, int);
	virtual void moveRight(int, int);
	virtual void deleteObject(int, int);
};

class CTRUCK : public CVEHICLE
{
private:
	char a = 220, b = 219;
	std::string truckToLeft;  // ▄███
	std::string truckToRight; // ███▄

public:
	CTRUCK();
	void moveLeft(int, int);
	void moveRight(int, int);
	void deleteObject(int, int);
};

class CCAR : public CVEHICLE
{
private:
	char a = 220, b = 219;
	std::string car; //▄██▄

public:
	CCAR();
	void moveLeft(int, int);
	void moveRight(int, int);
	void deleteObject(int, int);
};

#endif /* Vehicle.h */