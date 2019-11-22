#include "ShapeArray.h"
using namespace std;

void ShapeArray::input()
{
    int size;
    int type;
    Shape *p = nullptr;
    cout << "How many Shape: ";
    cin >> size;
    for (int i = 0; i < size; i++)
    {
        do
        {
            cout << "1: Rectangle; 2: Circle" << endl;
            cin >> type;
        } while (type < 1 || type > 2);
        if (type == 1)
            p = Shape::initShape(type);
        else if (type == 2)
            p = Shape::initShape(type);
        cin.ignore(1);
        p->input();
        shape.push_back(p);
    }
}

void ShapeArray::outputArea()
{
    for (int i = 0; i < shape.size(); i++)
    {
        cout << "Area: " << shape[i]->calcArea() << endl;
    }
}
