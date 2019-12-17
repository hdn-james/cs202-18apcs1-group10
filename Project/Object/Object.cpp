#include <thread>

#include "Object.h"
using namespace std;

double Object::get_x() { return absX; }

double Object::get_y() { return absY; }

int Object::get_veX() { return veX; }

int Object::get_veY() { return veY; }

int Object::get_attribute() { return attr; }

int Object::get_width() { return width; }

int Object::get_height() { return height; }

double Object::get_distanceFrom(Object *other) const
{
    double distance_X = abs(other->absX - (absX + width));
    if (distance_X > abs(other->absX + other->width - absX))
        distance_X = abs(other->absX + other->width - absX);

    double distance_Y = other->absY - (absY + height);
    if (distance_Y > abs(other->absY + other->height - absY))
        distance_Y = abs(other->absY + other->height - absY);

    return sqrt(distance_X * distance_X + distance_Y * distance_Y);
}

double Object::get_distanceFrom(double x, double y) const
{
    double distance_X = abs(x - (absX + width));
    if (distance_X > abs(x - absX))
        distance_X = abs(x - absX);

    double distance_Y = y - (absY + height);
    if (distance_Y > abs(y - absY))
        distance_Y = abs(y - absY);

    return sqrt(distance_X * distance_X + distance_Y * distance_Y);
}

bool Object::contains(int x, int y) const
{
    if (_x <= x && x < _x + width && _y <= y && y < _y + height)
        return true;
    return false;
}

bool Object::impact(Object *other) const
{
    for (int i = _x; i < _x + width; i++)
        for (int j = _y; j < _y + height; j++)
        {
            if (other->contains(i, j))
                return true;
        }
    return false;
}

bool Object::isShowing() const { return show; }

void Object::set(int x, int y)
{
    absX = _x = x;
    absY = _y = y;
}

void Object::setVelocity(int velX, int velY)
{
	veX = velX;
	veY = velY;
}

void Object::resetTime()
{
    lastMovingTime = clock();
}

void Object::move()
{
    if (veX + veY == 0)
        return;
    double deltaT = double(clock() - lastMovingTime);
    if (deltaT >= Config::get(Config::frame_length))
    {
        absX += 1.0 * veX * deltaT / 1000;
        absY += 1.0 * veY * deltaT / 1000;
        _x = int(absX);
        _y = int(absY);
        this->lastMovingTime = clock();
    }
}

void Object::cls()
{
    Console::cls(this->_x, this->_y, this->width, this->height);
    this->show = false;
}

void Object::crash() const
{
    mciSendString("play \"Sounds/crash1.mp3\"", NULL, 0, NULL);
}