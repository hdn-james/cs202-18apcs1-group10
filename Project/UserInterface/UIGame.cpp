#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <string>

#include "UIGame.h"

UIGame* UIGame::_instance = nullptr;

UIGame* UIGame::getInstance()
{
	if (_instance) return _instance;
	return new UIGame();
}

int UIGame::Rand(int left, int right)
{
	return (rand() * (RAND_MAX + 1)
		+ rand()) % (right - left + 1) + left;
}

void UIGame::loadPeople(std::istream & stream)
{
	int x, y;
	stream.read(reinterpret_cast<char *>(&x), sizeof(x));
	stream.read(reinterpret_cast<char *>(&y), sizeof(y));
	_people = new People(x, y);
}

void UIGame::savePeople(std::ostream & stream)
{
	int x = _people->get_x();
	int y = _people->get_y();
	stream.write(reinterpret_cast<char *>(&x), sizeof(x));
	stream.write(reinterpret_cast<char *>(&y), sizeof(y));
}

Object* UIGame::loadObject(std::istream& stream)
{
	int type, x, y, attr;
	stream.read(reinterpret_cast<char *>(&type), sizeof(type));
	stream.read(reinterpret_cast<char *>(&x), sizeof(x));
	stream.read(reinterpret_cast<char *>(&y), sizeof(y));
	stream.read(reinterpret_cast<char *>(&attr), sizeof(attr));

	Object* obj = newObject(type, attr);
	obj->set(x, y);
	return obj;
}

void UIGame::saveObject(std::ostream& stream, Object* obj)
{
	int type = obj->type();
	int x = obj->get_x();
	int y = obj->get_y();
	int attr = obj->get_attribute();
	stream.write(reinterpret_cast<char *>(&type), sizeof(type));
	stream.write(reinterpret_cast<char *>(&x), sizeof(x));
	stream.write(reinterpret_cast<char *>(&y), sizeof(y));
	stream.write(reinterpret_cast<char *>(&attr), sizeof(attr));
}

UIGame::UIGame()
{
	srand(time(NULL));
	_x = 34;
	_y = 0;
	_width = 119;
	_height = 41;
	_level = 1;
	_show = true;
	_pause = false;

	for (int i = 0; i < _laneNum; ++i)
	{
		_lanes.push_back(Lane{ _x, _y + (i + 1) * (_laneHeight + 1)});
	}
	reset();
}

UIGame::~UIGame()
{
	if (_people != nullptr)
	{
		delete _people;
		_people = nullptr;
	}
	deleteObjects();
}

std::string UIGame::difficultyToString()
{
	switch (_difficulty)
	{
	case UIGame::easy:
		return "Easy";

	case UIGame::normal:
		return "Normal";

	case UIGame::hard:
		return "Hard";
	}
	return "";
}

void UIGame::reset()
{
	_level = 1;
	_show = true;
	_pause = false;
	deleteObjects();
	init();
}

void UIGame::init()
{
	_minSpace = 20 - _level * _factor[_difficulty][0];
	int minVel = _level * _factor[_difficulty][1];
	int maxVel = _level * _factor[_difficulty][2];

	for (int i = 0; i < _laneNum; ++i)
	{
		_lanes[i].Velocity = Rand(minVel, maxVel);
		_lanes[i].Velocity *= Rand(0, 1) ? -1 : 1;
	}

	Object* newObj = nullptr;
	for (int k = 0; k < 10; ++k)
	{
		for (int i = 0; i < _laneNum; ++i)
		{
			// New objects
			if (!newObj)
				newObj = newObject(rand() % 4, 15);

			int newObjX = _lanes[i].X + Rand(0, _width - 1);
			int newObjY = _lanes[i].Y + _laneHeight - newObj->get_height();

			newObj->set(newObjX, newObjY);
			newObj->setVelocity(_lanes[i].Velocity, 0);

			bool canAddObj = true;
			for (int j = 0; j < _lanes[i].objects.size(); ++j)
			{
				Object* obj = _lanes[i].objects[j];
				int space = Rand(_minSpace, _width);

				if (newObj->impact(obj) || newObj->get_distanceFrom(obj) < space)
				{
					canAddObj = false;
				}
			}

			if (canAddObj)
			{
				_lanes[i].objects.push_back(newObj);
				newObj = nullptr;
			}
		}
	}
	_people = new People();
	_people->set(_x + _width / 2, _lanes[_laneNum - 1].Y + (_laneHeight + 1));
	_people->setVelocity(0, 0);
}

