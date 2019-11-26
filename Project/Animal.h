#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <vector>

#include "Console.h"
using namespace std;

class CANIMAL
{
	int mX, mY;

public:
	virtual void moveLeft(int, int);
	virtual void moveRight(int, int);
	virtual void deleteObject(int, int);

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
	void moveLeft(int, int);
	void moveRight(int, int);
	void deleteObject(int, int);

	virtual void Tell();
};

class CBIRD : public CANIMAL
{
private:
	char a = 223, b = 254; // ▀■▀
	std::string bird;

public:
	CBIRD();
	void moveLeft(int, int);
	void moveRight(int, int);
	void deleteObject(int, int);

	virtual void Tell();
};

#endif /* Animal.h */