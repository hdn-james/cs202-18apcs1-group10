#include "Circle.h"
using namespace std;

Circle::Circle()
{
    radius = 0;
}

void Circle::input()
{
    cout << "Circle" << endl;
    cout << "Center: ";
    float x, y;
    cin >> x >> y;
    center.set(x, y);
    cout << "Radius: ";
    cin >> this->radius;
}

float Circle::calcArea()
{
    return 3.1416 * radius * radius;
}