void UIGame::check()
{
	if (_people->get_y() < _lanes[0].Y)
	{
		_level++;
		deleteObjects();
		init();
		UIPopUp::Alert(65, 15, "NEXT LEVEL: " + std::to_string(_level));
		return;
	}

	for (int i = 0; i < _laneNum; ++i)
	{
		for (int j = 0; j < _lanes[i].objects.size(); ++j)
		{
			if (_people->impact(_lanes[i].objects[j]))
			{
				if (!_mute)
				{
					_people->crash();
				}
		
				Console::drawObject("UserInterface/Crash/fire.txt", _people->get_x() - 5, max(0, _people->get_y() - 5));
				
				

				Console::draw();
				Sleep(10 * Config::get(Config::frame_length));

				bool result = UIPopUp::Question(60, 15, "You lose! Play again?");
				if (result)
				{
					this->reset();
				}
				else
				{
					this->hide();
				}
			}
		}
	}
}

void UIGame::addObject()
{
	Object* newObj = nullptr;
	for (int i = 0; i < _laneNum; ++i)
	{
		// New objects
		if (!newObj)
			newObj = newObject(rand() % 4, 9 + Rand(0, 6));

		int newObjX = _lanes[i].X + _width - 1;
		if (_lanes[i].Velocity > 0)
			newObjX = 2;
		int newObjY = _lanes[i].Y + _laneHeight - newObj->get_height();

		newObj->set(newObjX, newObjY);
		newObj->setVelocity(_lanes[i].Velocity, 0);

		// check if we can add an object to current lane
		bool canAddObj = true;
		for (int j = 0; j < _lanes[i].objects.size(); ++j)
		{
			Object* obj = _lanes[i].objects[j];
			int space = Rand(_minSpace, _width);

			if (newObj->impact(obj) || newObj->get_distanceFrom(obj) < space)
			{
				canAddObj = false;
			}
		}

		if (canAddObj)
		{
			_lanes[i].objects.push_back(newObj);
			newObj = nullptr;
		};
	}
}

std::string TextWithLength(std::string text, int length)
{
	while (text.length() < length)
		text += ' ';
	return text;
}

void UIGame::writeInfo()
{
	using namespace Utilities;
	UISidePanel* panel = UISidePanel::getInstance();
	panel->clsInfo();
	panel->setInfo(
		alignText(center, TextWithLength("Level      : " + std::to_string(_level), 20) + '\n', panel->width()) +
		alignText(center, TextWithLength("difficulty : " + difficultyToString(), 20) + '\n', panel->width()) +
		alignText(center, TextWithLength("Sound      : " + std::string((_mute) ? "Off" : "On"), 20) + '\n', panel->width())
	);
}

void UIGame::update()
{
	int now_pause = Rand(0, 100);
	if (now_pause == 0 && _pauseFrame == 0)
	{
		_pauseFrame = (3 - _difficulty) * 10;
	}

	if (_pauseFrame > 0)
	{
		_pauseFrame--;
		if (_pauseFrame == 0)
			this->Continue();
	}

	if (_pause) return;

	this->check();
	this->addObject();

	for (int i = 0; i < _laneNum; ++i)
	{
		for (int j = 0; j < _lanes[i].objects.size(); ++j)
		{
			Object* obj = _lanes[i].objects[j];	
			if (obj->get_x() >= _x + _width || obj->get_x() < 2)
			{
				obj->cls();
				_lanes[i].objects.erase(_lanes[i].objects.begin() + j++);
				continue;
			}
			obj->cls();
			if (_pauseFrame == 0)
				obj->move();
		}
	}
}

void UIGame::pause()
{
	_pause = true;
}

