#include "Animal.h"
#include "GraphicsHandler.h"
using namespace std;

void CANIMAL::moveLeft(int x, int y) {}

void CANIMAL::moveRight(int x, int y) {}

void CANIMAL::deleteObject(int x, int y)
{
    GotoXY(x, y);
    cout << "   ";
}

CDINAUSOR::CDINAUSOR()
{
    dinausorToLeft.push_back(c);
    dinausorToLeft.push_back(a);
    dinausorToLeft.push_back(b);
    dinausorToRight.push_back(b);
    dinausorToRight.push_back(a);
    dinausorToRight.push_back(c);
}

void CDINAUSOR::moveLeft(int x, int y)
{
    deleteObject(x, y);
    GotoXY(x - 1, y);
    cout << dinausorToLeft;
}

void CDINAUSOR::moveRight(int x, int y)
{
    deleteObject(x, y);
    GotoXY(x + 1, y);
    cout << dinausorToRight;
}

void CDINAUSOR::deleteObject(int x, int y)
{
    CANIMAL::deleteObject(x, y);
}

CBIRD::CBIRD()
{
    bird.push_back(a);
    bird.push_back(b);
    bird.push_back(a);
}

void CBIRD::moveLeft(int x, int y) {
    deleteObject(x, y);
    GotoXY(x - 1, y);
    cout << bird;
}

void CBIRD::moveRight(int x, int y) {
    deleteObject(x, y);
    GotoXY(x + 1, y);
    cout << bird;
}

void CBIRD::deleteObject(int x, int y)
{
    CANIMAL::deleteObject(x, y);
}