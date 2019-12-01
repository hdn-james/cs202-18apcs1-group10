#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "Console.h"
using namespace std;

class menuFunction
{
private:
	vector<string> MENU;
	int numOfItems;
	string title = R"(
 
                      _________________ _______ ________________    ______________  ____________   ________ _______ _______ ________ 
                     __  ____/___  __ \__  __ \__  ___/__  ___/    ___  __/___  / / /___  ____/   ___  __ \__  __ \___    |___  __ \
                     _  /     __  /_/ /_  / / /_____ \ _____ \     __  /   __  /_/ / __  __/      __  /_/ /_  / / /__  /| |__  / / /
                     / /___   _  _, _/ / /_/ / ____/ / ____/ /     _  /    _  __  /  _  /___      _  _, _/ / /_/ / _  ___ |_  /_/ / 
                     \____/   /_/ |_|  \____/  /____/  /____/      /_/     /_/ /_/   /_____/      /_/ |_|  \____/  /_/  |_|/_____/                
	)";

public:
	menuFunction();
	~menuFunction();

	void drawMainMenu();
	void deleteMenu();
	void drawBorder();
	void credit();
	void arrow(int, int);
	int choice();
};

int getMove();

#endif /* Menu.h */