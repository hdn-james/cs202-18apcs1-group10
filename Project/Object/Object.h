#ifndef OBJECT_H
#define OBJECT_H

#define CAR "Object/Draw/car.txt"
#define BIRD "Object/Draw/bird.txt"
#define BIRD_REVERSE "Object/Draw/birdR.txt"
#define DINOSAUR "Object/Draw/dinosaur.txt"
#define DINOSAUR_REVERSE "Object/Draw/dinosaurR.txt"
#define TRUCK "Object/Draw/truck.txt"
#define TRUCK_REVERSE "Object/Draw/truckR.txt"

#include <sstream>
#include <ctime>

#include "../Console/Console.h"
#include "../Console/Config.h"

#pragma comment(lib, "Winmm.lib")

class Object
{
protected:
  int _x = 0, _y = 0;
  int attr = 15;
  int width = 0, height = 0;
  bool show = false;

  double absX = 0, absY = 0;
  int veX = 1;
  int veY = 1;
  clock_t lastMovingTime = clock();

public:
  enum object_type
  {
    truck,
    car,
    dinosaur,
    bird,
    people
  };

  virtual double get_x();
  virtual double get_y();
  virtual int get_veX();
  virtual int get_veY();
  virtual int get_attribute();
  virtual int get_width();
  virtual int get_height();
  virtual double get_distanceFrom(Object *) const;
  virtual double get_distanceFrom(double, double) const;

  virtual bool contains(int, int) const;
  virtual bool impact(Object *) const;
  virtual bool isShowing() const;
  virtual void set(int, int);

  virtual void resetTime();
  virtual void move();
  virtual void setVelocity(int, int);

  virtual void draw() = 0;
  virtual void drawReverse() = 0;

  virtual void cls();
  virtual int type() const = 0;
  virtual void crash() const;
};

#endif // !OBJECT_H