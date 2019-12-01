#include <iostream>
#include <vector>

#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
using namespace std;

int main()
{
    vector<Shape *> shape;
    int type;

    while (true)
    {
        cout << "1: Rectangle, 2: Circle, 3: Exit" << endl;
        cin >> type;
        if (type == 1)
            shape.push_back(new Rectangle);
        else if (type == 2)
            shape.push_back(new Circle);
        else if (type == 3)
            break;
    }

    for (int i = 0; i < shape.size(); i++)
    {
        shape[i]->input();
        shape[i]->calcArea();
    }

    for (int i = 0; i < shape.size(); i++)
    {
        delete shape[i];
    }

    return 0;
}