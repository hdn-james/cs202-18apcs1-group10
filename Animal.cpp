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

/* CDINAUSOR::CDINAUSOR()
{
	this->dinausorToLeft.push_back(c);
	this->dinausorToLeft.push_back(a);
	this->dinausorToLeft.push_back(b);
	this->dinausorToRight.push_back(b);
	this->dinausorToRight.push_back(a);
	this->dinausorToRight.push_back(c);
} */

void CDINOSAUR::moveLeft(int x)
{
	deleteObject();
	this->mX -= x;
	GotoXY(this->mX, this->mY);
	DrawObject("dinosaur_left", this->mX, this->mY);
}

void CDINOSAUR::moveRight(int x)
{
	deleteObject();
	this->mX += x;
	DrawObject("dinosaur_right", this->mX, this->mY);
}

void CDINOSAUR::deleteObject()
{
	CANIMAL::deleteObject();
}

/* CBIRD::CBIRD()
{
	this->bird.push_back(a);
	this->bird.push_back(b);
	this->bird.push_back(a);
} */

void CBIRD::moveLeft(int x)
{
	deleteObject();
	this->mX -= x;
	DrawObject("bird_left", this->mX, this->mY);
}

void CBIRD::moveRight(int x)
{
	deleteObject();
	this->mX += x;
	DrawObject("bird_right", this->mX, this->mY);
}

void CBIRD::deleteObject()
{
	CANIMAL::deleteObject();
}