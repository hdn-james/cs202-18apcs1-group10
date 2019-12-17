#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <string>

#include "UIGame.h"

UIGame* UIGame::_instance = nullptr;

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


void UIGame::load()
{;
	this->pause();
	
	std::string filename = UIPopUp::Prompt(60, 17, "                Enter file name:");
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

	std::string filename = UIPopUp::Prompt(60, 15, "          Enter file name:");
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
