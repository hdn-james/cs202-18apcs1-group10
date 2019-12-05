#include "Vehicle.h"
using namespace std;

void CVEHICLE::moveLeft(int x) {}

void CVEHICLE::moveRight(int x) {}

void CVEHICLE::deleteObject()
{
	GotoXY(mX, mY);
	cout << "    ";
}

CTRUCK::CTRUCK()
{
	this->truckToLeft.push_back(a);
	this->truckToLeft.push_back(b);
	this->truckToLeft.push_back(b);
	this->truckToLeft.push_back(b);
	this->truckToRight.push_back(b);
	this->truckToRight.push_back(b);
	this->truckToRight.push_back(b);
	this->truckToRight.push_back(a);
}

void CTRUCK::moveLeft(int x)
{
	deleteObject();
	this->mX -= x;
	GotoXY(this->mX, this->mY);
	//cout << truckToLeft;
	for (int i = 0; i < truckToLeft.size(); i++)
		cout << truckToLeft[i];
}

void CTRUCK::moveRight(int x)
{
	deleteObject();
	this->mX += x;
	GotoXY(this->mX, this->mY);
	//cout << truckToRight;
	for (int i = 0; i < truckToRight.size(); i++)
		cout << truckToRight[i];
}

void CTRUCK::deleteObject()
{
	CVEHICLE::deleteObject();
}

CCAR::CCAR()
{
	this->car.push_back(a);
	this->car.push_back(b);
	this->car.push_back(b);
	this->car.push_back(a);
}

void CCAR::moveLeft(int x)
{
	deleteObject();
	this->mX -= x;
	GotoXY(this->mX, this->mY);
	//cout << car;
	for (int i = 0; i < car.size(); i++)
		cout << car[i];
}

void CCAR::moveRight(int x)
{
	deleteObject();
	this->mX += x;
	GotoXY(this->mX, this->mY);
	for (int i = 0; i < car.size(); i++)
		cout << car[i];
}

void CCAR::deleteObject()
{
	CVEHICLE::deleteObject();
}