#include "UIPopUp.h"

#include "../Console/Console.h"
#include "../Console/Config.h"
#include "../Console/Utilities.h"

#include <sstream>
#include <iostream>

UIPopUp::UIPopUp(short x, short y, std::string msg, PopUpType type)
{
	using namespace Utilities;

	UIPopUp::_type = type;
	UIPopUp::_done = false;
	UIPopUp::_result = nullptr;

	auto size = Console::getSize();
	UI::_width = popup_width;
	UI::_height = popup_height;
	UI::_x = x;
	UI::_y = y;

	int i = _width - 1;
	while (i < msg.length())
	{
		msg.insert(i, 1, '\n');
		i += _width - 1;
	}
	UIPopUp::_msg = msg;

	if (type == UIPopUp::alert)
	{
		UIPopUp::_buttons.push_back(UIButton(UI::_x + UI::_width/2 - 1, UI::_y + UI::_height - 2, alignText(center, "Ok", 4)));
	}
	else if (type == UIPopUp::question)
	{
		UIPopUp::_buttons.push_back(UIButton(UI::_x + UI::_width/2 - 7, UI::_y + UI::_height - 2, alignText(center, "Yes", 6)));
		UIPopUp::_buttons.push_back(UIButton(UI::_x + UI::_width/2 + 4, UI::_y + UI::_height - 2, alignText(center, "No", 6)));
	}
	else
	{
		UIPopUp::_buttons.push_back(UIButton(UI::_x + UI::_width/2 - 6, UI::_y + UI::_height - 2, alignText(center, "Ok", 4)));
		UIPopUp::_buttons.push_back(UIButton(UI::_x + UI::_width/2 + 1, UI::_y + UI::_height - 2, alignText(center, "Cancel", 8)));
	}
	if (type == PopUpType::prompt)
	{
		_result = new std::string;
		Console::GotoXY(_x + 2, _y + _height - 4);
	}
}

UIPopUp::~UIPopUp() { delete _result; }

void UIPopUp::Alert(short x, short y, std::string msg)
{
	UIPopUp p(x, y, msg, PopUpType::alert);
	while (!p._done)
	{
		Console::waitInput(&p);
		p.draw();
		Console::draw();
	}
}

bool UIPopUp::Question(short x, short y, std::string msg)
{
	UIPopUp p(x, y, msg, PopUpType::question);
	while (!p._done) {
		Console::waitInput(&p);
		p.draw();
		Console::draw();
	}
	return *((bool*)p._result);
	return false;
}

bool UIPopUp::Confirm(short x, short y, std::string msg) {
	UIPopUp p(x, y, msg, PopUpType::confirm);
	while (!p._done) {
		Console::waitInput(&p);
		p.draw();
		Console::draw();
	}
	return *((bool*)p._result);
}

std::string UIPopUp::Prompt(short x, short y, std::string msg) {
	UIPopUp p(x, y, msg, PopUpType::prompt);
	while (!p._done) {
		Console::waitInput(&p);
		p.draw();
		Console::draw();
	}
	if (p._result)
		return *((std::string*) p._result);
	else
		return "";
}

void UIPopUp::drawBorder(int x, int y, int width, int height, int color)
{
	auto chars = Utilities::getPixelChars();

	Console::write(x, y, chars.full, color);
	Console::write(x + width - 1, y, chars.full, color);
	Console::write(x, y + height - 1, chars.full, color);
	Console::write(x + width - 1, y + height - 1, chars.full, color);

	for (int i = x + 1; i < x + width - 1; i++)
	{
		Console::write(i, y, chars.top, color);
		Console::write(i, y + height - 1, chars.bottom, color);
	}

	for (int i = y + 1; i < y + height - 1; i++)
	{
		Console::write(x, i, chars.full, color);
		Console::write(x + width - 1, i, chars.full, color);
	}
}

void UIPopUp::draw() {

	using namespace Utilities;

	cls();

	if (!_done)
	{
		auto size = Console::getSize();
		int color = Color::Yellow
			;

		Console::write(_x + 1, _y + 1, _msg, Color::Yellow);
		drawBorder(_x, _y, _width, _height, color);

		if (_type == PopUpType::prompt) {
			auto chars = getChars(SINGLE);
			Console::write(_x + 1, _y + _height - 5, chars.topLeft, color);
			Console::write(_x + 1, _y + _height - 4, chars.vertical, color);
			Console::write(_x + 1, _y + _height - 3, chars.bottomLeft, color);
			Console::write(_x + _width - 2, _y + _height - 5, chars.topRight, color);
			Console::write(_x + _width - 2, _y + _height - 4, chars.vertical, color);
			Console::write(_x + _width - 2, _y + _height - 3, chars.bottomRight, color);
			for (int i = _x + 2; i <= _x + _width - 3; i++) {
				Console::write(i, _y + _height - 5, chars.horizontal, color);
				Console::write(i, _y + _height - 3, chars.horizontal, color);
			}
		}

		for (int i = 0; i < _buttons.size(); ++i)
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
		auto charP = Utilities::getPixelChars();
				if (_type == UIPopUp::alert)
		{
			Console::write(_x + (_width / 2 - 2), _y + _height - 2, charP.right, color);
			Console::write(_x + (_width / 2 + 3), _y + _height - 2, charP.left, color);
		} 
		else if (_type == UIPopUp::question)
		{
			Console::write(_x + (_width/2 - 8), _y + _height - 2, charP.right, color);
			Console::write(_x + (_width/2 - 1), _y + _height - 2, charP.left, color);
			Console::write(_x + (_width/2 + 3), _y + _height - 2, charP.right, color);
			Console::write(_x + (_width/2 + 10), _y + _height - 2, charP.left, color);
		}
		else
		{
					Console::write(_x + (_width / 2 - 7), _y + _height - 2, charP.right, color);
					Console::write(_x + (_width / 2 - 2), _y + _height - 2, charP.left, color);
					Console::write(_x + (_width / 2), _y + _height - 2, charP.right, color);
					Console::write(_x + (_width / 2 + 9), _y + _height - 2, charP.left, color);
		}

		if (_type == PopUpType::prompt) {
			std::string temp = *((std::string*) _result);
			Console::write(_x + 2, _y + _height - 4, temp, Color::Yellow);
			if (!_donePrompt)
				Console::GotoXY(_x + 2 + temp.length(), _y + _height - 4);
		}
	}
}

bool UIPopUp::onKeyPressed(unsigned short key) {
	if (_type == UIPopUp::prompt && _donePrompt == false)
	{
		size_t len = ((std::string*) _result)->length();
		if (key == VK_BACK) {
			if (len > 0)
				((std::string*) _result)->pop_back();
			return true;
		}

		std::string temp = key == VK_SPACE ? " " : Utilities::vk2Str(key);
		if (temp.length() == 1 && len < popup_width - 10) {
			*((std::string*) _result) += temp[0];
			return true;
		}
	}

	WORD parsedKey = Config::parseKey(key);
	switch (parsedKey) {
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
		_donePrompt = true;	
		_hoveredButton = 1;
		onButtonPressed(_hoveredButton);
		return true;
	}
	return true;
}

void UIPopUp::onButtonPressed(int ID) {
	_done = true;
	if (_type != PopUpType::prompt)
		_result = new bool(!ID);
	else if (ID == 1) {
		delete _result;
		_result = nullptr;
	}
}