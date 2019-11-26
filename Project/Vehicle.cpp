#include "Vehicle.h"
using namespace std;

void CVEHICLE::moveLeft(int x, int y) {}

void CVEHICLE::moveRight(int x, int y) {}

void CVEHICLE::deleteObject(int x, int y)
{
    GotoXY(x, y);
    cout << "    ";
}

CTRUCK::CTRUCK()
{
    truckToLeft.push_back(a);
    truckToLeft.push_back(b);
    truckToLeft.push_back(b);
    truckToLeft.push_back(b);
    truckToRight.push_back(b);
    truckToRight.push_back(b);
    truckToRight.push_back(b);
    truckToRight.push_back(a);
}

void CTRUCK::moveLeft(int x, int y)
{
    deleteObject(x, y);
    GotoXY(x - 1, y);
    cout << truckToLeft;
}

void CTRUCK::moveRight(int x, int y)
{
    deleteObject(x, y);
    GotoXY(x + 1, y);
    cout << truckToRight;
}

void CTRUCK::deleteObject(int x, int y)
{
    CVEHICLE::deleteObject(x, y);
}

CCAR::CCAR()
{
    car.push_back(a);
    car.push_back(b);
    car.push_back(b);
    car.push_back(a);
}

void CCAR::moveLeft(int x, int y) {
    deleteObject(x, y);
    GotoXY(x - 1, y);
    cout << car;
}

void CCAR::moveRight(int x, int y) {
    deleteObject(x, y);
    GotoXY(x + 1, y);
    cout << car;
}

void CCAR::deleteObject(int x, int y)
{
    CVEHICLE::deleteObject(x, y);
}