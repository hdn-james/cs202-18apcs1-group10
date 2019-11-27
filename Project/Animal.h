#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <vector>

#include "Console.h"
using namespace std;

class CANIMAL
{
protected:
	int mX, mY;

public:
	virtual void moveLeft(int);
	virtual void moveRight(int);
	virtual void deleteObject();

	virtual void Tell();
};

class CDINAUSOR : public CANIMAL
{
private:
	char a = 219, b = 220, c = 223; // █ ▄ ▀
	std::string dinausorToLeft;
	std::string dinausorToRight;

public:
	CDINAUSOR();
	void moveLeft(int);
	void moveRight(int);
	void deleteObject();

	virtual void Tell();
};

class CBIRD : public CANIMAL
{
private:
	char a = 223, b = 254; // ▀■▀
	std::string bird;

public:
	CBIRD();
	void moveLeft(int);
	void moveRight(int);
	void deleteObject();

	virtual void Tell();
};

#endif /* Animal.h */