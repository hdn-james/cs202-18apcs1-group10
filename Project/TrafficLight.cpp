#include "TrafficLight.h"
#include "GraphicsHandler.h"
using namespace std;

TrafficLight::TrafficLight()
{
    light.resize(2);
    light[0] = a;
    light[1] = a;
}

void TrafficLight::redLight(int x, int y)
{
    GotoXY(x, y);
    TextColor(Color_Red);
    cout << light[0];
    cout << light[1];
    TextColor(Color_DarkGreen);
    cout << light[2];
    cout << light[3];
    TextColor(default_Color);
}

void TrafficLight::greenLight(int x, int y)
{
    GotoXY(x, y);
    TextColor(Color_DarkRed);
    cout << light[0];
    cout << light[1];
    TextColor(Color_Green);
    cout << light[2];
    cout << light[3];
    TextColor(default_Color);
}