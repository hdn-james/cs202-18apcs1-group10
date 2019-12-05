#include "Animal.h"
#include "GraphicsHandler.h"
using namespace std;


void CANIMAL::moveLeft(int x) {}

void CANIMAL::moveRight(int x) {}

void CANIMAL::deleteObject()
{
	GotoXY(mX, mY);
	cout << "   ";
}

CDINAUSOR::CDINAUSOR()
{
	this->dinausorToLeft.push_back(c);
	this->dinausorToLeft.push_back(a);
	this->dinausorToLeft.push_back(b);
	this->dinausorToRight.push_back(b);
	this->dinausorToRight.push_back(a);
	this->dinausorToRight.push_back(c);
}

void CDINAUSOR::moveLeft(int x)
{
	deleteObject();
	this->mX -= x;
	GotoXY(this->mX, this->mY);
	//cout << this->dinausorToLeft;
	for (int i = 0; i < this->dinausorToLeft.size(); i++)
		cout << this->dinausorToLeft[i];
}

void CDINAUSOR::moveRight(int x)
{
	deleteObject();
	this->mX += x;
	GotoXY(this->mX, this->mY);
	//cout << this->dinausorToRight;
	for (int i = 0; i < this->dinausorToRight.size(); i++)
		cout << this->dinausorToRight[i];
}

void CDINAUSOR::deleteObject()
{
	CANIMAL::deleteObject();
}

CBIRD::CBIRD()
{
	this->bird.push_back(a);
	this->bird.push_back(b);
	this->bird.push_back(a);
}

void CBIRD::moveLeft(int x)
{
	deleteObject();
	this->mX -= x;
	GotoXY(this->mX, this->mY);
	//cout << this->bird;
	for (int i = 0; i < this->bird.size(); i++)
		cout << this->bird[i];
}

void CBIRD::moveRight(int x)
{
	deleteObject();
	this->mX += x;
	GotoXY(this->mX, this->mY);
	//cout << this->bird;
	for (int i = 0; i < this->bird.size(); i++)
		cout << this->bird[i];
}

void CBIRD::deleteObject()
{
	CANIMAL::deleteObject();
}