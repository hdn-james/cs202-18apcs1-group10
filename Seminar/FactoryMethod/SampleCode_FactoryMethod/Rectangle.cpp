#include "Rectangle.h"
using namespace std;

Rectangle::Rectangle()
{
    width = 0;
    height = 0;
}

void Rectangle::input()
{
    cout << "Rectangle" << endl;
    float x, y;
    cout << "Top Left: ";
    cin >> x >> y;
    topLeft.set(x, y);
    cout << "Width: ";
    cin >> this->width;
    cout << "Height: ";
    cin >> this->height;
}

float Rectangle::calcArea()
{
    return width * height;
}
