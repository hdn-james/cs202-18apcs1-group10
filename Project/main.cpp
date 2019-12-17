#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <thread>

#include "Console/Config.h"
#include "Console/Console.h"
#include "Console/Utilities.h"
#include "UserInterface/UIMainMenu.h"
#include "UserInterface/UISidePanel.h"
#include "UserInterface/UIGame.h"
#include "UserInterface/UIPopUp.h"
#include "UserInterface/SplashScreen.h"

#define console_config "Config/config.ini"

using namespace std;
using namespace Utilities;

void ProgramStart()
{
	Config::load(console_config);
	Console::init();

	SplashScreen* SS = nullptr;
	SS->draw();	

	UISidePanel* panel = UISidePanel::getInstance();
	panel->show();

	UIMainMenu* menu = UIMainMenu::getInstance();
	menu->show();

	mciSendString("open \"Sounds/background1.mp3\" type mpegvideo alias mp3", NULL, 0, 0);
	mciSendString("play mp3 repeat", NULL, 0, 0);


	while (menu->isShowing())
	{
		//SS->draw();
		Console::waitInput(menu);
		menu->draw();

		panel->setInfo(
			  alignText(center, std::string("Huynh Dai Nhan \n"), panel->width())
			+ alignText(center, std::string("Pham Quoc Huy  \n"), panel->width())
			+ alignText(center, std::string("Le Hoang Nhi   \n"), panel->width()));
		panel->draw();
		Console::draw();
		Sleep(Config::get(Config::frame_length));
	}
}

int main()
{
	ProgramStart();
	return 0;
}