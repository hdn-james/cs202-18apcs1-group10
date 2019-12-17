#ifndef UIINGAMEMENU_H
#define UIINGAMEMENU_H

#include "UIButton.h"

#include <vector>
#include <functional>

class UIIngameMenu : public UI
{
public:
    enum ingame_option
    {
        continue_,
        save,
        load,
        setting,
        exit
    };

private:
    std::vector<UIButton> _buttons;
    int _hoveredButton = 0;
    static UIIngameMenu *_instance;
    UIIngameMenu(int x = 80, int y = 10, int width = 28, int height = 20);

public:
    static UIIngameMenu *getInstance();
    ~UIIngameMenu();
    ingame_option getOption();

    void draw();
    void show();
    void hide();

    bool onKeyPressed(unsigned short);
    void onButtonPressed(int);
};

#endif // !UIINGAMEMENU_H