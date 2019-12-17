#include "UIMainMenu.h"

#include <sstream>
#include <thread>

#include "../Console/Console.h"
#include "../Console/Config.h"
#include "../Console/Utilities.h"

using namespace std;

UIMainMenu* UIMainMenu::_instance = nullptr;
UIMainMenu* UIMainMenu::getInstance() {
	if (_instance == nullptr)
		_instance = new UIMainMenu();
	return _instance;
}

UIMainMenu::UIMainMenu(int x, int y, int width, int height) {
	using namespace Utilities;

	_show = true;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_game = UIGame::getInstance();
	TextWithBorderOptions options{ 18 };
	_buttons.push_back(UIButton(_x + (_width - 19) / 2, _y + 4 * 0 + 1, "      New Game       "));
	_buttons.push_back(UIButton(_x + (_width - 19) / 2, _y + 4 * 1 + 1, "      Continue       "));
	_buttons.push_back(UIButton(_x + (_width - 19) / 2, _y + 4 * 2 + 1, "      Load Game      "));
	_buttons.push_back(UIButton(_x + (_width - 19) / 2, _y + 4 * 3 + 1, "      Setting        "));
	_buttons.push_back(UIButton(_x + (_width - 19) / 2, _y + 4 * 4 + 1, "      Exit           "));
}

UIMainMenu::~UIMainMenu() {
	delete _instance;
}

void UIMainMenu::newGame()
{
	_game->reset();
	startGame();
}

void UIMainMenu::startGame()
{
	UIPopUp::Alert(65, 17, "                ARE YOU READY?");
	Sleep(200);

	_game->show();
	_game->Continue();
	while (_game->isShowing())
	{
		Console::waitInput(_game);
		_game->update();
		_game->draw();

		UISidePanel* panel = panel->getInstance();
		panel->draw();

		Sleep(Config::get(Config::frame_length));
		Console::draw();
	}
}

void drawSideRoad(int y, int attr)
{
	auto chars = Utilities::getPixelChars();
	for (int i = 0; i < 117; ++i)
	{
		Console::write(34 + i, y, chars.bottom, attr);
	}
}

void draw1()
{
	std::stringstream people;
	people
		<< char(32) << char(32) << char(222) << char(219) << char(221) << char(32) << char(32) << "\n"
		<< char(220) << char(220) << char(220) << char(219) << char(220) << char(220) << char(220) << "\n"
		<< char(219) << char(222) << char(219) << char(219) << char(219) << char(221) << char(219) << "\n"
		<< char(32) << char(222) << char(219) << char(219) << char(219) << char(221) << char(32) << "\n"
		<< char(32) << char(32) << char(219) << char(32) << char(219) << char(32) << char(32);

	Console::write(93, 42, people.str(), 15);
}

void UIMainMenu::draw()
{
	if (_show)
	{
		Console::drawObject("UserInterface/SplashScreen/SS-name.txt", 61, 33);
		drawSideRoad(5, Utilities::Color::Red);
		drawSideRoad(41, Utilities::Color::Red);
		draw1();
		Utilities::TextWithBorderOptions options{ _width, _height };
		Console::write(_x - 1, _y - 1, Utilities::textWithBorder(options, ""), Utilities::Color::Yellow);

		for (auto i = 0; i < _buttons.size(); ++i)
		{
			if (i == _hoveredButton)
			{
				_buttons[i].highlight();
				_buttons[i].draw();
			}
			else
			{
				_buttons[i].unHighlight();
				_buttons[i].draw();
			}
		}
	}
}

void UIMainMenu::show()
{
	for (auto i = 0; i < _buttons.size(); ++i)
	{
		_buttons[i].show();
	}
	_show = true;
	draw();
}

void UIMainMenu::hide()
{
	for (auto i = 0; i < _buttons.size(); ++i)
	{
		_buttons[i].hide();
	}
	Console::cls(_x - 1, _y - 1, _width + 2, _height + 2);
	_show = false;
}

bool UIMainMenu::onKeyPressed(unsigned short key) {
	if (isShowing())
	{
		WORD parsedKey = Config::parseKey(key);

		switch (parsedKey) 
		{
		case Config::Key::key_up:
		case Config::Key::key_left:
			if (_hoveredButton == 0)
				_hoveredButton = _buttons.size() - 1;
			else
				_hoveredButton--;
			return true;

		case Config::Key::key_down:
		case Config::Key::key_right:
			if (_hoveredButton == _buttons.size() - 1)
				_hoveredButton = 0;
			else
				_hoveredButton++;
			return true;

		case Config::Key::key_enter:
			onButtonPressed(_hoveredButton);
			return true;
		}
	}
	return _game->onKeyPressed(key);
}


void UIMainMenu::onButtonPressed(int ID) {
	this->hide();
	switch (ID)
	{
	case 0: // New Game
		newGame();
		break;
	case 1: // Continue
		startGame();
		break;

	case 2: // Load Game
		_game->load();
		startGame();
		break;

	case 3: // Setting
		_game->setting();
		break;

	case 4: // Exit
		this->hide();
		return;
	}
	this->show();
}