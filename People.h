#ifndef PEOPLE_H
#define PEOPLE_H

#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include "Animal.h"
#include "Vehicle.h"
using namespace std;

class CPEOPLE
{
	int mX, mY;
	bool mState; // trang thai song chet
	vector<string> Object;
	int numPlay;
public:
	CPEOPLE();
	void draw();
	void removeDraw();
	void move(char input,int val);
	void Up(int val);
	void Left(int val);
	void Right(int val);
	void Down(int val);
	bool isImpact(const CVEHICLE *&);
	bool isImpact(const CANIMAL *&);
	bool isFinish();
	bool isDead();
};

#endif /* People.h *
