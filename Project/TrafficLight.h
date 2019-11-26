#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <iostream>
using namespace std;
#include <vector>

#include "Console.h"

class TrafficLight
{
public:
private:
	bool color; // true: green false: red
    char a = 219;
	std::vector<char> light;

public:
	TrafficLight();
	void redLight(int, int);
	void greenLight(int, int);
};

#endif /* TrafficLight.h */