void UIGame::Continue()
{
	_pause = false;
	for (int i = 0; i < _laneNum; ++i)
	{
		for (int j = 0; j < _lanes[i].objects.size(); ++j)
		{
			_lanes[i].objects[j]->resetTime();
		}
	}
}

void UIGame::setDifficulty(difficulty dif)
{
	_difficulty = dif;
	deleteObjects();
	init();
}

void UIGame::setting()
{
	this->pause();
	std::string result = UIPopUp::Prompt(65, 17, "ENTER difficulty\n\nEasy - 1\nNormal - 2\nHard - 3");

	if (result == "")
	{
		this->Continue();
		return;
	}

	if (result == "1")
		setDifficulty(difficulty::easy);
	else if (result == "2")
		setDifficulty(difficulty::normal);
	else if (result == "3")
		setDifficulty(difficulty::hard);
	else 
		UIPopUp::Alert(65, 17, "                Invalid Input!");

	this->Continue();
}

int UIGame::findLane(Object* obj)
{
	for (int i = 0; i < _laneNum; ++i)
	{
		if (obj->get_y() >= _lanes[i].Y)
		{
			return i;
		}
	}
}

void UIGame::load()
{;
	this->pause();
	
	std::string filename;
	filename += "Saved/";
	filename += UIPopUp::Prompt(60, 17, "                Enter file name:");
	if (filename == "")
	{
		this->Continue();
		return;
	}
	
	filename += ".txt";
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		UIPopUp::Alert(60, 17, "            No such file or directory!");
	}
	else
	{
		this->deleteObjects();
		if (_people != nullptr)
		{
			delete _people;
			_people = nullptr;
		}

		file.read(reinterpret_cast<char *>(&_level), sizeof(_level));
		file.read(reinterpret_cast<char *>(&_difficulty), sizeof(_difficulty));
		this->loadPeople(file);

		for (int i = 0; i < _laneNum; ++i)
		{
			int size;
			file.read(reinterpret_cast<char *>(&_lanes[i].Velocity), sizeof(_lanes[i].Velocity));
			file.read(reinterpret_cast<char *>(&size), sizeof(size));
			for (int j = 0; j < size; ++j)
			{
				Object* obj = loadObject(file);
				obj->setVelocity(_lanes[i].Velocity, 0);
				_lanes[i].objects.push_back(obj);
			}
		}
		file.close();
		//UIPopUp::Alert(60, 15, "Successfully!");
	}
	this->Continue();
}

void UIGame::save()
{
	this->pause();

	std::string filename;
	filename += "Saved/";
	filename += UIPopUp::Prompt(60, 15, "          Enter file name:");
	if (filename == "")
	{
		this->Continue();
		return;
	}
	filename += ".txt";
	std::ofstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		UIPopUp::Alert(60, 17, "        Fail to save!");
	}
	else
	{
		file.write(reinterpret_cast<char *>(&_level), sizeof(_level));
		file.write(reinterpret_cast<char *>(&_difficulty), sizeof(_difficulty));
		this->savePeople(file);

		for (int i = 0; i < _laneNum; ++i)
		{
			int size = _lanes[i].objects.size();
			file.write(reinterpret_cast<char *>(&_lanes[i].Velocity), sizeof(_lanes[i].Velocity));
			file.write(reinterpret_cast<char *>(&size), sizeof(size));
			for (int j = 0; j < _lanes[i].objects.size(); ++j)
			{
				this->saveObject(file, _lanes[i].objects[j]);
			}
		}
		file.close();
		UIPopUp::Alert(60, 17, "                Successfully!");
	}
	this->Continue();
}

void UIGame::ingameMenu()
{
	this->pause();

	UIIngameMenu::ingame_option option = UIIngameMenu::getInstance()->getOption();
	switch (option)
	{
	case UIIngameMenu::continue_:
		this->Continue();
		break;

	case UIIngameMenu::setting:
		this->setting();
		break;

	case UIIngameMenu::load:
		this->load();
		UIPopUp::Alert(65, 15, "                 Loading....");
		Sleep(200);
		break;

	case UIIngameMenu::save:
		this->save();
		break;

	case UIIngameMenu::exit:
		this->hide();
		break;
	}
}

