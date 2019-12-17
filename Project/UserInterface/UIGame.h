#ifndef UIGAME_H
#define UIGAME_H

#include "../Console/Console.h"
#include "../Console/Utilities.h"
#include "../Object/Dinosaur.h"
#include "../Object/Truck.h"
#include "../Object/Bird.h"
#include "../Object/Car.h"
#include "../Object/People.h"

#include "UIIngameMenu.h"
#include "UISidePanel.h"
#include "UIPopUp.h"
#include "UI.h"

class UIGame : public UI
{
public:
    enum difficulty
    {
        easy,
        normal,
        hard
    };

private:
    struct Lane
    {
        int X = 0, Y = 0;
        int Velocity = 1;
        std::vector<Object *> objects;
    };

    int _laneNum = 6;
    int _laneHeight = 5;
    int _laneWidth = 119;

    int _level = 1;
    int _minSpace = 20;
    difficulty _difficulty = difficulty::easy;

    const int _factor[3][3] = {
        {1, 1, 3},
        {2, 2, 4},
        {3, 3, 6}};
	
    std::vector<Lane> _lanes;
    People *_people;

    int _pauseFrame = 10;
    bool _pause = false;
    bool _mute = false;

    static UIGame *_instance;
    UIGame();

    void drawSideRoad(int, int);
    void drawLaneBreak(int, int);
    void hdrawTrafficLight(int);
    int findLane(Object *);
    int Rand(int, int);

    void loadPeople(std::istream &);
    void savePeople(std::ostream &);
    Object *loadObject(std::istream &);
    void saveObject(std::ostream &, Object *);

public:
    static UIGame *getInstance();
    ~UIGame();
    std::string difficultyToString();

    void reset();
    void init();
    void check();
    void addObject();
    void writeInfo();
    void update();

    void pause();
    void Continue();
    void setDifficulty(difficulty);
    void setting();
    void load();
    void save();

    void ingameMenu();
    bool onKeyPressed(unsigned short);
    void draw();

    Object *newObject(int, int attr = 15);
    void deleteObjects();
};
#endif // !UIGAME_H
