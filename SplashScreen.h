#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#define SS_CAR "UserInterface/SplashScreen/SS-car.txt"
#define SS_NAME "UserInterface/SplashScreen/SS-name.txt"
#define SS_LOAD "UserInterface/SplashScreen/SS-loading"
#define txt ".txt"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <stdio.h>

#include "../Console/Console.h"
#include "../Console/Utilities.h"


class SplashScreen 
{
public:
	void draw();
};

#endif // !SPLASHSCREEN_H
