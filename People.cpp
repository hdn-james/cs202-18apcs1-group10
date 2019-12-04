#include"People.h"
#include"Console.h"

CPEOPLE::CPEOPLE()
{
	mState = true;
	mX = 70;
	mY = 35;
	numPlay = 3;
	ifstream fin;
	fin.open("People.txt");
	if (fin.is_open())
	{
		Object.clear();
		while (!fin.eof())
		{
			string tmp;
			getline(fin, tmp, '\n');
			Object.push_back(tmp);
		}
	}
	fin.close();

}

void CPEOPLE::draw()
{
	int size = Object.size();
	for (int i = 0; i < size; ++i)
	{
		GotoXY(mX, mY + i);
		cout << Object[i];
	}

}

void CPEOPLE::removeDraw()
{
	int size = Object.size();
	int length = Object[0].length();
	string null = "";
	for (int i = 0; i < length; ++i)
		null += " ";
	for (int i = 0; i < length; ++i)
	{
		GotoXY(mX, mY + i);
		cout << null;
	}
}


void CPEOPLE::move(char input, int val)
{

	if (input == 'w' || input == 'W')
		Up(val);
	else if (input == 's' || input == 'S')
		Down(val);
	else if (input == 'a' || input == 'A')
		Left(val);
	else if (input == 'd' || input == 'D')
		Right(val);
}

void CPEOPLE::Up(int val)
{
	if (mY - val >= 0)
	{
		removeDraw();
		mY -= val;
		draw();
	}
}

void CPEOPLE::Down(int val)
{
	if (mY + val <= 35)
	{
		removeDraw();
		mY += val;
		draw();
	}
}

void CPEOPLE::Left(int val)
{
	if (mX - val >= 0)
	{
		removeDraw();
		mX -= val;
		draw();
	}
}

void CPEOPLE::Right(int val)
{
	if (mX + val <= 70)
	{
		removeDraw();
		mX += val;
		draw();
	}
}


bool CPEOPLE::isFinish()
{
	if (mY == 0)
		return true;
	return false;
}

bool CPEOPLE::isImpact(const CVEHICLE*&)
{

}
bool CPEOPLE::isImpact(const CANIMAL*&)
{

}

bool CPEOPLE::isDead()
{
	if (isImpact(const CVEHICLE * &))
	{
		numPlay--;
		return true;
	}
	return false;
}





