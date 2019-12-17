#ifndef UIMAINMENU_H
#define UIMAINMENU_H

#include "UIButton.h"
#include "UIGame.h"
#include "UISidePanel.h"

#include <vector>
#include <functional>

class UIMainMenu : public UI
{
private:
    std::vector<UIButton> _buttons;
    int _hoveredButton = 0;
    UIGame *_game = nullptr;

    static UIMainMenu *_instance;
    UIMainMenu(int x = 80, int y = 10, int width = 28, int height = 20);

public:
    static UIMainMenu *getInstance();
    ~UIMainMenu();

    void newGame();
    void startGame();
    void draw();
    void show();
    void hide();

    bool onKeyPressed(unsigned short);
    void onButtonPressed(int);
};

#endif // !GUIMAINMENU_H