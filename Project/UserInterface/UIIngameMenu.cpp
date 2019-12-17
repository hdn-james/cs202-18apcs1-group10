#include "UIIngameMenu.h"

#include <sstream>
#include <thread>

#include "../Console/Console.h"
#include "../Console/Config.h"
#include "../Console/Utilities.h"

using namespace std;

UIIngameMenu* UIIngameMenu::_instance = nullptr;
UIIngameMenu* UIIngameMenu::getInstance() {
	if (_instance == nullptr)
		_instance = new UIIngameMenu();
	return _instance;
}

UIIngameMenu::UIIngameMenu(int x, int y, int width, int height) {
	using namespace Utilities;

	_show = true;
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	TextWithBorderOptions options{ 18 };
	_buttons.push_back(UIButton(_x + (_width - 19) / 2, _y + 4 * 0 + 1, "      New Game       "));
	_buttons.push_back(UIButton(_x + (_width - 19) / 2, _y + 4 * 1 + 1, "      Continue       "));
	_buttons.push_back(UIButton(_x + (_width - 19) / 2, _y + 4 * 2 + 1, "      Load Game      "));
	_buttons.push_back(UIButton(_x + (_width - 19) / 2, _y + 4 * 3 + 1, "      Setting        "));
	_buttons.push_back(UIButton(_x + (_width - 19) / 2, _y + 4 * 4 + 1, "      Exit           "));
}

UIIngameMenu::~UIIngameMenu() {
	delete _instance;
}

UIIngameMenu::ingame_option UIIngameMenu::getOption()
{
	this->show();
	while (this->isShowing())
	{
		Console::waitInput(this);
		this->draw();
		Console::draw();
		Sleep(Config::get(Config::frame_length));
	}
	return ingame_option(_hoveredButton);
}

void UIIngameMenu::draw()
{
	if (_show)
	{
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

void UIIngameMenu::show()
{
	for (auto i = 0; i < _buttons.size(); ++i)
	{
		_buttons[i].show();
	}
	_show = true;
}

void UIIngameMenu::hide()
{
	for (auto i = 0; i < _buttons.size(); ++i)
	{
		_buttons[i].hide();
	}
	Console::cls(_x - 1, _y - 1, _width + 2, _height + 2);
	_show = false;
}

bool UIIngameMenu::onKeyPressed(unsigned short key) {
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

		case Config::key_esc:
			_hoveredButton = 0;
			onButtonPressed(_hoveredButton);
			return true;
		}
	}
	return false;
}


void UIIngameMenu::onButtonPressed(int btnId) {
	this->hide();
}