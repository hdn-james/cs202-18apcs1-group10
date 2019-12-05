#include "People.h"

CPEOPLE::CPEOPLE()
{
	
}

void CPEOPLE::deleteObject()
{
	GotoXY(mX, mY);
	cout << "    ";
}

void CPEOPLE::drawPeople()
{
	for (int i = 0; i < people.size(); i++)
		cout << people[i];
}

void CPEOPLE::Up()
{
	deleteObject();
	this->mY -= 1;
	GotoXY(this->mX, this->mY);
	drawPeople();
}

void CPEOPLE::Down()
{
	deleteObject();
	this->mY += 1;
	GotoXY(this->mX, this->mY);
	drawPeople();
}

void CPEOPLE::Left()
{
	deleteObject();
	this->mX -= 1;
	GotoXY(this->mX, this->mY);
	drawPeople();
}

void CPEOPLE::Right()
{
	deleteObject();
	this->mX += 1;
	GotoXY(this->mX, this->mY);
	drawPeople();
}