bool UIGame::onKeyPressed(unsigned short key)
{
	if (isShowing())
	{
		WORD parsedKey = Config::parseKey(key);
		switch (parsedKey)
		{
		case Config::key_pause:
			if (_pause)
				this->Continue();
			else
				this->pause();
			return true;

		case Config::key_esc:
			this->ingameMenu();
			return true;

		case Config::key_load:
			this->load();
			return true;

		case Config::key_save:
			this->save();
			return true;

		case Config::key_mute:
			if (this->_mute)
			{
				mciSendString("resume mp3", NULL, 0, NULL);
				this->_mute = false;
			}
			else
			{
				mciSendString("stop mp3", NULL, 0, NULL);
				this->_mute = true;
			}
		}

		if (_pause)
			return false;

		switch (parsedKey)
		{
		case Config::key_up:
			_people->cls();
			if (_people->get_y() > (int)_lanes[0].Y - (_laneHeight + 1))
				_people->set(_people->get_x(), _people->get_y() - ((int)_laneHeight + 1));
			return true;

		case Config::key_left:
			_people->cls();
			if (_people->get_x() > _x)
				_people->set(_people->get_x() - 1, _people->get_y());
			return true;

		case Config::key_down:
			_people->cls();
			if (_people->get_y() < (int)_lanes[_laneNum - 1].Y + (_laneHeight + 1))
				_people->set(_people->get_x(), _people->get_y() + ((int)_laneHeight + 1));
			return true;

		case Config::key_right:
			_people->cls();
			if (_people->get_x() < (int)_x + _width - 1)
				_people->set(_people->get_x() + 1, _people->get_y());
			return true;
		}
	}
	return false;
}

void UIGame::drawSideRoad(int y, int attr)
{
	auto chars = Utilities::getPixelChars();
	for (int i = 0; i < _width; ++i)
	{
		Console::write(_x + i, y,chars.bottom, attr);
	}	
}

void UIGame::drawLaneBreak(int y, int attr)
{
	auto chars = Utilities::getPixelChars();
	int temp = 0;
	for (int i = 0; i < _width; ++i)
	{
		temp = temp % 6;
		if (temp < 3) 
			Console::write(_x + i, y, chars.center, attr);
		temp++;
	}
}

void UIGame::hdrawTrafficLight(int attr)
{
	auto chars = Utilities::getPixelChars();
	std::stringstream stream;
	stream << chars.full << chars.full
			<< chars.full << chars.full;
	Console::write(_x, _lanes[0].Y - 3, stream.str(), attr);
	Console::write(_x + _width - 4, _lanes[0].Y - 3, stream.str(), attr);
}

void UIGame::draw()
{
	cls();
	Console::GotoXY(0, _y + _height);
	if (_show)
	{
		hdrawTrafficLight((int)(_pauseFrame > 0) ? Utilities::Color::Red : Utilities::Color::Cyan);

		drawSideRoad(5, Utilities::Color::Red);
		for (int i = 1; i <= _laneNum - 1; ++i)
		{
			drawLaneBreak(5 + i * (_laneHeight + 1), Utilities::Color::White);
		}
		drawSideRoad(5 + _laneNum * (_laneHeight + 1), Utilities::Color::Red);

		for (int i = 0; i < _laneNum; ++i)
		{
			for (int j = 0; j < _lanes[i].objects.size(); ++j)
			{
				_lanes[i].objects[j]->draw();
			}
		}
		_people->draw();
	}
	this->writeInfo();
}

Object*  UIGame::newObject(int type, int attr)
{
	Object* obj = nullptr;
	switch (type)
	{
	case Object::bird:
		obj = new Bird(0, 0, attr);
		break;
	case Object::car:
		obj = new Car(0, 0, attr);
		break;
	case Object::dinosaur:
		obj = new Dinosaur(0, 0, attr);
		break;
	case Object::truck:
		obj = new Truck(0, 0, attr);
		break;
	}
	return obj;
}

void UIGame::deleteObjects()
{
	for (int i = 0; i < _laneNum; ++i)
	{
		for (int j = 0; j < _lanes[i].objects.size(); ++j)
			delete _lanes[i].objects[j];
		_lanes[i].objects.clear();
	}
}
